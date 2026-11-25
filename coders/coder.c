/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 06:06:03 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/25 07:44:39 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (coder->compiles_done < coder->config->number_of_compiles_required)
	{
		if (run_coder_cycle(coder))
		{
			stop_simulation(coder->coordinator, 0);
			printf("Coder %d: cycle failed\n", coder->id);
			return (NULL);
		}
	}
	return (NULL);
}

static int	create_coders(t_coder *coders, t_config *config, t_dongle *dongles,
		t_coordinator *coord)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		coders[i].id = i + 1;
		coders[i].config = config;
		coders[i].dongles = dongles;
		coders[i].coordinator = coord;
		coders[i].right_index = i;
		coders[i].last_compile_start = coord->start_ms;
		coders[i].compiles_done = 0;
		if (i == 0)
			coders[i].left_index = config->number_of_coders - 1;
		else
			coders[i].left_index = i - 1;
		if (pthread_create(&coders[i].thread, NULL, coder_routine,
				&coders[i]) != 0)
		{
			break ;
		}
		i++;
	}
	return (i);
}

static int	join_coders(t_coder *coders, int count)
{
	int	i;
	int	failed;

	i = 0;
	failed = 0;
	while (i < count)
	{
		if (pthread_join(coders[i].thread, NULL) != 0)
		{
			failed = 1;
		}
		i++;
	}
	return (failed);
}

static int	finish_simulation(t_simulation *sim, int created, int monitor_ok)
{
	int	join_failed;
	int	result;

	if (!monitor_ok)
		stop_simulation(&sim->coord, 0);
	join_failed = join_coders(sim->coders, created);
	if (monitor_ok && pthread_join(sim->monitor_thread, NULL) != 0)
		join_failed = 1;
	result = 1;
	if (!join_failed)
	{
		result = (sim->coord.stopped || !monitor_ok);
		destroy_simulation(sim);
	}
	return (result);
}

int	start_coders(t_config *config)
{
	t_simulation	sim;
	int				created;
	int				monitor_ok;

	if (init_simulation(&sim, config) != 0)
		return (1);
	sim.coord.start_ms = get_time_ms();
	if (sim.coord.start_ms < 0)
	{
		destroy_simulation(&sim);
		return (1);
	}
	created = create_coders(sim.coders, sim.config, sim.dongles, &sim.coord);
	monitor_ok = 0;
	if (created == config->number_of_coders)
		monitor_ok = (pthread_create(&sim.monitor_thread, NULL, monitor_routine,
					&sim) == 0);
	return (finish_simulation(&sim, created, monitor_ok));
}

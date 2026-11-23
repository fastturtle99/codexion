/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 06:06:03 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/23 16:34:40 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	*coder_routine(void *arg)
{
	t_coder		*coder;
	long long	deadline;

	coder = (t_coder *)arg;
	deadline = coder->coordinator->start_ms + coder->config->time_to_burnout;
	if (submit_request(coder->coordinator, coder->id, deadline) != 0)
		return (printf("Coder %d: request failed\n", coder->id), NULL);
	printf("Coder %d submitted a request\n", coder->id);
	if (wait_for_grant(coder, deadline) != 0)
		return (printf("Coder %d: wait failed\n", coder->id), NULL);
	printf("Coder %d received its dongles\n", coder->id);
	usleep(50000);
	if (release_pair(coder))
		printf("Coder %d: release failed\n", coder->id);
	else
		printf("Coder %d released its dongles\n", coder->id);
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

int	start_coders(t_config *config)
{
	t_simulation	sim;
	int				created;
	int				failed;

	if (init_simulation(&sim, config) != 0)
		return (1);
	sim.coord.start_ms = get_time_ms();
	if (sim.coord.start_ms < 0)
	{
		destroy_simulation(&sim);
		return (1);
	}
	created = create_coders(sim.coders, sim.config, sim.dongles, &sim.coord);
	failed = join_coders(sim.coders, created);
	if (!failed)
		destroy_simulation(&sim);
	return (created != config->number_of_coders || failed);
}

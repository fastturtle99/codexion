/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 07:26:22 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/25 07:32:39 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	monitor_done(t_simulation *sim)
{
	int	i;
	int	done;
	int	required;

	if (pthread_mutex_lock(&sim->coord.mutex) != 0)
		return (-1);
	required = sim->config->number_of_compiles_required;
	done = sim->coord.stopped;
	i = 0;
	while (!done && i < sim->config->number_of_coders)
	{
		if (sim->coders[i].compiles_done < required)
			break ;
		i++;
	}
	if (i == sim->config->number_of_coders)
		done = 1;
	if (pthread_mutex_unlock(&sim->coord.mutex) != 0)
		return (-1);
	return (done);
}

void	*monitor_routine(void *arg)
{
	t_simulation	*sim;
	int				result;

	sim = (t_simulation *)arg;
	while (1)
	{
		result = check_burnout(sim);
		if (result != 0)
			break ;
		result = monitor_done(sim);
		if (result != 0)
			break ;
		sleep_ms(1);
	}
	return (NULL);
}

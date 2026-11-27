/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 16:54:32 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/25 17:18:23 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

static int	find_expired_coder(t_simulation *sim, long long now)
{
	t_coder	*coder;
	int		i;

	i = 0;
	while (i < sim->config->number_of_coders)
	{
		coder = &sim->coders[i];
		if (coder->compiles_done < sim->config->number_of_compiles_required
			&& now >= coder->last_compile_start + sim->config->time_to_burnout)
			return (coder->id);
		i++;
	}
	return (0);
}

static int	mark_burnout(t_coordinator *coord, int id)
{
	coord->stopped = 1;
	coord->burned_out_id = id;
	printf("Coder %d burned out\n", id);
	if (pthread_cond_broadcast(&coord->changed) != 0)
		return (-1);
	return (id);
}

int	check_burnout(t_simulation *sim)
{
	t_coordinator	*coord;
	long long		now;
	int				id;

	coord = &sim->coord;
	if (pthread_mutex_lock(&coord->mutex) != 0)
		return (-1);
	id = 0;
	if (!coord->stopped)
	{
		now = get_time_ms();
		if (now < 0)
			id = -1;
		else
			id = find_expired_coder(sim, now);
		if (id > 0)
			id = mark_burnout(coord, id);
	}
	if (pthread_mutex_unlock(&coord->mutex) != 0)
		return (-1);
	return (id);
}

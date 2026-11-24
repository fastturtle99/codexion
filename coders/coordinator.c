/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 23:29:16 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/24 16:19:47 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>
#include <string.h>

static int	init_coord_buffers(t_coordinator *coord)
{
	int	n;

	n = coord->coder_count;
	coord->waiting.items = malloc(sizeof(t_request) * n);
	if (!coord->waiting.items)
		return (1);
	coord->granted = malloc(sizeof(int) * n);
	if (!coord->granted)
	{
		free(coord->waiting.items);
		return (1);
	}
	memset(coord->granted, 0, sizeof(int) * n);
	return (0);
}

static int	init_coord_sync(t_coordinator *coord)
{
	if (pthread_mutex_init(&coord->mutex, NULL) != 0)
		return (1);
	if (pthread_cond_init(&coord->changed, NULL) != 0)
	{
		pthread_mutex_destroy(&coord->mutex);
		return (1);
	}
	return (0);
}

int	init_coordinator(t_coordinator *coord, t_dongle *dongles, t_config *config)
{
	coord->dongles = dongles;
	coord->waiting.size = 0;
	coord->waiting.capacity = config->number_of_coders;
	coord->waiting.scheduler = config->scheduler;
	coord->next_arrival = 0;
	coord->coder_count = config->number_of_coders;
	coord->stopped = 0;
	coord->burned_out_id = 0;
	if (init_coord_buffers(coord) != 0)
		return (1);
	if (init_coord_sync(coord) != 0)
	{
		free(coord->granted);
		free(coord->waiting.items);
		return (1);
	}
	return (0);
}

void	destroy_coordinator(t_coordinator *coord)
{
	pthread_cond_destroy(&coord->changed);
	pthread_mutex_destroy(&coord->mutex);
	free(coord->granted);
	free(coord->waiting.items);
}

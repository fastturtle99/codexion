/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 20:01:15 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/02 23:22:43 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

void	destroy_dongles(t_dongle *dongles, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&dongles[i].mutex);
		i++;
	}
}

int	init_dongles(t_dongle *dongles, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		dongles[i].cooldown_until = 0;
		dongles[i].in_use = 0;
		if (pthread_mutex_init(&dongles[i].mutex, NULL) != 0)
		{
			destroy_dongles(dongles, i);
			return (1);
		}
		i++;
	}
	return (0);
}

t_dongle	*alloc_dongles(int count)
{
	t_dongle	*dongles;

	dongles = malloc(sizeof(t_dongle) * count);
	if (!dongles)
	{
		return (NULL);
	}
	if (init_dongles(dongles, count) != 0)
	{
		free(dongles);
		return (NULL);
	}
	return (dongles);
}

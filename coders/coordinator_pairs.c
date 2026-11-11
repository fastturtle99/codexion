/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinator_pairs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 08:15:02 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/11 08:15:50 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	dongle_ready(t_dongle *dongle, long long now)
{
	return (!dongle->in_use && now >= dongle->cooldown_until);
}

int	reserve_pair(t_coordinator *coord, int left, int right)
{
	long long	now;
	int			success;

	if (left == right)
		return (0);
	if (pthread_mutex_lock(&coord->mutex) != 0)
		return (0);
	success = 0;
	now = get_time_ms();
	if (now >= 0 && dongle_ready(&coord->dongles[left], now)
		&& dongle_ready(&coord->dongles[right], now))
	{
		coord->dongles[left].in_use = 1;
		coord->dongles[right].in_use = 1;
		success = 1;
	}
	pthread_mutex_unlock(&coord->mutex);
	return (success);
}

int	release_pair(t_coordinator *coord, int left, int right, int cooldown_ms)
{
	long long	now;

	if (left == right)
		return (1);
	if (pthread_mutex_lock(&coord->mutex) != 0)
		return (1);
	now = get_time_ms();
	if (now < 0)
	{
		pthread_mutex_unlock(&coord->mutex);
		return (1);
	}
	coord->dongles[left].cooldown_until = now + cooldown_ms;
	coord->dongles[right].cooldown_until = now + cooldown_ms;
	coord->dongles[left].in_use = 0;
	coord->dongles[right].in_use = 0;
	if (pthread_mutex_unlock(&coord->mutex) != 0)
		return (1);
	return (0);
}

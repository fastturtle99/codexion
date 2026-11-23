/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinator_pairs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 08:15:02 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/23 16:16:32 by anasufi          ###   ########.fr       */
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

static void	clear_pair(t_coder *coder, long long now)
{
	t_coordinator	*coord;

	coord = coder->coordinator;
	coord->dongles[coder->left_index].cooldown_until = now
		+ coder->config->dongle_cooldown;
	coord->dongles[coder->right_index].cooldown_until = now
		+ coder->config->dongle_cooldown;
	coord->dongles[coder->left_index].in_use = 0;
	coord->dongles[coder->right_index].in_use = 0;
	coord->granted[coder->id - 1] = 0;
	pthread_cond_broadcast(&coord->changed);
}

int	release_pair(t_coder *coder)
{
	t_coordinator	*coord;
	long long		now;

	coord = coder->coordinator;
	if (coder->left_index == coder->right_index)
		return (1);
	if (pthread_mutex_lock(&coord->mutex) != 0)
		return (1);
	now = get_time_ms();
	if (now >= 0)
		clear_pair(coder, now);
	if (pthread_mutex_unlock(&coord->mutex) != 0)
		return (1);
	return (now < 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_grant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 07:46:38 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/26 19:14:20 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

static int	pair_ready(t_coordinator *coord, int left, int right, long long now)
{
	t_dongle	*d;

	d = coord->dongles;
	if (left == right)
		return (0);
	return (!d[left].in_use && !d[right].in_use && now >= d[left].cooldown_until
		&& now >= d[right].cooldown_until);
}

static void	mark_granted(t_coordinator *coord, int left, int right,
		int coder_id)
{
	coord->dongles[left].in_use = 1;
	coord->dongles[right].in_use = 1;
	coord->granted[coder_id - 1] = 1;
	pthread_cond_broadcast(&coord->changed);
}

static int	stop_expired_head(t_coordinator *coord, int coder_id)
{
	coord->stopped = 1;
	coord->burned_out_id = coder_id;
	printf("Coder %d burned out\n", coder_id);
	if (pthread_cond_broadcast(&coord->changed) != 0)
		return (-1);
	return (0);
}

static int	grant_head(t_coordinator *coord, t_request *out, long long now)
{
	t_request	request;
	int			left;
	int			right;

	if (coord->waiting.size == 0)
		return (0);
	request = coord->waiting.items[0];
	right = request.coder_id - 1;
	left = (right + coord->coder_count - 1) % coord->coder_count;
	if (now >= request.deadline)
		return (stop_expired_head(coord, request.coder_id));
	if (!pair_ready(coord, left, right, now))
		return (0);
	if (heap_pop(&coord->waiting, out) != 0)
		return (-1);
	mark_granted(coord, left, right, out->coder_id);
	return (1);
}

int	try_grant_next(t_coordinator *coord, t_request *granted)
{
	long long	now;
	int			result;

	if (pthread_mutex_lock(&coord->mutex) != 0)
		return (-1);
	now = get_time_ms();
	if (now < 0)
		result = -1;
	else if (coord->stopped)
		result = 0;
	else
		result = grant_head(coord, granted, now);
	if (pthread_mutex_unlock(&coord->mutex) != 0)
		return (-1);
	return (result);
}

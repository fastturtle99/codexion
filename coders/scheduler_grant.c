/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_grant.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 07:46:38 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/10 07:47:00 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	pair_ready(t_coordinator *coord, int left, int right, long long now)
{
	t_dongle	*d;

	d = coord->dongles;
	if (left == right)
		return (0);
	return (!d[left].in_use && !d[right].in_use && now >= d[left].cooldown_until
		&& now >= d[right].cooldown_until);
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
	if (now >= request.deadline || !pair_ready(coord, left, right, now))
		return (0);
	if (heap_pop(&coord->waiting, out) != 0)
		return (-1);
	coord->dongles[left].in_use = 1;
	coord->dongles[right].in_use = 1;
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
	else
		result = grant_head(coord, granted, now);
	if (pthread_mutex_unlock(&coord->mutex) != 0)
		return (-1);
	return (result);
}

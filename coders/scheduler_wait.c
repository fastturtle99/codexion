/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_wait.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 06:38:05 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/23 16:12:34 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <errno.h>

static long long	next_wake_ms(t_coordinator *c, long long deadline,
		long long now)
{
	t_request	head;
	long long	ready;
	int			left;
	int			right;

	if (c->waiting.size == 0 || c->coder_count < 2)
		return (deadline);
	head = c->waiting.items[0];
	if (head.deadline <= now)
		return (deadline);
	right = head.coder_id - 1;
	left = (right + c->coder_count - 1) % c->coder_count;
	if (c->dongles[left].in_use || c->dongles[right].in_use)
		return (deadline);
	ready = c->dongles[left].cooldown_until;
	if (c->dongles[right].cooldown_until > ready)
		ready = c->dongles[right].cooldown_until;
	if (ready < deadline)
	{
		if (ready > now)
			return (ready);
		else
			return (now);
	}
	return (deadline);
}

static int	wait_until_change(t_coordinator *c, long long deadline)
{
	struct timespec	wake;
	long long		now;
	int				status;

	now = get_time_ms();
	if (now < 0 || now >= deadline)
		return (-1);
	ms_to_timespec(next_wake_ms(c, deadline, now), &wake);
	status = pthread_cond_timedwait(&c->changed, &c->mutex, &wake);
	if (status != 0 && status != ETIMEDOUT)
		return (-1);
	return (0);
}

static int	wait_once(t_coder *coder, long long deadline)
{
	t_coordinator	*c;
	int				result;

	c = coder->coordinator;
	if (pthread_mutex_lock(&c->mutex) != 0)
		return (-1);
	if (c->granted[coder->id - 1])
		result = 1;
	else
		result = wait_until_change(c, deadline);
	if (pthread_mutex_unlock(&c->mutex) != 0)
		return (-1);
	return (result);
}

int	wait_for_grant(t_coder *coder, long long deadline)
{
	t_request	granted;
	int			result;

	while (1)
	{
		if (try_grant_next(coder->coordinator, &granted) < 0)
			return (1);
		result = wait_once(coder, deadline);
		if (result == 1)
			return (0);
		if (result < 0)
			return (1);
	}
}

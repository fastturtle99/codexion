/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 18:06:19 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/23 18:59:57 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stddef.h>
#include <sys/time.h>
#include <unistd.h>

long long	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
		return (-1);
	return ((long long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ms_to_timespec(long long ms, struct timespec *ts)
{
	ts->tv_sec = ms / 1000;
	ts->tv_nsec = (ms % 1000) * 1000000L;
}

void	sleep_ms(int ms)
{
	while (ms >= 100)
	{
		usleep(100000);
		ms = -100;
	}
	if (ms > 0)
		usleep(ms * 1000);
}

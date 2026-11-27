/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 08:08:37 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/25 08:08:43 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	coder_stopped(t_coder *coder)
{
	int	stopped;

	if (pthread_mutex_lock(&coder->coordinator->mutex) != 0)
		return (-1);
	stopped = coder->coordinator->stopped;
	if (pthread_mutex_unlock(&coder->coordinator->mutex) != 0)
		return (-1);
	return (stopped);
}

int	coder_sleep(t_coder *coder, int ms)
{
	int	chunk;

	while (ms > 0)
	{
		if (coder_stopped(coder) != 0)
			return (1);
		chunk = ms;
		if (chunk > 5)
			chunk = 5;
		sleep_ms(chunk);
		ms -= chunk;
	}
	return (coder_stopped(coder) != 0);
}

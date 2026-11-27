/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_compile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 19:16:05 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/26 18:40:05 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	record_compile_start(t_coder *coder)
{
	t_coordinator	*coord;
	long long		now;
	int				status;

	coord = coder->coordinator;
	if (pthread_mutex_lock(&coord->mutex) != 0)
		return (1);
	now = get_time_ms();
	status = (now < 0 || coord->stopped);
	if (!status && now >= coder->last_compile_start
		+ coder->config->time_to_burnout)
		status = 2;
	if (!status)
		coder->last_compile_start = now;
	if (pthread_mutex_unlock(&coord->mutex) != 0)
		return (1);
	return (status);
}

int	perform_compile(t_coder *coder)
{
	int	status;

	status = record_compile_start(coder);
	if (status == 2)
		stop_simulation(coder->coordinator, coder->id);
	if (status != 0)
		return (1);
	return (coder_sleep(coder, coder->config->time_to_compile));
}

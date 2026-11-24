/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_compile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 19:16:05 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/23 19:16:11 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	perform_compile(t_coder *coder)
{
	t_coordinator	*coord;
	long long		now;

	coord = coder->coordinator;
	if (pthread_mutex_lock(&coord->mutex) != 0)
		return (1);
	now = get_time_ms();
	if (now >= 0)
		coder->last_compile_start = now;
	if (pthread_mutex_unlock(&coord->mutex) != 0)
		return (1);
	if (now < 0)
		return (1);
	sleep_ms(coder->config->time_to_compile);
	return (0);
}

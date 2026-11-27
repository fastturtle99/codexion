/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinator_stop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/24 16:20:23 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/25 17:27:23 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int	stop_simulation(t_coordinator *coord, int coder_id)
{
	int	result;

	if (pthread_mutex_lock(&coord->mutex) != 0)
		return (1);
	if (!coord->stopped)
	{
		coord->stopped = 1;
		coord->burned_out_id = coder_id;
		if (coder_id > 0)
			printf("Coder %d burned out\n", coder_id);
	}
	result = pthread_cond_broadcast(&coord->changed);
	if (pthread_mutex_unlock(&coord->mutex) != 0)
		return (1);
	return (result != 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requests.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 01:33:52 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/07 01:33:56 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	submit_request(t_coordinator *coord, int coder_id, long long deadline)
{
	t_request	request;
	long long	now;
	int			result;

	if (pthread_mutex_lock(&coord->mutex) != 0)
		return (1);
	now = get_time_ms();
	result = 1;
	if (now >= 0)
	{
		request.coder_id = coder_id;
		request.request_time = now;
		request.deadline = deadline;
		request.arrival_order = coord->next_arrival;
		result = heap_push(&coord->waiting, request);
		if (result == 0)
			coord->next_arrival++;
	}
	if (pthread_mutex_unlock(&coord->mutex) != 0)
		return (1);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_select.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 08:04:52 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/27 08:04:57 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	find_eligible_index(t_coordinator *coord, long long now)
{
	t_request	request;
	int			left;
	int			right;
	int			i;

	i = 0;
	while (i < coord->waiting.size)
	{
		request = coord->waiting.items[i];
		right = request.coder_id - 1;
		left = (right + coord->coder_count - 1) % coord->coder_count;
		if (now < request.deadline && !blocked_by_prior_request(coord, request)
			&& pair_ready(coord, left, right, now))
			return (i);
		i++;
	}
	return (-1);
}

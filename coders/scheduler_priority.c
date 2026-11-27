/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_priority.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 07:49:06 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/27 07:49:09 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	blocked_by_prior_request(t_coordinator *coord, t_request candidate)
{
	t_request	other;
	int			i;

	i = 0;
	while (i < coord->waiting.size)
	{
		other = coord->waiting.items[i];
		if (other.coder_id != candidate.coder_id && request_before(other,
				candidate, coord->waiting.scheduler)
			&& requests_conflict(other.coder_id, candidate.coder_id,
				coord->coder_count))
			return (1);
		i++;
	}
	return (0);
}

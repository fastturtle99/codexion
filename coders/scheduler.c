/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 01:15:51 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/19 01:16:02 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	fifo_before(t_request a, t_request b)
{
	return (a.arrival_order < b.arrival_order);
}

int	edf_before(t_request a, t_request b)
{
	if (a.deadline == b.deadline)
		return (a.arrival_order < b.arrival_order);
	return (a.deadline < b.deadline);
}

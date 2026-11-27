/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_conflict.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 07:36:51 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/27 07:37:00 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	requests_conflict(int first_id, int second_id, int count)
{
	int	left_a;
	int	right_a;
	int	left_b;
	int	right_b;

	right_a = first_id - 1;
	left_a = (right_a + count - 1) % count;
	right_b = second_id - 1;
	left_b = (right_b + count - 1) % count;
	return (left_a == left_b || left_a == right_b || right_a == left_b
		|| right_a == right_b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 06:52:43 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/21 05:11:33 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int	main(void)
{
	t_request	a;
	t_request	b;
	t_request	c;
	t_request	d;
	t_request	items[4];
	t_heap		heap;

	a = (t_request){1, 100, 900, 1};
	b = (t_request){2, 150, 600, 2};
	c = (t_request){3, 200, 1000, 3};
	d = (t_request){4, 250, 300, 4};
	heap.items = items;
	heap.size = 0;
	heap.capacity = 4;
	heap.scheduler = SCHEDULER_EDF;
	if (heap_push(&heap, a) != 0)
	{
		return (1);
	}
	if (heap_push(&heap, b) != 0)
	{
		return (1);
	}
	if (heap_push(&heap, c) != 0)
	{
		return (1);
	}
	if (heap_push(&heap, d) != 0)
	{
		return (1);
	}
	printf("Root: Coder %d, deadline %lld\n", heap.items[0].coder_id,
		heap.items[0].deadline);
	return (0);
}

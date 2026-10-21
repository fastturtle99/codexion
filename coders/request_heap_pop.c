/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_heap_pop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 05:14:10 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/21 05:39:16 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	request_sift_down(t_heap *heap)
{
	int	i;
	int	left;
	int	best;

	i = 0;
	while (1)
	{
		left = 2 * i + 1;
		if (left >= heap->size)
			break ;
		best = left;
		if (left + 1 < heap->size && request_before(heap->items[left + 1],
				heap->items[left], heap->scheduler))
			best = left + 1;
		if (!request_before(heap->items[best], heap->items[i], heap->scheduler))
			break ;
		request_swap(&heap->items[i], &heap->items[best]);
		i = best;
	}
}

int	heap_pop(t_heap *heap, t_request *removed)
{
	if (heap->size == 0)
		return (1);
	*removed = heap->items[0];
	heap->size--;
	if (heap->size == 0)
		return (0);
	heap->items[0] = heap->items[heap->size];
	request_sift_down(heap);
	return (0);
}

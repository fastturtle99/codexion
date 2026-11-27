/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_heap_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/27 08:13:06 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/27 08:20:18 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	swap_requests(t_request *a, t_request *b)
{
	t_request	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	sift_up_at(t_heap *heap, int i)
{
	int	parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (!request_before(heap->items[i], heap->items[parent],
				heap->scheduler))
			break ;
		swap_requests(&heap->items[i], &heap->items[parent]);
		i = parent;
	}
}

static void	sift_down_at(t_heap *heap, int i)
{
	int	left;
	int	right;
	int	best;

	while (1)
	{
		left = 2 * i + 1;
		right = left + 1;
		best = i;
		if (left < heap->size && request_before(heap->items[left],
				heap->items[best], heap->scheduler))
			best = left;
		if (right < heap->size && request_before(heap->items[right],
				heap->items[best], heap->scheduler))
			best = right;
		if (best == i)
			break ;
		swap_requests(&heap->items[i], &heap->items[best]);
		i = best;
	}
}

int	heap_remove_at(t_heap *heap, int index, t_request *out)
{
	int	parent;

	if (!heap || !out || index < 0 || index >= heap->size)
		return (1);
	*out = heap->items[index];
	heap->size--;
	if (index == heap->size)
		return (0);
	heap->items[index] = heap->items[heap->size];
	parent = (index - 1) / 2;
	if (index > 0 && request_before(heap->items[index], heap->items[parent],
			heap->scheduler))
		sift_up_at(heap, index);
	else
		sift_down_at(heap, index);
	return (0);
}

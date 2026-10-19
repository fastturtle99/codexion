/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request_heap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 02:26:30 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/19 02:26:38 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	heap_push(t_heap *heap, t_request request)
{
	int	i;
	int	parent;

	if (heap->size >= heap->capacity)
		return (1);
	i = heap->size;
	heap->items[i] = request;
	heap->size++;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (!request_before(heap->items[i], heap->items[parent],
				heap->scheduler))
			break ;
		request_swap(&heap->items[i], &heap->items[parent]);
		i = parent;
	}
	return (0);
}

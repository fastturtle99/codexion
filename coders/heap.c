/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 06:52:29 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/19 01:24:21 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	request_swap(t_request *a, t_request *b)
{
	t_request	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	heap_insert(int *heap, int *size, int capacity, int value)
{
	int	i;
	int	parent;

	if (*size >= capacity)
		return (1);
	i = *size;
	heap[i] = value;
	(*size)++;
	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (heap[parent] <= heap[i])
			break ;
		swap(&heap[parent], &heap[i]);
		i = parent;
	}
	return (0);
}

static void	heap_sift_down(int *heap, int size)
{
	int	i;
	int	left;
	int	right;
	int	smallest;

	i = 0;
	while (1)
	{
		left = 2 * i + 1;
		right = left + 1;
		smallest = i;
		if (left < size && heap[left] < heap[smallest])
			smallest = left;
		if (right < size && heap[right] < heap[smallest])
			smallest = right;
		if (smallest == i)
			break ;
		swap(&heap[i], &heap[smallest]);
		i = smallest;
	}
}

int	heap_remove(int *heap, int *size, int *removed)
{
	if (*size == 0)
		return (1);
	*removed = heap[0];
	(*size)--;
	if (*size == 0)
		return (0);
	heap[0] = heap[*size];
	heap_sift_down(heap, *size);
	return (0);
}

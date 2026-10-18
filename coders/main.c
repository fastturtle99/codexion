/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 06:52:43 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/19 00:27:26 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int	main(void)
{
	int	heap[3] = {42, 0, 0};
	int	size;
	int	removed;
	int	result;

	size = 1;
	result = heap_remove(heap, &size, &removed);
	printf("First removal: %d\n", result);
	printf("Removed value: %d\n", removed);
	printf("Heap size: %d\n", size);
	result = heap_remove(heap, &size, &removed);
	printf("Second removal: %d\n", result);
	return (0);
}

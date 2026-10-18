/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 06:52:43 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/19 00:09:34 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int	main(void)
{
	int	heap[10] = {300, 400, 700, 900, 500};
	int	size;
	int	i;

	size = 5;
	heap_insert(heap, &size, 10, 200);
	i = 0;
	while (i < size)
	{
		printf("%d ", heap[i]);
		i++;
	}
	printf("\n");
	return (0);
}

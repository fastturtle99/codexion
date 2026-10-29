/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 06:52:43 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/29 07:34:38 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc != 9)
	{
		fprintf(stderr, "Error: expected 8 arguments\n");
		return (1);
	}
	if (!validate_numbers(argv))
	{
		fprintf(stderr, "Error: invalid numeric argument\n");
		return (1);
	}
	printf("Argument count and first number are valid!\n");
	return (0);
}

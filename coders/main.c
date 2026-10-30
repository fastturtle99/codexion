/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 06:52:43 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/30 17:47:10 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_config	config;

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
	if (!is_valid_coder_count(argv[1]))
	{
		fprintf(stderr, "Error: coder count must be positive\n");
		return (1);
	}
	load_config(&config, argv);
	printf("Number of coders: %d", config.number_of_coders);
	printf("Burnout: %d ms\n", config.time_to_burnout);
	printf("Argument count and first number are valid!\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 06:52:43 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/03 18:17:10 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

static int	validate_input(int argc, char **argv)
{
	if (argc != 9)
	{
		fprintf(stderr, "Error: expected 8 arguments\n");
		return (0);
	}
	if (!validate_numbers(argv))
	{
		fprintf(stderr, "Error: invalid numeric argument\n");
		return (0);
	}
	if (!is_valid_coder_count(argv[1]))
	{
		fprintf(stderr, "Error: coder count must be positive\n");
		return (0);
	}
	if (!is_valid_scheduler(argv[8]))
	{
		fprintf(stderr, "Error: invalid scheduler\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_config	config;

	if (!validate_input(argc, argv))
		return (1);
	load_config(&config, argv);
	printf("Current time: %lld ms\n", get_time_ms());
	return (start_coders(&config));
}

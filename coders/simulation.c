/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 23:24:42 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/07 01:23:15 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

int	init_simulation(t_simulation *sim, t_config *config)
{
	sim->config = config;
	sim->coders = malloc(sizeof(t_coder) * config->number_of_coders);
	if (!sim->coders)
		return (1);
	sim->dongles = alloc_dongles(config->number_of_coders);
	if (!sim->dongles)
	{
		free(sim->coders);
		return (1);
	}
	if (init_coordinator(&sim->coord, sim->dongles, config) != 0)
	{
		destroy_dongles(sim->dongles, config->number_of_coders);
		free(sim->dongles);
		free(sim->coders);
		return (1);
	}
	return (0);
}

void	destroy_simulation(t_simulation *sim)
{
	destroy_coordinator(&sim->coord);
	destroy_dongles(sim->dongles, sim->config->number_of_coders);
	free(sim->dongles);
	free(sim->coders);
}

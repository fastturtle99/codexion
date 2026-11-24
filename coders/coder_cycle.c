/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/23 19:27:22 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/24 16:48:31 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

static void	debug_and_refactor(t_coder *coder)
{
	printf("Coder %d is debugging\n", coder->id);
	sleep_ms(coder->config->time_to_debug);
	printf("Coder %d is refactoring\n", coder->id);
	sleep_ms(coder->config->time_to_refactor);
}

static int	record_compile(t_coder *coder)
{
	t_coordinator	*coord;

	coord = coder->coordinator;
	if (pthread_mutex_lock(&coord->mutex) != 0)
		return (1);
	coder->compiles_done++;
	if (pthread_mutex_unlock(&coord->mutex) != 0)
		return (1);
	return (0);
}

int	run_coder_cycle(t_coder *coder)
{
	long long	deadline;
	int			compile_result;
	int			release_result;

	deadline = coder->last_compile_start + coder->config->time_to_burnout;
	if (submit_request(coder->coordinator, coder->id, deadline))
		return (1);
	printf("Coder %d submitted a request\n", coder->id);
	if (wait_for_grant(coder, deadline))
		return (1);
	printf("Coder %d received its dongles\n", coder->id);
	compile_result = perform_compile(coder);
	release_result = release_pair(coder);
	if (compile_result || release_result)
		return (1);
	if (record_compile(coder))
		return (1);
	printf("Coder %d released its dongles\n", coder->id);
	if (coder->compiles_done < coder->config->number_of_compiles_required)
		debug_and_refactor(coder);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 06:06:03 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/31 06:06:09 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

static void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	printf("Coder %d started (out of %d)\n", coder->id,
		coder->config->number_of_coders);
	return (NULL);
}

int	start_first_coder(t_config *config)
{
	t_coder	coder;

	coder.id = 1;
	coder.config = config;
	if (pthread_create(&coder.thread, NULL, coder_routine, &coder) != 0)
		return (1);
	if (pthread_join(coder.thread, NULL) != 0)
		return (1);
	return (0);
}

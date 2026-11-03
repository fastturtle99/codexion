/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 06:06:03 by anasufi           #+#    #+#             */
/*   Updated: 2026/11/02 22:45:05 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <stdlib.h>

static void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	// printf("Coder %d started (out of %d)\n", coder->id,
	// 	coder->config->number_of_coders);
	printf("Coder %d needs dongles D%d and D%d\n", coder->id, coder->left_index,
		coder->right_index);
	return (NULL);
}

static int	create_coders(t_coder *coders, t_config *config, t_dongle *dongles)
{
	int	i;

	i = 0;
	while (i < config->number_of_coders)
	{
		coders[i].id = i + 1;
		coders[i].config = config;
		coders[i].dongles = dongles;
		coders[i].right_index = i;
		if (i == 0)
			coders[i].left_index = config->number_of_coders - 1;
		else
			coders[i].left_index = i - 1;
		if (pthread_create(&coders[i].thread, NULL, coder_routine,
				&coders[i]) != 0)
		{
			break ;
		}
		i++;
	}
	return (i);
}

static int	join_coders(t_coder *coders, int count)
{
	int	i;
	int	failed;

	i = 0;
	failed = 0;
	while (i < count)
	{
		if (pthread_join(coders[i].thread, NULL) != 0)
		{
			failed = 1;
		}
		i++;
	}
	return (failed);
}

int	start_coders(t_config *config)
{
	t_coder		*coders;
	t_dongle	*dongles;
	int			created;
	int			failed;

	coders = malloc(sizeof(t_coder) * config->number_of_coders);
	if (!coders)
		return (1);
	dongles = alloc_dongles(config->number_of_coders);
	if (!dongles)
	{
		free(coders);
		return (1);
	}
	created = create_coders(coders, config, dongles);
	failed = join_coders(coders, created);
	if (!failed)
	{
		destroy_dongles(dongles, config->number_of_coders);
		free(dongles);
		free(coders);
	}
	return (created != config->number_of_coders || failed);
}

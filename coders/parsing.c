/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 07:24:47 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/30 17:36:14 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int	is_valid_number(const char *str)
{
	int	i;
	int	value;
	int	digit;

	if (!str || !str[0])
		return (0);
	i = 0;
	value = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		digit = str[i] - '0';
		if (value > (INT_MAX - digit) / 10)
			return (0);
		value = value * 10 + digit;
		i++;
	}
	return (1);
}

int	validate_numbers(char **argv)
{
	int	i;

	i = 1;
	while (i <= 7)
	{
		if (!is_valid_number(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_scheduler(const char *str)
{
	if (strcmp(str, "fifo") == 0)
		return (1);
	if (strcmp(str, "edf") == 0)
		return (1);
	return (0);
}

int	is_valid_coder_count(char *str)
{
	if (!is_valid_number(str))
		return (0);
	if (atoi(str) == 0)
		return (0);
	return (1);
}

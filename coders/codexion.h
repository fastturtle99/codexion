/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 06:52:40 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/18 07:26:19 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

void	swap(int *a, int *b);
int		heap_insert(int *heap, int *size, int capacity, int value);
int		heap_remove(int *heap, int *size, int *removed);

#endif

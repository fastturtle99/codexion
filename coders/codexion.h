/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 06:52:40 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/21 05:40:36 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

typedef struct s_request
{
	int				coder_id;
	long long		request_time;
	long long		deadline;
	unsigned long	arrival_order;
}					t_request;

typedef enum e_scheduler
{
	SCHEDULER_FIFO,
	SCHEDULER_EDF
}					t_scheduler;

typedef struct s_heap
{
	t_request		*items;
	int				size;
	int				capacity;
	t_scheduler		scheduler;
}					t_heap;

void				swap(int *a, int *b);
int					heap_insert(int *heap, int *size, int capacity, int value);
int					heap_remove(int *heap, int *size, int *removed);
int					fifo_before(t_request a, t_request b);
int					edf_before(t_request a, t_request b);
void				request_swap(t_request *a, t_request *b);
int					request_before(t_request a, t_request b,
						t_scheduler scheduler);
int					heap_push(t_heap *heap, t_request request);
int					heap_pop(t_heap *heap, t_request *removed);

#endif

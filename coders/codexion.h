/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anasufi <anasufi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 06:52:40 by anasufi           #+#    #+#             */
/*   Updated: 2026/10/31 06:09:37 by anasufi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>

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

typedef struct s_config
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	t_scheduler		scheduler;
}					t_config;

typedef struct s_heap
{
	t_request		*items;
	int				size;
	int				capacity;
	t_scheduler		scheduler;
}					t_heap;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	t_config		*config;
}					t_coder;

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
int					is_valid_number(const char *str);
int					validate_numbers(char **argv);
int					is_valid_coder_count(char *str);
void				load_config(t_config *config, char **argv);
int					start_first_coder(t_config *config);

#endif

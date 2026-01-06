/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:24:16 by meelma            #+#    #+#             */
/*   Updated: 2025/12/10 14:30:42 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

typedef enum e_optype
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_optype;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}			t_fork;

typedef struct s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_sleep;
	long	time_to_eat;
	long	nbr_limit_meals;
	long	start_simulation;
	bool	end_simulation;
	bool	all_threads_ready;
	t_mtx	table_mutex;
	t_mtx	write_mutex;
	t_fork	*forks;
	t_philo	*philos;
}				t_table;

/*  Parsing */
int		parse_input(t_table *table, char **av);

/* Safe Handle Mutex and Threads */
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_optype optype);
void	safe_mutex_handle(t_mtx *mutex, t_optype optype);

/* Init.c */
void	init_data(t_table *table);

/* Write.c */
void	write_status(t_philo_status status, t_philo *philo);

/* Simulation */
void	*simulation(void *data);
void	start_dinner(t_table *table);

/* Actions */
void	philo_think(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);

/* Monitor */
void	*monitor(void *data);

/* Setters and getters */
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	simulation_finnished(t_table *table);

/* Utils */
void	error_exit(const char *error);
void	*safe_malloc(size_t bytes);
void	*single_philo(void *data);

/* Time utils */
void	wait_all_threads(t_table *table);
long	gettime(t_time_code time_code);
void	custom_usleep(long usec, t_table *table);

/* Cleanup */
void	cleanup_simulation(void *data);

#endif

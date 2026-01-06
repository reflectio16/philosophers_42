/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:46:33 by meelma            #+#    #+#             */
/*   Updated: 2025/12/10 13:59:56 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h""

void	*simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	if (philo->id % 2 == 0)
		custom_usleep(philo->table->time_to_eat, philo->table);
	while (!simulation_finnished(philo->table))
	{
		if (philo->full)
			break ;
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

static void	create_threads(t_table *table)
{
	int	i;

	i = 0;
	if (table->philo_nbr == 1)
	{
		safe_thread_handle(&table->philos[0].thread_id, single_philo,
			&table->philos[0], CREATE);
	}
	else
	{
		while (i < table->philo_nbr)
		{
			safe_thread_handle(&table->philos[i].thread_id, simulation,
				&table->philos[i], CREATE);
			i++;
		}
	}
}

static void	init_simulation_start(t_table *table)
{
	int	i;

	table->start_simulation = gettime(MICROSECOND);
	i = 0;
	while (i < table->philo_nbr)
	{
		set_long(&table->table_mutex, &table->philos[i].last_meal_time,
			table->start_simulation);
		i++;
	}
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
}

static void	join_threads(t_table *table, pthread_t *monitor_thread)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
	safe_thread_handle(monitor_thread, NULL, NULL, JOIN);
}

void	start_dinner(t_table *table)
{
	pthread_t	monitor_thread;

	if (table->nbr_limit_meals == 0)
		return ;
	create_threads(table);
	init_simulation_start(table);
	safe_thread_handle(&monitor_thread, monitor, table, CREATE);
	join_threads(table, &monitor_thread);
}

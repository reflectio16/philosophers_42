/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:45:33 by meelma            #+#    #+#             */
/*   Updated: 2025/12/10 14:19:10 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	check_philo_death(t_table *table, int i)
{
	long	last_meal;

	last_meal = get_long(&table->table_mutex,
			&table->philos[i].last_meal_time);
	if (gettime(MICROSECOND) - last_meal > table->time_to_die)
	{
		set_bool(&table->table_mutex, &table->end_simulation, true);
		write_status(DIED, &table->philos[i]);
		return (true);
	}
	return (false);
}

static bool	check_all_philos(t_table *table)
{
	int	i;
	int	full_count;

	i = 0;
	full_count = 0;
	while (i < table->philo_nbr)
	{
		if (get_bool(&table->table_mutex, &table->philos[i].full))
		{
			full_count++;
			i++;
			continue ;
		}
		if (check_philo_death(table, i))
			return (true);
		i++;
	}
	if (full_count == table->philo_nbr)
	{
		set_bool(&table->table_mutex, &table->end_simulation, true);
		return (true);
	}
	return (false);
}

void	*monitor(void *data)
{
	t_table	*table;

	table = (t_table *)data;
	wait_all_threads(table);
	while (!simulation_finnished(table))
	{
		if (check_all_philos(table))
			return (NULL);
	}
	return (NULL);
}

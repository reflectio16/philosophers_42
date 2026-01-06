/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:44:12 by meelma            #+#    #+#             */
/*   Updated: 2025/12/10 14:18:28 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	cleanup_simulation(void *data)
{
	int		i;
	t_table	*table;

	i = 0;
	table = (t_table *)data;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks[i].fork);
		i++;
	}
	pthread_mutex_destroy(&table->write_mutex);
	pthread_mutex_destroy(&table->table_mutex);
	free(table->forks);
	free(table->philos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:15:28 by meelma            #+#    #+#             */
/*   Updated: 2025/12/10 14:17:29 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static long	get_elapsed_time(t_table *table)
{
	return ((gettime(MICROSECOND) - table->start_simulation) / 1000);
}

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->table->table_mutex, &philo->full))
		return ;
	safe_mutex_handle(&philo->table->write_mutex, LOCK);
	elapsed = get_elapsed_time(philo->table);
	if (status == DIED)
	{
		printf("%ld %d died\n", elapsed, philo->id);
		safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
		return ;
	}
	if (!simulation_finnished(philo->table))
	{
		if (status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			printf("%ld %d has taken a fork\n", elapsed, philo->id);
		else if (status == EATING)
			printf("%ld %d is eating\n", elapsed, philo->id);
		else if (status == SLEEPING)
			printf("%ld %d is sleeping\n", elapsed, philo->id);
		else if (status == THINKING)
			printf("%ld %d is thinking\n", elapsed, philo->id);
	}
	safe_mutex_handle(&philo->table->write_mutex, UNLOCK);
}

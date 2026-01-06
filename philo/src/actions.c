/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:43:39 by meelma            #+#    #+#             */
/*   Updated: 2025/12/10 14:04:21 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_eat(t_philo *philo)
{
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	safe_mutex_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->table->table_mutex, &philo->last_meal_time,
		gettime(MICROSECOND));
	safe_mutex_handle(&philo->table->table_mutex, LOCK);
	philo->meals_counter++;
	safe_mutex_handle(&philo->table->table_mutex, UNLOCK);
	write_status(EATING, philo);
	custom_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nbr_limit_meals > 0
		&& philo->meals_counter >= philo->table->nbr_limit_meals)
		set_bool(&philo->table->table_mutex, &philo->full, true);
	safe_mutex_handle(&philo->second_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
}

void	philo_sleep(t_philo *philo)
{
	write_status(SLEEPING, philo);
	custom_usleep(philo->table->time_to_sleep, philo->table);
}

void	philo_think(t_philo *philo)
{
	long	think_time;

	write_status(THINKING, philo);
	if (philo->table->philo_nbr % 2 == 1)
	{
		think_time = philo->table->time_to_eat * 2
			- philo->table->time_to_sleep;
		if (think_time > 0)
			custom_usleep(think_time, philo->table);
	}
}

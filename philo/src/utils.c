/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:47:50 by meelma            #+#    #+#             */
/*   Updated: 2025/12/10 14:24:59 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void	*safe_malloc(size_t bytes)
{
	void	*new;

	new = malloc(bytes);
	if (new == NULL)
		error_exit("Error with the malloc!");
	return (new);
}

void	*single_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_finnished(philo->table))
		usleep(100);
	return (NULL);
}

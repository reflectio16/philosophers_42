/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:47:35 by meelma            #+#    #+#             */
/*   Updated: 2025/12/10 14:14:47 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
		;
}

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit ("Wrong input to gettime");
	return (-1);
}

void	custom_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remain;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finnished(table))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		remain = usec - elapsed;
		if (remain > 1e3)
			usleep(remain / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

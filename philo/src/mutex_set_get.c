/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_set_get.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:19:53 by meelma            #+#    #+#             */
/*   Updated: 2025/12/10 14:21:26 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool *value)
{
	bool	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

long	get_long(t_mtx *mutex, long *value)
{
	long	ret;

	safe_mutex_handle(mutex, LOCK);
	ret = *value;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	safe_mutex_handle(mutex, LOCK);
	*dest = value;
	safe_mutex_handle(mutex, UNLOCK);
}

bool	simulation_finnished(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_simulation));
}

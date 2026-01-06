/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:06:33 by meelma            #+#    #+#             */
/*   Updated: 2025/12/10 14:08:52 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	handle_mutex_error(int status, t_optype optype)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (optype == LOCK || optype == UNLOCK))
		error_exit("The value specified by mutex is invalid");
	else if (status == EINVAL && (optype == INIT))
		error_exit("The value specified by attr is invalid");
	else if (status == EINVAL && (optype == DESTROY))
		error_exit("The mutex is not initialized or is already destroyed");
	else if (status == EDEADLK)
		error_exit("A deadlock occur if the thread blocked waiting for mutex");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		error_exit("Insufficient memory exists to initialize the mutex");
	else if (status == EBUSY)
		error_exit("Mutex is locked");
}

void	safe_mutex_handle(t_mtx *mutex, t_optype optype)
{
	if (optype == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), optype);
	else if (optype == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), optype);
	else if (optype == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), optype);
	else if (optype == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), optype);
	else
		error_exit("Wrong optype for mutex handle!");
}

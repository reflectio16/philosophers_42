/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 14:22:22 by meelma            #+#    #+#             */
/*   Updated: 2025/12/10 14:24:17 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	handle_thread_error(int status, t_optype optype)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("Not enough system resources to create another thread");
	else if (status == EPERM)
		error_exit("No permission to set certain scheduling parameters\n");
	else if (status == EINVAL && (optype == CREATE))
		error_exit("Invalid thread attributes\n");
	else if (status == EINVAL && (optype == JOIN || optype == DETACH))
		error_exit("The value specified by thread is not joinable\n");
	else if (status == ESRCH)
		error_exit("No thread with that ID exists\n");
	else if (status == EDEADLK)
		error_exit("Deadlock detected (joining self or circular wait)");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_optype optype)
{
	if (optype == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), optype);
	else if (optype == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), optype);
	else if (optype == DETACH)
		handle_thread_error(pthread_detach(*thread), optype);
	else
		error_exit("Wrong optype for thread handle!");
}

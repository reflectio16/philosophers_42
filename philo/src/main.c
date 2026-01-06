/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 15:44:50 by meelma            #+#    #+#             */
/*   Updated: 2025/12/09 17:24:10 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (parse_input(&table, av))
		{
			printf("Invalid input\n");
			return (1);
		}
		init_data(&table);
		start_dinner(&table);
		cleanup_simulation(&table);
	}
	else
	{
		printf("Invalid input\n");
		return (1);
	}
	return (0);
}

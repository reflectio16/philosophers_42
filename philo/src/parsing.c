/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meelma <meelma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 17:21:19 by meelma            #+#    #+#             */
/*   Updated: 2025/12/10 14:09:30 by meelma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	check_valid_input(const char *str)
{
	int	len;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		return (1);
	if (!is_digit(*str))
		return (1);
	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (*str != '\0' || len > 10)
		return (1);
	return (0);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	while (is_digit(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num);
}

int	parse_input(t_table *table, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_valid_input(av[i]))
			return (1);
		if (ft_atol(av[i]) > INT_MAX)
			return (1);
		i++;
	}
	table->philo_nbr = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	if (av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
	if (table->philo_nbr == 0)
		return (1);
	return (0);
}

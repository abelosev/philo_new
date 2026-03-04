/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:24:10 by anbelose          #+#    #+#             */
/*   Updated: 2026/02/25 19:24:18 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	check_nbr(const char *str, long *res)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		return (false);
	if (str[i] == '0' && str[i + 1])
		return (false);
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (false);
		*res = *res * 10 + str[i] - '0';
		if (*res > 2147483647 || *res < 0)
			return (false);
		i++;
	}
	return (true);
}

bool	check_input(int ac, char **av)
{
	int	i;
	long	res;

	i = 1;
	res = 0;
	if (ac < 5 || ac > 6)
	{
		printf("The number of args is not correct\n");
		return (false);
	}
	while (i < ac)
	{
		if (!check_nbr(av[i], &res) || (i == 1 && res > 200)
			|| res == 0 || (i >= 2 && i <= 4 && res < 60))
		{
			printf("At least one of the args is not correct\n");
			return (false);
		}
		res = 0;
		i++;
	}
	return (true);
}

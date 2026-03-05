/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:25:37 by anbelose          #+#    #+#             */
/*   Updated: 2026/03/05 02:36:01 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	one_philo(t_philo *ph)
// {
// 	if (ph->data->philo_nb != 1)
// 		return (0);
// 	pthread_mutex_lock(&ph->data->fork[0]);
// 	ft_print(ph, 0);
// 	ft_usleep(ph, ph->data->time_die);
// 	pthread_mutex_unlock(&ph->data->fork[0]);
// 	end_simul(ph);
// 	return (1);
// }

// int	create_gap(t_philo *ph)
// {
// 	if (ph->data->philo_nb % 2 == 0)
// 	{
// 		if (ph->id % 2 == 0)
// 			return (ft_usleep(ph, ph->data->time_eat / 2));
// 	}
// 	else
// 	{
// 		if (ph->id % 3 == 2)
// 			return (ft_usleep(ph, ph->data->time_eat / 2));
// 		else if (ph->id % 3 == 0)
// 			return (ft_usleep(ph, ph->data->time_eat));
// 	}
// 	return (0);
// }

// int	think_pause(t_philo *ph)
// {
// 	unsigned long long	think_time;

// 	if (ph->data->philo_nb % 2 == 0)
// 		return (0);
// 	if (ph->data->time_eat * 2 <= ph->data->time_sleep)
// 		return (ft_usleep(ph, 1));
// 	think_time = ph->data->time_eat * 2 - ph->data->time_sleep;
// 	return (ft_usleep(ph, think_time));
// }

// int	philo_loop(t_philo *ph, int l_index, int r_index)
// {
// 	while (1)
// 	{
// 		if (eating(ph, l_index, r_index))
// 			return (1);
// 		if (ft_print(ph, 2))
// 			return (1);
// 		if (ft_usleep(ph, ph->data->time_sleep))
// 			return (1);
// 		if (ft_print(ph, 3))
// 			return (1);
// 		if (think_pause(ph))
// 			return (1);
// 	}
// 	return (0);
// }

// void	*routine(void *arg)
// {
// 	t_philo	*ph;
// 	int		l_index;
// 	int		r_index;

// 	ph = (t_philo *)arg;
// 	if (one_philo(ph))
// 		return ((void *)ph);
// 	l_index = ph->id - 1;
// 	r_index = ph->id % ph->data->philo_nb;
// 	if (create_gap(ph))
// 		return ((void *)ph);
// 	philo_loop(ph, l_index, r_index);
// 	return ((void *)ph);
// }

#include "philo.h"

int	one_philo(t_philo *ph)
{
	if (ph->data->philo_nb != 1)
		return (0);
	pthread_mutex_lock(&ph->data->fork[0]);
	ft_print(ph, 0);
	ft_usleep(ph, ph->data->time_die);
	pthread_mutex_unlock(&ph->data->fork[0]);
	end_simul(ph);
	return (1);
}

int	create_gap(t_philo *ph)
{
	if (ph->id % 2 == 0)
		return (ft_usleep(ph, ph->data->time_eat / 2));
	if (ph->data->philo_nb % 2 != 0 && ph->id == ph->data->philo_nb)
		return (ft_usleep(ph, ph->data->time_eat));
	return (0);
}

static int	think_pause(t_philo *ph)
{
	if (ph->data->philo_nb % 2 == 0)
		return (0);
	if (ph->data->time_eat * 2 <= ph->data->time_sleep)
		return (0);
	return (ft_usleep(ph, ph->data->time_eat * 2
			- ph->data->time_sleep));
}

static int	philo_loop(t_philo *ph, int l_index, int r_index)
{
	while (1)
	{
		if (eating(ph, l_index, r_index))
			return (1);
		if (ft_print(ph, 2))
			return (1);
		if (ft_usleep(ph, ph->data->time_sleep))
			return (1);
		if (ft_print(ph, 3))
			return (1);
		if (think_pause(ph))
			return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (one_philo(ph))
		return ((void *)ph);
	if (create_gap(ph))
		return ((void *)ph);
	philo_loop(ph, ph->id - 1, ph->id % ph->data->philo_nb);
	return ((void *)ph);
}

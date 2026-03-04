/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:59:11 by anbelose          #+#    #+#             */
/*   Updated: 2026/02/25 17:59:16 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taking_fork(t_philo *ph, int f_index)
{
	pthread_mutex_lock(&ph->data->fork[f_index]);
	if (ft_print(ph, 0))
	{
		pthread_mutex_unlock(&ph->data->fork[f_index]);
		return (1);
	}
	return (0);
}

static int	eat_and_wait(t_philo *ph, int l_index, int r_index)
{
	ph->had_meals++;
	pthread_mutex_lock(&ph->data->full);
	if (ph->had_meals == ph->data->meal_nb)
		ph->data->nb_full++;
	pthread_mutex_unlock(&ph->data->full);
	if (ft_usleep(ph, ph->data->time_eat))
	{
		pthread_mutex_unlock(&ph->data->fork[r_index]);
		pthread_mutex_unlock(&ph->data->fork[l_index]);
		return (1);
	}
	pthread_mutex_unlock(&ph->data->fork[r_index]);
	pthread_mutex_unlock(&ph->data->fork[l_index]);
	return (0);
}

int	forks_taken(t_philo *ph, int l_index, int r_index)
{
	int	status;

	pthread_mutex_lock(&ph->data->dead);
	ph->start_meal = get_timestamp();
	pthread_mutex_unlock(&ph->data->dead);
	if (ft_print(ph, 1))
	{
		pthread_mutex_unlock(&ph->data->fork[r_index]);
		pthread_mutex_unlock(&ph->data->fork[l_index]);
		return (1);
	}
	if (eat_and_wait(ph, l_index, r_index))
		return (1);
	status = end_simul(ph);
	if (status == 3)
		death_log(ph);
	if (status != 0)
		return (1);
	return (0);
}

int	eating(t_philo *ph, int l_index, int r_index)
{
	if (ph->id % 2 != 0)
	{
		if (taking_fork(ph, r_index))
			return (1);
		if (taking_fork(ph, l_index))
		{
			pthread_mutex_unlock(&ph->data->fork[r_index]);
			return (1);
		}
	}
	else
	{
		if (taking_fork(ph, l_index))
			return (1);
		if (taking_fork(ph, r_index))
		{
			pthread_mutex_unlock(&ph->data->fork[l_index]);
			return (1);
		}
	}
	if (forks_taken(ph, l_index, r_index))
		return (1);
	return (0);
}

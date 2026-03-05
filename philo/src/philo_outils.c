/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 03:07:26 by anbelose          #+#    #+#             */
/*   Updated: 2026/03/05 03:07:27 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_simul(t_philo *ph)
{
	int	res;

	pthread_mutex_lock(&ph->data->dead);
	if (ph->data->flag_death)
		res = 1;
	else
		res = 0;
	pthread_mutex_unlock(&ph->data->dead);
	if (res != 0)
		return (res);
	pthread_mutex_lock(&ph->data->full);
	if (ph->data->meal_nb != 0
		&& ph->data->nb_full == ph->data->philo_nb)
		res = 2;
	pthread_mutex_unlock(&ph->data->full);
	return (res);
}

int	ft_usleep(t_philo *ph, unsigned long long gap)
{
	unsigned long long	start;
	int					status;

	start = get_timestamp();
	while (get_timestamp() - start < gap)
	{
		status = end_simul(ph);
		if (status != 0)
			return (1);
		usleep(100);
	}
	return (0);
}

static int	check_death(t_data *data)
{
	t_philo	*tmp;

	tmp = data->philos;
	while (tmp)
	{
		pthread_mutex_lock(&data->dead);
		if (get_timestamp() - tmp->start_meal
			>= (unsigned long long)data->time_die)
		{
			data->flag_death = true;
			pthread_mutex_unlock(&data->dead);
			death_log(tmp);
			return (1);
		}
		pthread_mutex_unlock(&data->dead);
		tmp = tmp->next;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data))
			return (NULL);
		pthread_mutex_lock(&data->full);
		if (data->meal_nb != 0
			&& data->nb_full == data->philo_nb)
		{
			pthread_mutex_unlock(&data->full);
			return (NULL);
		}
		pthread_mutex_unlock(&data->full);
		usleep(1000);
	}
	return (NULL);
}

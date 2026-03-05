/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:25:11 by anbelose          #+#    #+#             */
/*   Updated: 2026/03/04 21:47:53 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_philos(t_data *data)
{
	t_philo	*tmp;

	tmp = data->philos;
	while (tmp)
	{
		if (get_timestamp() - tmp->start_meal
			>= (unsigned long long)data->time_die)
		{
			data->flag_death = true;
			pthread_mutex_unlock(&data->full);
			pthread_mutex_unlock(&data->dead);
			death_log(tmp);
			return (3);
		}
		tmp = tmp->next;
	}
	if (data->meal_nb != 0 && data->nb_full == data->philo_nb)
		return (2);
	return (0);
}

int	end_simul(t_philo *ph)
{
	int	res;

	pthread_mutex_lock(&ph->data->dead);
	pthread_mutex_lock(&ph->data->full);
	if (ph->data->flag_death)
		res = 1;
	else
		res = check_all_philos(ph->data);
	if (res != 3)
	{
		pthread_mutex_unlock(&ph->data->full);
		pthread_mutex_unlock(&ph->data->dead);
	}
	return (res);
}


// int	ft_usleep(t_philo *ph, unsigned long long gap)
// {
// 	unsigned long long	start;
// 	int					status;

// 	start = get_timestamp();
// 	while (get_timestamp() - start < gap)
// 	{
// 		status = end_simul(ph);
// 		if (status != 0)
// 			return (1);
// 		usleep(100);
// 	}
// 	return (0);
// }

int	ft_usleep(t_philo *ph, unsigned long long gap)
{
	unsigned long long	start;
	int					status;
	int					sleep_time;

	if (ph->data->philo_nb > 100)
		sleep_time = 500;
	else
		sleep_time = 100;
	start = get_timestamp();
	while (get_timestamp() - start < gap)
	{
		status = end_simul(ph);
		if (status != 0)
			return (1);
		usleep(sleep_time);
	}
	return (0);
}
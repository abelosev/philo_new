/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:25:37 by anbelose          #+#    #+#             */
/*   Updated: 2026/02/25 19:25:45 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int one_philo(t_philo *ph)
{
    if (ph->data->philo_nb != 1)
        return (0);
    ph->start_meal = ph->data->start_simul;
    pthread_mutex_lock(&ph->data->fork[0]);
    ft_print(ph, 0);
    ft_usleep(ph, ph->data->time_die);
    pthread_mutex_unlock(&ph->data->fork[0]);
	death_log(ph);
    return (1);
}

void	forks_index(t_philo *ph, int *l_index, int *r_index)
{
	*l_index = ph->id - 1;
	*r_index = ph->id % ph->data->philo_nb;
}

void	create_gap(t_philo *ph)
{
	if (ph->data->philo_nb % 2 == 0)
	{
		if (ph->id % 2 == 0)
			//usleep(30 * 1000);
			usleep(ph->data->time_eat * 500);
	}
	else if (ph->data->philo_nb % 2 == 1)
	{
		if (ph->id % 3 == 2)
			//usleep(30 * 1000);
			usleep(ph->data->time_eat * 500);
		else if (ph->id % 3 == 0)
			//usleep(60 * 1000);
			usleep(ph->data->time_eat * 1000);
	}
}

void	*routine(void *arg)
{
	t_philo	*ph;
	int		l_index;
	int		r_index;

	ph = (t_philo *)arg;
	if (one_philo(ph))
		return ((void *)ph);
	ph->start_meal = ph->data->start_simul;
	forks_index(ph, &l_index, &r_index);
	create_gap(ph);
	while (1)
	{
		if (eating(ph, l_index, r_index))
			break ;
		ft_print(ph, 2);
		if (ft_usleep(ph, (ph->data->time_sleep)))
			break ;
		ft_print(ph, 3);
		if (ph->data->philo_nb % 2 == 1
			&& ft_usleep(ph, (ph->data->time_eat / 2)))
			break ;
	}
	return ((void *)ph);
}

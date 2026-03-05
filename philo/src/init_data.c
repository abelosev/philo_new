/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 03:06:50 by anbelose          #+#    #+#             */
/*   Updated: 2026/03/05 03:06:52 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_data *data, char **av)
{
	data->philo_nb = ft_atoi_modif(av[1]);
	data->time_die = ft_atoi_modif(av[2]);
	data->time_eat = ft_atoi_modif(av[3]);
	data->time_sleep = ft_atoi_modif(av[4]);
	if (av[5])
		data->meal_nb = ft_atoi_modif(av[5]);
	else
		data->meal_nb = 0;
}

int	init_logs(t_data *data)
{
	data->logs = malloc(sizeof(char *) * 7);
	if (!data->logs)
		return (1);
	data->logs[0] = ft_strdup("has taken a fork");
	data->logs[1] = ft_strdup("is eating");
	data->logs[2] = ft_strdup("is sleeping");
	data->logs[3] = ft_strdup("is thinking");
	data->logs[4] = ft_strdup("died");
	data->logs[5] = ft_strdup("All philosophers are full");
	data->logs[6] = NULL;
	if (!data->logs[0] || !data->logs[1] || !data->logs[2]
		|| !data->logs[3] || !data->logs[4] || !data->logs[5])
		return (free_tab(data->logs), 1);
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->full, NULL);
	pthread_mutex_init(&data->dead, NULL);
	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->fork)
		return (1);
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **av)
{
	init_args(data, av);
	data->flag_death = false;
	data->nb_full = 0;
	data->start_simul = 0;
	data->philos = NULL;
	data->fork = NULL;
	data->logs = NULL;
	if (init_mutexes(data))
		return (1);
	if (init_logs(data))
		return (1);
	return (0);
}

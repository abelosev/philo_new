/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:59:27 by anbelose          #+#    #+#             */
/*   Updated: 2026/02/25 17:59:34 by anbelose         ###   ########.fr       */
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
	data->logs[0] = ft_strdup("has taken a fork\n");
	data->logs[1] = ft_strdup("is eating\n");
	data->logs[2] = ft_strdup("is sleeping\n");
	data->logs[3] = ft_strdup("is thinking\n");
	data->logs[4] = ft_strdup("died\n");
	data->logs[5] = ft_strdup("All philosophers are full\n");
	data->logs[6] = NULL;
	return (0);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->philo_nb);
	if (!data->fork)
		return (1);
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->full, NULL);
	pthread_mutex_init(&data->dead, NULL);
	return (0);
}

int	init_data(t_data *data, char **av)
{
	init_args(data, av);
	data->flag_death = false;
	data->nb_full = 0;
	data->start_simul = get_timestamp();
	if (init_logs(data))
		return (1);
	if (init_mutexes(data))
		return (1);
	return (0);
}

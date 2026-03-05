/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:59:43 by anbelose          #+#    #+#             */
/*   Updated: 2026/02/25 17:59:48 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_data(t_data *data, char **av)
{
	if (init_data(data, av))
	{
		free_data(data);
		return (1);
	}
	data->philos = philo_list(data);
	if (!data->philos)
	{
		free_data(data);
		return (1);
	}
	if (start_threads(data))
	{
		free_data(data);
		return (1);
	}
	return (0);
}

static void	join_philos(t_data *data)
{
	t_philo	*start;

	start = data->philos;
	while (start != NULL)
	{
		pthread_join(start->th, NULL);
		start = start->next;
	}
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!check_input(ac, av))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data || get_data(data, av))
		return (1);
	if (pthread_create(&data->monitor_th, NULL, monitor, (void *)data) != 0)
	{
		free_data(data);
		return (1);
	}
	pthread_join(data->monitor_th, NULL);
	join_philos(data);
	if (data->meal_nb != 0 && data->nb_full == data->philo_nb)
		full_log(data->philos);
	free_data(data);
	return (0);
}
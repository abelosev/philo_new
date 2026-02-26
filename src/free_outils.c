/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_outils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:24:31 by anbelose          #+#    #+#             */
/*   Updated: 2026/02/25 19:24:37 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_list(t_philo *list)
{
	t_philo	*tmp;

	while (list != NULL)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->philos)
		free_list(data->philos);
	if (data->logs)
		free_tab(data->logs);
	pthread_mutex_destroy(&(data->print));
	pthread_mutex_destroy(&(data->full));
	pthread_mutex_destroy(&(data->dead));
	if (data->fork)
	{
		while (i < data->philo_nb)
		{
			pthread_mutex_destroy(&data->fork[i]);
			i++;
		}
	}
	free(data->fork);
	free(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:25:25 by anbelose          #+#    #+#             */
/*   Updated: 2026/02/25 19:25:31 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_log(t_philo *ph)
{
	u_int64_t	time_ms;

	pthread_mutex_lock(&ph->data->print);
	time_ms = get_timestamp() - ph->data->start_simul;
	printf("%lu %d %s\n", time_ms, ph->id, ph->data->logs[4]);
	pthread_mutex_unlock(&ph->data->print);
}

void	full_log(t_philo *ph)
{
	u_int64_t	time_ms;

	pthread_mutex_lock(&ph->data->print);
	time_ms = get_timestamp() - ph->data->start_simul;
	printf("%lu %s\n", time_ms, ph->data->logs[5]);
	pthread_mutex_unlock(&ph->data->print);
}

int	ft_print(t_philo *ph, int index)
{
	u_int64_t	time_ms;

	if (end_simul(ph) != 0)
		return (1);
	pthread_mutex_lock(&ph->data->print);
	time_ms = get_timestamp() - ph->data->start_simul;
	printf("%lu %d %s\n", time_ms, ph->id, ph->data->logs[index]);
	pthread_mutex_unlock(&ph->data->print);
	return (0);
}

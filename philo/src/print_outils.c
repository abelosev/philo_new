/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_outils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 19:25:25 by anbelose          #+#    #+#             */
/*   Updated: 2026/03/04 21:50:28 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_log(t_philo *ph)
{
	u_int64_t	time_ms;

	pthread_mutex_lock(&ph->data->print);
	time_ms = get_timestamp() - ph->data->start_simul;
	printf("%llu %d %s\n", time_ms, ph->id, ph->data->logs[4]);
	pthread_mutex_unlock(&ph->data->print);
}

void	full_log(t_philo *ph)
{
	u_int64_t	time_ms;

	pthread_mutex_lock(&ph->data->print);
	time_ms = get_timestamp() - ph->data->start_simul;
	printf("%llu %s\n", time_ms, ph->data->logs[5]);
	pthread_mutex_unlock(&ph->data->print);
}

int	ft_print(t_philo *ph, int index)
{
	u_int64_t	time_ms;
	int			status;

	status = end_simul(ph);
	if (status == 3)
		death_log(ph);
	if (status != 0)
		return (1);
	pthread_mutex_lock(&ph->data->print);
	pthread_mutex_lock(&ph->data->dead);
	if (ph->data->flag_death)
	{
		pthread_mutex_unlock(&ph->data->dead);
		pthread_mutex_unlock(&ph->data->print);
		return (1);
	}
	pthread_mutex_unlock(&ph->data->dead);
	time_ms = get_timestamp() - ph->data->start_simul;
	printf("%llu %d %s\n", time_ms, ph->id, ph->data->logs[index]);
	pthread_mutex_unlock(&ph->data->print);
	return (0);
}

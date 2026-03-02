/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anbelose <anbelose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 17:57:13 by anbelose          #+#    #+#             */
/*   Updated: 2026/02/25 17:57:24 by anbelose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct s_philo
{
	int				id;
	int				had_meals;
	pthread_t		th;
	u_int64_t		start_meal;
	struct s_data	*data;
	struct s_philo	*next;
}	t_philo;

typedef struct s_data
{
	int				philo_nb;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meal_nb;
	int				nb_full;
	u_int64_t		start_simul;
	t_philo			*philos;
	bool			flag_death;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	full;
	pthread_mutex_t	dead;
	char			**logs;
}	t_data;

int			ft_atoi_modif(const char *str);
int			ft_usleep(t_philo *ph, u_int64_t gap);
int			init_data(t_data *data, char **av);
int			end_simul(t_philo *ph);
int			ft_print(t_philo *ph, int index);
int			eating(t_philo *ph, int l_index, int r_index);
void		free_list(t_philo *list);
void		free_data(t_data *data);
bool		check_nbr(const char *str, int *res);
bool		check_input(int ac, char **av);
char		*ft_strdup(const char *s1);
void		*routine(void *arg);
void		death_log(t_philo *ph);
void		full_log(t_philo *ph);
u_int64_t	get_timestamp(void);
t_philo		*philo_list(t_data *data);
t_philo		*philo_list(t_data *data);

#endif

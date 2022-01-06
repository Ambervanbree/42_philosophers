/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 09:40:26 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/06 15:34:47 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_philo;

typedef struct s_data
{
	int				nr_philo;
	int				die_time;
	int				eat_time;
	int				zzz_time;
	int				philo_died;
	int				nr_meals;
	int				ate_enough;
	long			start_time;
	struct s_philo	*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	still_alive;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				last_meal;
	int				nr_meals;
	int				just_ate;
	int				just_slept;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

int		ft_atoi(const char *str);
int		create_threads(t_data *data);
int		timestamp(t_data *data);
int		philo_is_eating(t_philo *philo);
int		philo_is_sleeping(t_philo *philo);
int		philo_is_thinking(t_philo *philo);
int		your_time_is_up(t_philo *philo);
void	controlled_sleep(t_data *data, int code);

#endif
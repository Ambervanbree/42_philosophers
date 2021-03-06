/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:08:06 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/13 15:01:37 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5
# define LOCK 6
# define UNLOCK 7
# define ADD 8
# define CHECK 9

struct	s_philo;

typedef struct s_data
{
	int				nr_philo;
	int				die_time;
	int				eat_time;
	int				zzz_time;
	int				max_meals;
	long			start_time;
	int				ate_enough;
	int				its_over;
	struct s_philo	*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	time_up;
	pthread_mutex_t	full;
	pthread_mutex_t	dead;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				nr_meals;
	int				just_ate;
	int				just_slept;
	pthread_t		philo;
	t_data			*data;
}	t_philo;

int		ft_atoi_philo(const char *str);
void	ft_putstr_fd(char *string, int fd);
int		ft_strlen(char *string);
int		lonely_philosopher(t_data *data);
void	express_yourself(t_philo *philo, int status);
long	timestamp(void);
void	controlled_sleep(int time_ms);
int		your_time_is_up(t_philo *philo);
void	exit_function(t_data *data);
int		create_threads(t_data *data);
int		philo_is_thinking(t_philo *philo);
int		philo_is_sleeping(t_philo *philo);
int		philo_is_eating(t_philo *philo);
int		philo_ate_enough(t_data *data, int code);
void	fork_mutexes(t_philo *philom, int code);
int		philo_died(t_data *data, int code);
void	philo_dies(t_philo *philo);

#endif
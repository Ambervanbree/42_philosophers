/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 09:40:26 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/04 18:07:02 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

struct	s_philo;

typedef struct	s_data
{
	int				nr_philo;
	int				die_time;
	int				eat_time;
	int				zzz_time;
	int				nr_eat;
	int				fork[512];
	struct s_philo	*philo;
}	t_data;

typedef struct	s_philo
{
	int			id;
	pthread_t	thread;
	t_data		*data;
}	t_philo;

int		ft_atoi(const char *str);
int		create_threads(t_data *data);

#endif
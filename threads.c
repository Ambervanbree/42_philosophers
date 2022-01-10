/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:27:05 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/10 14:58:30 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	first_round(t_philo *philo)
{
	if (philo->id % 2 && philo->id != philo->data->nr_philo)
		philo_is_eating(philo);
	else
		philo_is_thinking(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	first_round(philo);
	while (1)
	{
		if (philo->just_ate)
		{
			if (philo_is_sleeping(philo) == 0)
				break ;
		}
		else if (philo->just_slept)
		{
			if (philo_is_thinking(philo) == 0)
				break ;
		}
		else
		{
			if (philo_is_eating(philo) == 0)
				break ;
		}
	}
	return (0);
}

int	create_threads(t_data *data)
{
	int			i;

	i = -1;
	while (++i < data->nr_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &philo_routine,
				(void *)&data->philo[i]) != 0)
		{
			perror("failed to create thread");
			return (0);
		}
	}
	i = -1;
	while (++i < data->nr_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			perror("failed to join thread");
			return (0);
		}
	}
	return (1);
}

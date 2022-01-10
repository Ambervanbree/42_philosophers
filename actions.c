/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:42:25 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/10 16:46:40 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	lock_mutexes(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->fork[philo->id - 1]) != 0)
	{
		perror("mutex lock failed");
		return (0);
	}
	if (philo->id == philo->data->nr_philo)
	{
		if (pthread_mutex_lock(&philo->data->fork[0]) != 0)
		{
			perror("mutex lock failed");
			pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
			return (0);
		}
	}
	else
	{
		if (pthread_mutex_lock(&philo->data->fork[philo->id]) != 0)
		{
			perror("mutex lock failed");
			pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
			return (0);
		}
	}
	return (1);
}

void	unlock_mutexes(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
	if (philo->id == philo->data->nr_philo)
		pthread_mutex_unlock(&philo->data->fork[0]);
	else
		pthread_mutex_unlock(&philo->data->fork[philo->id]);
}

int	philo_is_eating(t_philo *philo)
{
	if (lock_mutexes(philo) == 0)
		return (0);
	if (your_time_is_up(philo))
	{
		unlock_mutexes(philo);
		return (0);
	}
	printf("%d Philo %d has taken a fork\n", timestamp(philo->data), philo->id);
	printf("%d Philo %d is eating\n", timestamp(philo->data), philo->id);
	philo->last_meal = timestamp(philo->data);
	controlled_sleep(philo, philo->data->eat_time);
	philo->just_ate = 1;
	philo->nr_meals++;
	if (philo->nr_meals == philo->data->nr_meals)
		increment_meals(philo->data);
	unlock_mutexes(philo);
	return (1);
}

int	philo_is_sleeping(t_philo *philo)
{
	if (your_time_is_up(philo))
		return (0);
	printf("%d Philo %d is sleeping\n", timestamp(philo->data), philo->id);
	controlled_sleep(philo, philo->data->zzz_time);
	philo->just_slept = 1;
	philo->just_ate = 0;
	return (1);
}

int	philo_is_thinking(t_philo *philo)
{
	if (your_time_is_up(philo))
		return (0);
	printf("%d Philo %d is thinking\n", timestamp(philo->data), philo->id);
	philo->just_slept = 0;
	return (1);
}

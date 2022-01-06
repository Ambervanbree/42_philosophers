/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:42:25 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/06 18:27:58 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_mutexes(t_philo *philo)
{
	if (pthread_mutex_lock(&philo->data->fork[philo->id - 1]) != 0)
		perror("mutex lock failed");
//	printf("Philo %d took fork %d\n", philo->id, philo->id - 1);
	if (philo->id == philo->data->nr_philo)
	{
		if (pthread_mutex_lock(&philo->data->fork[0]) != 0)
			perror("mutex lock failed");
//		printf("Philo %d took fork %d\n", philo->id, 0);
	}
	else
	{
		if (pthread_mutex_lock(&philo->data->fork[philo->id]) != 0)
			perror("mutex lock failed");
//		printf("Philo %d took fork %d\n", philo->id, philo->id);
	}
}

void	unlock_mutexes(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->data->fork[philo->id - 1]));
//	printf("Philo %d dropped fork %d\n", philo->id, philo->id - 1);
	if (philo->id == philo->data->nr_philo)
	{
		pthread_mutex_unlock(&philo->data->fork[0]);
//		printf("Philo %d dropped fork %d\n", philo->id, 0);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[philo->id]);
//		printf("Philo %d dropped fork %d\n", philo->id, philo->id);
	}
}

int	philo_is_eating(t_philo *philo)
{
	if (your_time_is_up(philo))
		return (0);
	lock_mutexes(philo);
	printf("%d Philo %d has taken a fork\n", timestamp(philo->data), philo->id);
	printf("%d Philo %d is eating\n", timestamp(philo->data), philo->id);
	controlled_sleep(philo->data, 2);
	philo->just_ate = 1;
	philo->nr_meals++;
	philo->last_meal = timestamp(philo->data);
	if (philo->nr_meals == philo->data->nr_meals)
		philo->data->ate_enough++;
	unlock_mutexes(philo);
	return (1);
}

int	philo_is_sleeping(t_philo *philo)
{
	if (your_time_is_up(philo))
		return (0);
	printf("%d Philo %d is sleeping\n", timestamp(philo->data), philo->id);
	controlled_sleep(philo->data, 1);
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

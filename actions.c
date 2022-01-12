/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:27:09 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/12 09:54:15 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_is_eating(t_philo *philo)
{
	fork_mutexes(philo, LOCK);
	if (your_time_is_up(philo))
	{
		fork_mutexes(philo, UNLOCK);
		return (0);
	}
	pthread_mutex_lock(&philo->data->butler);
	if (pthread_create(&philo->butler, NULL,
			&butler_routine, (void *)philo) != 0)
	{
		perror("failed to create thread");
		return (0);
	}
	pthread_mutex_unlock(&philo->data->butler);
	nr_meals_philo(philo, ADD);
	express_yourself(philo, EAT);
	controlled_sleep(philo, philo->data->eat_time);
	philo->just_ate = 1;
	if (nr_meals_philo(philo, CHECK) == philo->data->max_meals)
		philo_ate_enough(philo->data, ADD);
	fork_mutexes(philo, UNLOCK);
	return (1);
}

int	philo_is_sleeping(t_philo *philo)
{
	if (your_time_is_up(philo))
		return (0);
	express_yourself(philo, SLEEP);
	controlled_sleep(philo, philo->data->zzz_time);
	philo->just_slept = 1;
	philo->just_ate = 0;
	return (1);
}

int	philo_is_thinking(t_philo *philo)
{
	if (your_time_is_up(philo))
		return (0);
	express_yourself(philo, THINK);
	controlled_sleep(philo, 1);
	philo->just_slept = 0;
	return (1);
}

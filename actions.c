/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:27:09 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/13 14:50:16 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_mutexes(t_philo *philo, int code)
{
	if (code == 6)
	{
		if (philo->id == philo->data->nr_philo)
		{
			pthread_mutex_lock(&philo->data->fork[0]);
			express_yourself(philo, FORK);
		}
		pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
		express_yourself(philo, FORK);
		if (!(philo->id == philo->data->nr_philo))
		{
			pthread_mutex_lock(&philo->data->fork[philo->id]);
			express_yourself(philo, FORK);
		}
	}
	if (code == 7)
	{
		if (!(philo->id == philo->data->nr_philo))
			pthread_mutex_unlock(&philo->data->fork[philo->id]);
		pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
		if (philo->id == philo->data->nr_philo)
			pthread_mutex_unlock(&philo->data->fork[0]);
	}
}

int	your_time_is_up(t_philo *philo)
{
	if (philo_died(philo->data, CHECK))
		return (1);
	if (philo_ate_enough(philo->data, CHECK) == philo->data->nr_philo)
		return (1);
	return (0);
}

int	philo_is_eating(t_philo *philo)
{
	fork_mutexes(philo, LOCK);
	if (your_time_is_up(philo))
	{
		fork_mutexes(philo, UNLOCK);
		return (0);
	}
	express_yourself(philo, EAT);
	philo->nr_meals++;
	controlled_sleep(philo->data->eat_time);
	philo->just_ate = 1;
	if (philo->nr_meals == philo->data->max_meals)
		philo_ate_enough(philo->data, ADD);
	fork_mutexes(philo, UNLOCK);
	return (1);
}

int	philo_is_sleeping(t_philo *philo)
{
	if (your_time_is_up(philo))
		return (0);
	express_yourself(philo, SLEEP);
	controlled_sleep(philo->data->zzz_time);
	philo->just_slept = 1;
	philo->just_ate = 0;
	return (1);
}

int	philo_is_thinking(t_philo *philo)
{
	if (your_time_is_up(philo))
		return (0);
	express_yourself(philo, THINK);
	philo->just_slept = 0;
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 12:23:04 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/12 10:24:43 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*butler_routine(void *arg)
{
	t_philo	*philo;
	int		nr_meals;

	philo = (t_philo *)arg;
	pthread_detach(philo->butler);
	nr_meals = nr_meals_philo(philo, CHECK);
	controlled_sleep(philo, philo->data->die_time);
	if (your_time_is_up(philo))
		return (0);
	if (nr_meals_philo(philo, CHECK) == nr_meals)
	{
		philo_died(philo->data, ADD);
		express_yourself(philo, DIE);
	}
	return (0);
}

int	lonely_philosopher(t_data *data)
{
	express_yourself(&data->philo[0], THINK);
	express_yourself(&data->philo[0], FORK);
	controlled_sleep(&data->philo[0], data->die_time);
	express_yourself(&data->philo[0], DIE);
	exit_function(data);
	return (1);
}

void	first_round(t_philo *philo)
{
	if (philo->id % 2 && philo->id != philo->data->nr_philo)
		philo_is_eating(philo);
	else
	{
		pthread_mutex_lock(&philo->data->butler);
		pthread_create(&philo->butler, NULL, &butler_routine, (void *)philo);
	//	printf("In FR: %p (philo %d)\n", philo->butler, philo->id);
		pthread_mutex_unlock(&philo->data->butler);
		philo_is_thinking(philo);
		controlled_sleep(philo, philo->data->eat_time);
	}
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
		if (pthread_create(&data->philo[i].philo, NULL, &philo_routine,
				(void *)&data->philo[i]) != 0)
		{
			perror("failed to create thread");
			return (0);
		}
	}
	i = -1;
	while (++i < data->nr_philo)
	{
		if (pthread_join(data->philo[i].philo, NULL) != 0)
		{
			perror("failed to join thread");
			return (0);
		}
	}
	return (1);
}

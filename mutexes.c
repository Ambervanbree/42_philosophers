/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:44:51 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/12 10:05:11 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	express_yourself(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->data->speaking);
	if (!your_time_is_up(philo))
	{
		if (status == 1)
			printf("%d %d has taken a fork\n", timestamp(philo->data),
				philo->id);
		if (status == 2)
			printf("%d %d is eating\n", timestamp(philo->data), philo->id);
		if (status == 3)
			printf("%d %d is sleeping\n", timestamp(philo->data), philo->id);
		if (status == 4)
			printf("%d %d is thinking\n", timestamp(philo->data), philo->id);
	}
	if (status == 5)
		printf("%d %d died\n", timestamp(philo->data), philo->id);
	pthread_mutex_unlock(&philo->data->speaking);
}

int	philo_ate_enough(t_data *data, int code)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&data->full);
	if (code == 8)
		data->ate_enough++;
	if (code == 9)
		ret = data->ate_enough;
	pthread_mutex_unlock(&data->full);
	return (ret);
}

int	philo_died(t_data *data, int code)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&data->time_up);
	if (code == 8)
		data->its_over = 1;
	if (code == 9)
		ret = data->its_over;
	pthread_mutex_unlock(&data->time_up);
	return (ret);
}

int	nr_meals_philo(t_philo *philo, int code)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&philo->pers_meals);
	if (code == 8)
		philo->nr_meals++;
	if (code == 9)
		ret = philo->nr_meals;
	pthread_mutex_unlock(&philo->pers_meals);
	return (ret);
}

int	your_time_is_up(t_philo *philo)
{
	if (philo_died(philo->data, CHECK))
		return (1);
	if (philo_ate_enough(philo->data, CHECK) == philo->data->nr_philo)
		return (1);
	return (0);
}

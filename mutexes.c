/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:44:51 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/13 14:50:22 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	express_yourself(t_philo *philo, int status)
{
	long	time;

	time = timestamp() - philo->data->start_time;
	if (status == 5)
	{
		controlled_sleep(10);
		printf("%ld %d died\n", time, philo->id);
	}
	else if (!your_time_is_up(philo))
	{
		if (status == 1)
			printf("%ld %d has taken a fork\n", time, philo->id);
		if (status == 2)
			printf("%ld %d is eating\n", time, philo->id);
		if (status == 3)
			printf("%ld %d is sleeping\n", time, philo->id);
		if (status == 4)
			printf("%ld %d is thinking\n", time, philo->id);
	}
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

void	philo_dies(t_philo *philo)
{
	controlled_sleep(philo->data->die_time);
	if (!your_time_is_up(philo))
	{
		pthread_mutex_lock(&philo->data->dead);
		philo_died(philo->data, ADD);
		express_yourself(philo, DIE);
		pthread_mutex_unlock(&philo->data->dead);
	}
}

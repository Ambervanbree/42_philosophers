/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 10:24:42 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/06 18:26:07 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	long int	i;
	long int	neg;
	long int	ret;

	i = 0;
	neg = 1;
	ret = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = neg * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
		if (neg == 1 && ret > 2147483647)
			return (-1);
		if (neg == -1 && ret > 2147483648)
			return (0);
	}
	return ((int)ret * neg);
}

int	your_time_is_up(t_philo *philo)
{
//	pthread_mutex_lock(&philo->data->still_alive);
	if (philo->data->philo_died)
	{
		printf("somebody is already dead\n");
//		pthread_mutex_unlock(&philo->data->still_alive);
		return (1);
	}
	if (philo->data->ate_enough == philo->data->nr_philo)
	{
		printf("everybody ate enough\n");
//		pthread_mutex_unlock(&philo->data->still_alive);
		return (1);
	}
	printf("philo %d had a last meal %d - %d = %d ms ago\n", philo->id, timestamp(philo->data), philo->last_meal, timestamp(philo->data) - philo->last_meal);
	if ((timestamp(philo->data) - philo->last_meal) > philo->data->die_time
			&& philo->last_meal != 0)
	{
		philo->data->philo_died = 1;
		printf("%d Philo %d died\n", timestamp(philo->data), philo->id);
//		pthread_mutex_unlock(&philo->data->still_alive);
		return (1);
	}
	return (0);
}

int	timestamp(t_data *data)
{
	long			ms;
	int				ret;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	if (data->start_time == 0)
	{
		data->start_time = ms / 10;
		return (0);
	}
	return (ret = ms / 10 - data->start_time);
}

void	controlled_sleep(t_data *data, int code)
{
	int				zzz;
	int				et;

	if (code == 1)
		zzz = data->zzz_time;
	else
		zzz = data->eat_time;
	et = timestamp(data) + zzz;
	while (timestamp(data) < et)
		usleep(100);
}

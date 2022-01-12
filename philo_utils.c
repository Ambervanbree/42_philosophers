/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:48:14 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/12 10:03:45 by avan-bre         ###   ########.fr       */
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

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	timestamp(t_data *data)
{
	long			ms;
	int				ret;
	struct timeval	current_time;

	pthread_mutex_lock(&data->time);
	gettimeofday(&current_time, NULL);
	ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	if (data->start_time == 0)
	{
		data->start_time = ms / 10;
		pthread_mutex_unlock(&data->time);
		return (0);
	}
	pthread_mutex_unlock(&data->time);
	return (ret = ms / 10 - data->start_time);
}

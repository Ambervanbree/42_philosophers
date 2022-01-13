/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:48:14 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/13 15:01:51 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_philo(const char *str)
{
	long int	i;
	long int	neg;
	long int	ret;

	i = 0;
	neg = 1;
	ret = 0;
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
	if (str[i] != 0)
		return (0);
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

long	timestamp(void)
{
	long			ms;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	ms = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (ms);
}

void	controlled_sleep(int time_ms)
{
	long	start;

	start = timestamp();
	while (timestamp() < (start + time_ms))
		usleep(100);
}

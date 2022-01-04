/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:27:05 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/04 18:27:23 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*init_philo(void *arg)
{
	t_philo	*philo;

	*philo = *(t_philo *)arg;
	printf("Philo ID is: %d\n", philo->id);
//	printf("Philo %d is created\n", *(int *)arg);
	return (0);
}

int	create_threads(t_data *data)
{
	pthread_t	philo[512];
	int			i;

	i = -1;
	while (++i < data->nr_philo)
	{
		if (pthread_create(&philo[i], NULL, &init_philo, data->philo + i) != 0)
		{
			perror("failed to creat thread");
			return (0);
		}
	}
	i = -1;
	while (++i < data->nr_philo)
	{
		if (pthread_join(philo[i], NULL) != 0)
		{
			perror("failed to join thread");
			return (0);
		}
		printf("Philo %d is joined\n", i);
	}
	return (1);
}
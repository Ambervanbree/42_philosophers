/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:06:27 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/10 16:36:12 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nr_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
		{
			perror("initialisation mutex failed");
			return (0);
		}
		data->philo[i].nr_meals = 0;
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].last_meal = 0;
		data->philo[i].just_ate = 0;
		data->philo[i].just_slept = 0;
	}
	return (1);
}

int	init_program(t_data *data, char *argv[])
{
	data->nr_philo = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->zzz_time = ft_atoi(argv[4]);
	if (argv[5])
		data->nr_meals = ft_atoi(argv[5]);
	else
		data->nr_meals = -1;
	data->ate_enough = 0;
	data->start_time = 0;
	data->philo_died = 0;
	data->philo = malloc(sizeof(t_philo) * data->nr_philo);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nr_philo);
	if (!data->philo || !data->fork)
	{
		perror("malloc failed");
		return (0);
	}
	pthread_mutex_init(&data->time_up, NULL);
	pthread_mutex_init(&data->meals, NULL);
	if (init_philos(data) == 0)
		return (0);
	return (1);
}

void	finish_program(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->time_up);
	pthread_mutex_init(&data->meals, NULL);
	i = -1;
	while (++i < data->nr_philo)
		pthread_mutex_destroy(&data->fork[i]);
	free(data->fork);
	free(data->philo);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (!(argc == 5 || argc == 6) || ft_atoi(argv[1]) < 1)
	{
		printf("Expected usage: ./philo <nr philo's> <time to death> <eating ");
		printf("time> <sleeping time> optional: <nr of times eating>\n");
		return (1);
	}
	if (init_program(&data, argv) == 0)
		return (1);
	if (ft_atoi(argv[1]) == 1)
	{
		printf("%d Philo 1 has died\n", timestamp(&data));
		free(data.fork);
		free(data.philo);
		return (1);
	}
	if (create_threads(&data) == 0)
	{
		free(data.fork);
		free(data.philo);
		return (1);
	}
	finish_program(&data);
}

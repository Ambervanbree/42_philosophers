/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 10:07:13 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/12 10:33:14 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_function(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->speaking);
	pthread_mutex_destroy(&data->time_up);
	pthread_mutex_destroy(&data->full);
	pthread_mutex_destroy(&data->time);
	pthread_mutex_destroy(&data->butler);
	i = -1;
	while (++i < data->nr_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		pthread_mutex_destroy(&data->philo[i].pers_meals);
	}
	free(data->philo);
	free(data->fork);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nr_philo)
	{
		data->philo[i].nr_meals = 0;
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].last_meal = 0;
		data->philo[i].just_ate = 0;
		data->philo[i].just_slept = 0;
		pthread_mutex_init(&data->fork[i], NULL);
		pthread_mutex_init(&data->philo[i].pers_meals, NULL);
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
		data->max_meals = ft_atoi(argv[5]);
	else
		data->max_meals = -1;
	data->start_time = 0;
	data->ate_enough = 0;
	data->its_over = 0;
	data->philo = malloc(sizeof(t_philo) * data->nr_philo);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nr_philo);
	if (!data->philo || !data->fork)
	{
		perror("malloc failed");
		return (0);
	}
	pthread_mutex_init(&data->speaking, NULL);
	pthread_mutex_init(&data->time_up, NULL);
	pthread_mutex_init(&data->full, NULL);
	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->butler, NULL);
	return (init_philos(data));
}

int	incorrect_usage(int argc, char *argv[])
{
	int	i;

	if (!(argc == 5 || argc == 6))
	{
		ft_putstr_fd("Error, expected usage: ", 2);
		ft_putstr_fd("./philo <nr philo's> <time to death> <eating time>", 2);
		ft_putstr_fd(" <sleeping time> optional: <nr of times eating>\n", 2);
		return (1);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		ft_putstr_fd("Error: Invalid number of philosophers\n", 2);
		return (1);
	}
	i = 1;
	while (argv[++i])
	{
		if ((ft_atoi(argv[i]) == 0 && ft_strlen(argv[i]) > 1)
			|| ft_atoi(argv[i]) < 0)
		{
			ft_putstr_fd("Error: Invalid argument detected\n", 2);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (incorrect_usage(argc, argv))
		return (1);
	if (init_program(&data, argv) == 0)
		return (1);
	if (ft_atoi(argv[1]) == 1)
		return (lonely_philosopher(&data));
	if (create_threads(&data) == 0)
	{
		exit_function(&data);
		return (1);
	}
	controlled_sleep(&data.philo[1], data.die_time * 2);
	exit_function(&data);
	return (0);
}

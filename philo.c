/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:06:27 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/04 18:27:24 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_structure(t_data *data, char *argv[])
{
	int		i;
//	t_philo	philo[data->nr_philo];

	data->nr_philo = ft_atoi(argv[1]);
	data->die_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->zzz_time = ft_atoi(argv[4]);
	if (argv[5])
		data->nr_eat = ft_atoi(argv[5]);
	i = -1;
	while (++i < data->nr_philo)
	{
		data->fork[i] = 0;
	// 	philo[i].id = i + 1;
	// 	philo[i].data = data;
	}
}

int	main(int argc, char *argv[])
{
	t_data	data;
	
	if (!(argc == 5 || argc == 6))
	{
		printf("Expected usage: ./philo <nr philo's> <time to death> <eating ");
		printf("time> <sleeping time> optional: <nr of times eating>\n");
		return (1);
	}
	init_structure(&data, argv);
	create_threads(&data);
}

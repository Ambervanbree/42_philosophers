/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 09:40:54 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/04 12:26:49 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*increment(void* arg)
{
	int	*value;

	value = malloc(sizeof(int));
	if (value == 0)
	{
		perror("malloc failed");
		return (NULL);
	}
	value = (int*) arg;
	printf("Thread input: %d\n", *value);
	*value += 1;
	printf("Thread result: %d\n", *value);
	return ((void *)value);
}

int	main(int argc, char *argv[])
{
	pthread_t	thread[3];
	int			i;
	int			res;

	i = 0;
	printf("argc: %d\n", argc);
	while (i < 3)
	{
		if (pthread_create(&thread[i], NULL, &increment, NULL) != 0)
		{
			perror("failed to create thread");
			return (1);
		}
		i++;
		printf("Thread %d created\n", i);
	}
	i = 0;
	while (i < 3)
	{
		if (pthread_join(thread[i], (void *)&res) != 0)
			return (2);
			i++;
		printf("Thread %d is done\n", i);
	}
	return (0);
}
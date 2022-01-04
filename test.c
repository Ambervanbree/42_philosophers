/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:10:16 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/04 12:30:29 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	*routine(void *arg)
{
	int	*value;

	value = malloc(sizeof(int));
	value = (int *)arg;
	printf("Thread input: %d\n", *value);
	*value += 1;
	printf("Thread result: %d\n", *value);
	return ((void *)value);
}

int	main()
{
	pthread_t	thread[3];
	int			i;
	int			res;

	i = 0;
	while (i < 3)
	{
		if (pthread_create(&thread[i], NULL, &routine, NULL) != 0)
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

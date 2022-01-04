/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:10:16 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/04 17:48:28 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

void	*routine(void *arg)
{
	printf("value is: %d\n", *(int *)arg);
	return (0);
}

int	main()
{
	pthread_t	thread[3];
	int			i;
	int			*a;

	i = 0;
	while (i < 3)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&thread[i], NULL, &routine, a) != 0)
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
		if (pthread_join(thread[i], NULL) != 0)
			return (2);
		i++;
		printf("Thread %d is done\n", i);
	}
	return (0);
}

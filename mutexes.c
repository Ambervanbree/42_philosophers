/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:56:01 by avan-bre          #+#    #+#             */
/*   Updated: 2022/01/10 16:36:16 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increment_meals(t_data *data)
{
	pthread_mutex_lock(&data->meals);
	data->ate_enough++;
	pthread_mutex_unlock(&data->meals);
}

int	check_meals(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->meals);
	ret = data->ate_enough;
	pthread_mutex_unlock(&data->meals);
	return (ret);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_set_ret.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:51:01 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/25 10:31:08 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ret_boolean(t_data *data, bool *set)
{
	bool	val;

	pthread_mutex_lock(&data->bool_lock);
	val = *set;
	pthread_mutex_unlock(&data->bool_lock);
	return (val);
}

void	set_boolean(t_data *data, bool *set, bool val)
{
	pthread_mutex_lock(&data->bool_lock);
	*set = val;
	pthread_mutex_unlock(&data->bool_lock);
}

void	set_long(t_data *data, long *set, long val)
{
	pthread_mutex_lock(&data->bool_lock);
	*set = val;
	pthread_mutex_unlock(&data->bool_lock);
}

long	ret_long(t_data *data, long *set)
{
	long	val;

	pthread_mutex_lock(&data->bool_lock);
	val = *set;
	pthread_mutex_unlock(&data->bool_lock);
	return (val);
}

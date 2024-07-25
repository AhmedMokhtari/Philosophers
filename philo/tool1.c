/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:58:01 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/25 09:03:20 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_now(void)
{
	struct timeval	val;
	long			time;

	gettimeofday(&val, NULL);
	time = (val.tv_sec * 1000) + (val.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long mili, t_data *data)
{
	long	i;

	i = time_now();
	while (time_now() - i < mili)
	{
		if (ret_boolean(data, &data->is_end))
			break ;
		//printf("alo \n");
		usleep(350);
	}
}

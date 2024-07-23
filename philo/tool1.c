/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:58:01 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/23 17:58:22 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(long mili, t_data *data)
{
	long	i;

	i = time_now();
	while (time_now() - i < mili)
	{
		if (ret_boolean(data, &data->is_end))
			break ;
		usleep(1);
	}
}

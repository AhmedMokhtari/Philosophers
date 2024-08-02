/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:52:06 by amokhtar          #+#    #+#             */
/*   Updated: 2024/08/01 11:53:31 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_full(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->nb_philo)
	{
		sem_wait(data->full);
		j++;
	}
	sem_post(data->end);
	return (NULL);
}

void	unlink_sem(void)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("end");
	sem_unlink("all_ready");
	sem_unlink("write");
	sem_unlink("full");
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:58:01 by amokhtar          #+#    #+#             */
/*   Updated: 2024/08/02 10:08:23 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	time_now(void)
{
	struct timeval	val;
	long			time;

	gettimeofday(&val, NULL);
	time = (val.tv_sec * 1000) + (val.tv_usec / 1000);
	return (time);
}

bool	check_dead(t_philo *philo)
{
	long	time;

	time = time_now() - philo->last_meal - philo->data->start_time;
	if (time >= philo->data->time_die)
	{
		sem_wait(philo->data->write);
		print_state(dead, philo);
		exit(42);
	}
	return (false);
}

void	ft_usleep(long mili, t_philo *philo)
{
	long	i;

	i = time_now();
	while (time_now() - i < mili)
	{
		if (!check_dead(philo))
			usleep(500);
	}
}

void	kill_all(t_data *data, int *p)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		kill(p[i], SIGKILL);
		i++;
	}
	free_data(data);
	free(p);
}

void	free_data(t_data *data)
{
	free(data->philo);
	unlink_sem();
	free(data);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:02:31 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/30 19:12:09 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_state(t_state state, t_philo *philo)
{
	long	time_span;

	time_span = time_now() - philo->data->start_time;
	// if (ret_boolean(philo->data, &philo->data->is_end) && state != dead)
	// 	return ;
	// pthread_mutex_lock(&philo->data->write);
	sem_wait(philo->data->write);
	if (state == taking_fork1 && !philo->is_full)
		printf("%ld %d has taken a fork\n", time_span, philo->id);
	else if (state == taking_fork2 && !philo->is_full)
		printf("%ld %d has taken a fork\n", time_span, philo->id);
	else if (state == eating && !philo->is_full)
		printf("%ld %d is eating\n", time_span, philo->id);
	else if (state == sleeping && !philo->is_full)
		printf("%ld %d is sleeping\n", time_span, philo->id);
	else if (state == thinking && !philo->is_full)
		printf("%ld %d is thinking\n", time_span, philo->id);
	else if (state == dead && !philo->is_full)
		printf("%ld %d died\n", time_span, philo->id);
	sem_post(philo->data->write);
}

void	eat(t_philo *philo)
{
	long	start;
	bool	b;

	start = philo->data->start_time;
	print_state(eating, philo);
	ft_usleep(philo->data->time_eat, philo);
	philo->last_meal = time_now() - start;
	philo->meals_eat++;
	b = philo->data->nb_meals != -1;
	if (b && philo->meals_eat == philo->data->nb_meals)
	{
		philo->is_full = true;
		sem_post(philo->data->full);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		exit(0);
	}
}

int	philo_eat(t_philo *philo)
{
	// pthread_mutex_lock(philo->left_fork);
	sem_wait(philo->data->forks);
	print_state(taking_fork1, philo);
	sem_wait(philo->data->forks);
	print_state(taking_fork2, philo);
	eat(philo);
	// if (ret_boolean(philo->data, &philo->data->is_end))
	// {
	// 	pthread_mutex_unlock(philo->left_fork);
	// 	pthread_mutex_unlock(philo->right_fork);
	// 	return (1);
	// }
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return (2);
}

void	sleep_first(t_philo *philo)
{
	print_state(thinking, philo);
	ft_usleep(50, philo);
}

void	*philo_life(t_philo *philo)
{
	int		ret;

	// while (ret_long(philo->data, &philo->data->start_time) == 0)
	// 	;
	// if (ret_boolean(philo->data, &philo->data->is_failed))
	// 	return (NULL);
	if (philo->id % 2 == 0)
		sleep_first(philo);
	while (true)
	{
		// ret = philo_eat(philo);
		philo_eat(philo);
		// if (ret == 0)
		// 	return (NULL);
		// else if (ret == 1)
		// 	break ;
		print_state(sleeping, philo);
		ft_usleep(philo->data->time_sleep, philo);
		// if (philo->data->is_end)
		// 	break ;
		print_state(thinking, philo);
	}
	exit(0);
	return (NULL);
}

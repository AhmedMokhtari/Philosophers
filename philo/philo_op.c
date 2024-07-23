/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:02:31 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/23 18:18:28 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_state(t_state state, t_philo *philo)
{
	long	time_span;

	time_span = time_now() - ret_long(philo->data, &philo->data->start_time);
	if (ret_boolean(philo->data, &philo->data->is_end) && state != dead)
		return ;
	pthread_mutex_lock(&philo->data->write);
	if (state == taking_fork1
		&& !ret_boolean(philo->data, &philo->data->is_end))
		printf("%-4ld %-4d has taken a fork\n", time_span, philo->id);
	else if (state == taking_fork2
		&& !ret_boolean(philo->data, &philo->data->is_end))
		printf("%-4ld %-4d has taken a fork\n", time_span, philo->id);
	else if (state == eating && !ret_boolean(philo->data, &philo->data->is_end))
		printf("%ld %d is eating\n", time_span, philo->id);
	else if (state == sleeping
		&& !ret_boolean(philo->data, &philo->data->is_end))
		printf("%-4ld %-4d is sleeping\n", time_span, philo->id);
	else if (state == thinking
		&& !ret_boolean(philo->data, &philo->data->is_end))
		printf("%-4ld %-4d is thinking\n", time_span, philo->id);
	else if (state == dead)
		printf("%-6ld %-6d dead\n", time_span, philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

void	eat(t_philo *philo)
{
	long	start;
	long	meals_eat;
	bool	b;

	meals_eat = -1;
	start = philo->data->start_time;
	print_state(eating, philo);
	ft_usleep(philo->data->time_eat, philo->data);
	set_long(philo->data, &philo->last_meal, time_now() - start);
	pthread_mutex_lock(&philo->data->bool_lock1);
	philo->meals_eat++;
	pthread_mutex_unlock(&philo->data->bool_lock1);
	b = ret_long(philo->data, &philo->data->nb_meals) != -1;
	if (b)
		meals_eat = ret_long(philo->data, &philo->meals_eat);
	if (b && meals_eat == ret_long(philo->data, &philo->data->nb_meals))
		set_boolean(philo->data, &philo->is_full, true);
}

void	*philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_state(taking_fork1, philo);
	if (philo->data->nb_philo == 1)
		return (pthread_mutex_unlock(philo->left_fork), NULL);
	pthread_mutex_lock(philo->right_fork);
	print_state(taking_fork2, philo);
	eat(philo);
	if (ret_boolean(philo->data, &philo->data->is_end))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ((void *)42);
	}
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (philo);
}

void	*philo_life(void *data)
{
	t_philo	*philo;
	void	*ret;

	philo = (t_philo *)data;
	while (ret_long(philo->data, &philo->data->start_time) == 0)
		;
	if (philo->id % 2 == 0)
		ft_usleep(10, philo->data);
	while (true)
	{
		if (ret_boolean(philo->data, &philo->is_full)
			|| ret_boolean(philo->data, &philo->data->is_end))
			break ;
		ret = philo_eat(philo);
		if (!ret)
			return (NULL);
		else if (ret == (void *)42)
			break ;
		print_state(sleeping, philo);
		ft_usleep(philo->data->time_sleep, philo->data);
		if (ret_boolean(philo->data, &philo->data->is_end))
			break ;
		print_state(thinking, philo);
	}
	return (NULL);
}

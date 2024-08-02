/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:02:31 by amokhtar          #+#    #+#             */
/*   Updated: 2024/08/02 15:17:46 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_state(t_state state, t_philo *philo)
{
	long	time_span;

	time_span = time_now() - philo->data->start_time;
	if (state == dead && !philo->is_full)
	{
		printf("%ld\t%d\tdied\n", time_span, philo->id);
		return ;
	}
	sem_wait(philo->data->write);
	if (state == taking_fork1 && !philo->is_full)
		printf("%ld\t%d\thas taken a fork\n", time_span, philo->id);
	else if (state == taking_fork2 && !philo->is_full)
		printf("%ld\t%d\thas taken a fork\n", time_span, philo->id);
	else if (state == eating && !philo->is_full)
		printf("%ld\t%d\tis eating\n", time_span, philo->id);
	else if (state == sleeping && !philo->is_full)
		printf("%ld\t%d\tis sleeping\n", time_span, philo->id);
	else if (state == thinking && !philo->is_full)
		printf("%ld\t%d\tis thinking\n", time_span, philo->id);
	sem_post(philo->data->write);
}

void	eat(t_philo *philo)
{
	long	start;
	bool	b;

	start = philo->data->start_time;
	philo->last_meal = time_now() - start;
	print_state(eating, philo);
	ft_usleep(philo->data->time_eat, philo);
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
	sem_wait(philo->data->forks);
	print_state(taking_fork1, philo);
	if (philo->data->nb_philo == 1)
	{
		ft_usleep(philo->data->time_die, philo);
		return (print_state(dead, philo), exit(42), 0);
	}
	sem_wait(philo->data->forks);
	print_state(taking_fork2, philo);
	eat(philo);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	return (0);
}

void	sleep_first(t_philo *philo)
{
	print_state(thinking, philo);
	ft_usleep(philo->data->time_eat, philo);
}

void	philo_life(t_philo *philo)
{
	sem_wait(philo->data->all_ready);
	philo->data->start_time = time_now();
	if (philo->id % 2 == 0)
		sleep_first(philo);
	while (true)
	{
		philo_eat(philo);
		print_state(sleeping, philo);
		ft_usleep(philo->data->time_sleep, philo);
		print_state(thinking, philo);
	}
	exit(0);
	return ;
}

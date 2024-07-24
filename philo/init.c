/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:06:18 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/24 10:30:50 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_forks(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->lock, NULL))
		return (ft_printerror("mutex init failed", data, 0), false);
	if (pthread_mutex_init(&data->bool_lock, NULL))
	{
		pthread_mutex_destroy(&data->lock);
		ft_printerror("mutex init failed", data, 0);
		return (false);
	}
	if (pthread_mutex_init(&data->write, NULL))
	{
		pthread_mutex_destroy(&data->lock);
		pthread_mutex_destroy(&data->bool_lock);
		ft_printerror("mutex init failed", data, 0);
		return (false);
	}
	while (++i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (ft_printerror("mutex init failed", data, i), false);
	}
	return (true);
}

bool	data_init(t_data *data)
{
	int	i;

	data->is_end = false;
	data->is_failed = false;
	data->forks = malloc((sizeof(pthread_mutex_t) * data->nb_philo));
	if (!data->forks)
		return (error("malloc failed"), free(data), false);
	data->philo = malloc((sizeof(t_philo) * data->nb_philo));
	if (!data->philo)
		return (free(data->forks), free(data), error("malloc failed"), 0);
	if (!init_forks(data))
		return (false);
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].data = data;
		data->philo[i].meals_eat = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].is_full = false;
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
	}
	return (true);
}

bool	is_valid(char *str)
{
	int	i;

	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	while (str && str[i])
	{
		if (!is_num(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	handle_input(t_data *data, char **argv)
{
	data->nb_meals = -1;
	if (is_valid(argv[1]) && ft_atoi(argv[1]) != -1)
		data->nb_philo = ft_atoi(argv[1]);
	else
		return (error("argument not valid"), false);
	if (is_valid(argv[2]) && ft_atoi(argv[2]) != -1)
		data->time_die = ft_atoi(argv[2]);
	else
		return (error("argument not valid"), false);
	if (is_valid(argv[3]) && ft_atoi(argv[3]) != -1)
		data->time_eat = ft_atoi(argv[3]);
	else
		return (error("argument not valid"), false);
	if (is_valid(argv[4]) && ft_atoi(argv[4]) != -1)
		data->time_sleep = ft_atoi(argv[4]);
	else
		return (error("argument not valid"), false);
	if (argv[5])
	{
		if (is_valid(argv[5]) && ft_atoi(argv[5]) != -1)
			data->nb_meals = ft_atoi(argv[5]);
		else
			return (error("argument not valid"), false);
	}
	return (true);
}

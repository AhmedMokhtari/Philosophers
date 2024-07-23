/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:06:18 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/23 17:55:48 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	data_init(t_data *data)
{
	int	i;

	i = -1;
	data->is_end = false;
	data->forks = ft_malloc((sizeof(pthread_mutex_t) * data->nb_philo));
	data->philo = ft_malloc((sizeof(t_philo) * data->nb_philo));
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->bool_lock, NULL);
	pthread_mutex_init(&data->bool_lock1, NULL);
	pthread_mutex_init(&data->write, NULL);
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->forks[i], NULL);
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

void	handle_input(t_data *data, char **argv)
{
	data->nb_meals = -1;
	if (is_valid(argv[1]))
		data->nb_philo = ft_atoi(argv[1]);
	else
		ft_printerror("argument not valid");
	if (is_valid(argv[2]))
		data->time_die = ft_atoi(argv[2]);
	else
		ft_printerror("argument not valid");
	if (is_valid(argv[3]))
		data->time_eat = ft_atoi(argv[3]);
	else
		ft_printerror("argument not valid");
	if (is_valid(argv[4]))
		data->time_sleep = ft_atoi(argv[4]);
	else
		ft_printerror("argument not valid");
	if (argv[5])
	{
		if (is_valid(argv[5]))
			data->nb_meals = ft_atoi(argv[5]);
		else
			ft_printerror("argument not valid");
	}
}

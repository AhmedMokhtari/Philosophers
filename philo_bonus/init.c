/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 11:53:45 by amokhtar          #+#    #+#             */
/*   Updated: 2024/08/03 11:51:47 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	open_seem(t_data *data)
{
	data->forks = sem_open("forks", O_CREAT, 0644, data->nb_philo);
	data->full = sem_open("full", O_CREAT, 0644, 0);
	data->end = sem_open("end", O_CREAT, 0644, 0);
	data->all_ready = sem_open("all_ready", O_CREAT, 0644, 0);
	data->write = sem_open("write", O_CREAT, 0644, 1);
	if (data->forks == SEM_FAILED || data->full == SEM_FAILED
		|| data->end == SEM_FAILED || data->write == SEM_FAILED
		|| data->all_ready == SEM_FAILED)
		return (error("sem_open failed"), free(data), false);
	return (true);
}

bool	data_init(t_data *data, int i)
{
	data->is_end = false;
	data->is_failed = false;
	unlink_sem();
	data->time_think = data->time_eat - data->time_sleep;
	data->time_think += data->time_eat * (data->nb_philo % 2);
	if (!open_seem(data))
		return (false);
	data->philo = malloc((sizeof(t_philo) * data->nb_philo));
	if (!data->philo)
		return (free(data), unlink_sem(), error("malloc failed"), 0);
	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].data = data;
		data->philo[i].meals_eat = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].is_full = false;
		data->philo[i].id = i + 1;
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
	if (is_valid(argv[1]) && ft_atoi(argv[1]) >= 0)
		data->nb_philo = ft_atoi(argv[1]);
	else
		return (error("argument not valid"), false);
	if (is_valid(argv[2]) && ft_atoi(argv[2]) > 0)
		data->time_die = ft_atoi(argv[2]);
	else
		return (error("argument not valid"), false);
	if (is_valid(argv[3]) && ft_atoi(argv[3]) > 0)
		data->time_eat = ft_atoi(argv[3]);
	else
		return (error("argument not valid"), false);
	if (is_valid(argv[4]) && ft_atoi(argv[4]) > 0)
		data->time_sleep = ft_atoi(argv[4]);
	else
		return (error("argument not valid"), false);
	if (argv[5])
	{
		if (is_valid(argv[5]) && ft_atoi(argv[5]) >= 0)
			data->nb_meals = ft_atoi(argv[5]);
		else
			return (error("argument not valid"), false);
	}
	return (true);
}

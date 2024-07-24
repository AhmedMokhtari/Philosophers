/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:56:17 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/24 11:00:36 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_dead(t_data *data)
{
	int		i;
	long	time;
	bool	full;
	long	*last_meal;

	while (!ret_boolean(data, &data->is_end))
	{
		i = -1;
		full = true;
		while (++i < data->nb_philo)
		{
			if (ret_boolean(data, &data->philo[i].is_full) == false)
				full = false;
			last_meal = &data->philo[i].last_meal;
			time = time_now() - ret_long(data, last_meal) - data->start_time;
			if (time >= data->time_die)
			{
				set_boolean(data, &data->is_end, true);
				print_state(dead, &data->philo[i]);
				return ;
			}
		}
		if (full)
			set_boolean(data, &data->is_end, true);
	}
}

bool	start_dinner(t_data *data)
{
	int			i;
	pthread_t	*t;

	i = 0;
	data->start_time = 0;
	while (i < data->nb_philo)
	{
		t = &data->philo[i].id_thread;
		if (pthread_create(t, NULL, philo_life, &data->philo[i]))
		{
			set_boolean(data, &data->is_failed, true);
			return (error("pthread_create Failed "), false);
		}
		i++;
	}
	set_long(data, &data->start_time, time_now());
	check_dead(data);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].id_thread, NULL))
			return (error("pthread_join Failed "), false);
	}
	return (true);
}

void	ft_clean(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->bool_lock);
	pthread_mutex_destroy(&data->write);
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->philo);
	free(data->forks);
	free(data);
}

void	ex(void)
{
	system("leaks philo");
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (write(2, "number argument error ", 22), -1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (error("malloc failed"), -1);
	if (!handle_input(data, argv))
		return (free(data), -1);
	if (data->nb_meals == 0)
		return (0);
	if (!data_init(data))
		return (-1);
	if (!start_dinner(data))
		return (ft_clean(data), -1);
	ft_clean(data);
	return (0);
}

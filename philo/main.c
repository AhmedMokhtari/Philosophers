/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:56:17 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/23 18:18:46 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_dead(t_data *data)
{
	int		i;
	long	time;
	bool	full;

	while (!ret_boolean(data, &data->is_end))
	{
		i = 0;
		full = true;
		while (i < data->nb_philo)
		{
			if (ret_boolean(data, &data->philo[i].is_full) == false)
				full = false;
			time = time_now() - ret_long(data, &data->philo[i].last_meal) - data->start_time;
			if (time >= data->time_die)
			{
				set_boolean(data, &data->is_end, true);
				print_state(dead, &data->philo[i]);
				return ;
			}
			i++;
		}
		if (full)
			set_boolean(data, &data->is_end, true);
	}
}
void	start_dinner(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].id_thread, NULL, philo_life, &data->philo[i]))
		{
			set_boolean(data, &data->is_end, true);
			printf("allo no thread \n");
			exit(1);
		}
		i++;
	}
	set_long(data, &data->start_time, time_now());
	check_dead(data);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philo[i].id_thread, NULL);
}
int main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	i = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		ft_printerror("moel-fat l7imari\n");
	if (argc < 5 ||  argc > 6)
		return (write(2, "number argument error ", 22), -1);
	handle_input(data, argv);
	if (data->nb_meals == 0)
		return (0);
	data_init(data);
	start_dinner(data);
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->bool_lock);
	pthread_mutex_destroy(&data->bool_lock1);
	pthread_mutex_destroy(&data->write);
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	return (0);
}
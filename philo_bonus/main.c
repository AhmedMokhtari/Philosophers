/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:58:59 by amokhtar          #+#    #+#             */
/*   Updated: 2024/08/02 12:54:19 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	check_philo(int *pid, t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nb_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 42)
		{
			kill_all(data, pid);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

bool	start_dinner(t_data *data, int i)
{
	pid_t		pid;
	int			*p;

	p = malloc(data->nb_philo * sizeof(int));
	if (!p)
		return (write(2, "error in malloc\n", 16), free_data(data), false);
	while (i < data->nb_philo)
	{
		pid = fork();
		if (pid == -1)
			return (write(2, "error in fork\n", 14), kill_all(data, p), false);
		if (pid == 0)
			philo_life(&data->philo[i]);
		p[i] = pid;
		i++;
	}
	i = -1;
	while (++i < data->nb_philo)
		sem_post(data->all_ready);
	check_philo(p, data);
	if (data->nb_meals > -1)
		check_full(data);
	sem_wait(data->end);
	return (free_data(data), free(p), true);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (write(2, "number argument error ", 22), -1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (error("malloc failed"), -1);
	if (!handle_input(data, argv))
		return (free(data), -1);
	if (data->nb_meals == 0 || data->nb_philo == 0)
		return (0);
	if (!data_init(data, -1))
		return (-1);
	if (!start_dinner(data, 0))
		return (-1);
	return (0);
}

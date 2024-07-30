/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:58:59 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/30 19:12:43 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	data_init(t_data *data)
{
	int	i;

	data->is_end = false;
	data->is_failed = false;
	sem_unlink("forks");
	sem_unlink("full");
	sem_unlink("end");
	sem_unlink("write");
	data->forks = sem_open("forks", O_CREAT, 0644, data->nb_philo);
	if (data->forks == SEM_FAILED)
		return (error("sem_open failed"), free(data), false);
	data->philo = malloc((sizeof(t_philo) * data->nb_philo));
	if (!data->philo)
		return (free(data), sem_close(data->forks), error("malloc failed"), 0);
	data->full = sem_open("full", O_CREAT, 0644, 0);
	data->end = sem_open("end", O_CREAT, 0644, 0);
	data->write = sem_open("write", O_CREAT, 0644, 1);
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
void	*check_full(void *da)
{
	int 	j;
	t_data	*data;

	j = 0;
	data = (t_data *)da;
	while (j < data->nb_philo)
	{
		sem_wait(data->full);
		j++;
	}
	sem_post(data->end);
	return (NULL);
}

bool	start_dinner(t_data *data)
{
	int			i;
	pid_t		pid;
	pthread_t	ptd;
	int			*p;

	i = 0;
	p = malloc(data->nb_philo);	
	data->start_time = time_now();
	while (i < data->nb_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_life(&data->philo[i]);
		}
		p[i] = pid;
		i++;
	}
	pthread_create(&ptd, NULL, check_full, data);
	sem_wait(data->end);
	pthread_join(ptd, NULL);
	i = 0;
	while (i < data->nb_philo)
	{
		// printf("killl %d\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", i);
		if (kill(p[i], SIGQUIT))
			perror("fsdf ");
		i++;
	}
	return (true);
}

int main(int argc, char **argv)
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
	start_dinner(data);
	return (0);
}
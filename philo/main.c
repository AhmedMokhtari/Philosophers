/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:56:17 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/22 16:50:46 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_num(char s)
{
	if (s >= '0' && s <= '9')
		return (true);
	return (false);
}
bool	ret_boolean(t_data *data, bool set)
{
		bool val;
		
		pthread_mutex_lock(&data->bool_lock);
		val = set;
		pthread_mutex_unlock(&data->bool_lock);
		return (val);
}



void	set_boolean(t_data *data, bool *set, bool val)
{
		pthread_mutex_lock(&data->bool_lock);
		*set = val;
		pthread_mutex_unlock(&data->bool_lock);
}

void	set_long(t_data *data, long *set, long val)
{
		pthread_mutex_lock(&data->bool_lock);
		*set = val;
		pthread_mutex_unlock(&data->bool_lock);
}

long	ret_long(t_data *data, long set)
{
		long	val;
		
		pthread_mutex_lock(&data->bool_lock);
		val = set;
		pthread_mutex_unlock(&data->bool_lock);
		return (val);
}


bool	is_space(char s)
{
	if ((s >= 9 && s <= 13) || s == 32)
		return (true);
	return (false);
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

void	ft_printerror(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

int	ft_atoi(char *s)
{
	long	sum;
	int		i;
	

	i = 0;
	sum = 0;
	while (is_space(s[i]))
		i++;
	if (s[i] == '+')
		i++;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			sum = (sum * 10)  + (s[i] - '0');
			if (sum > INT_MAX)
				ft_printerror("error in args INT Max");
		}
		i++;
	}
	// printf("sum is %ld \n", sum);
	return ((int)sum);
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

long	time_now()
{
	struct timeval	val;
	long			time;

	gettimeofday(&val, NULL);
	time = (val.tv_sec * 1000) + (val.tv_usec / 1000);
	return (time);	
}

void	ft_usleep(long mili, t_data *data)
{
	long	i;

	(void)data;
	i = time_now();
	// printf("usleep ----------<<<<.>>>>\n");
	while (time_now() - i < mili)
	{
		if (ret_boolean(data,data->is_end))
			break ;
		usleep(1);
	}
}
void	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->is_end = false;
	data->nb_meals = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		ft_printerror("malloc failed");
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		ft_printerror("malloc failed");
	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->bool_lock, NULL);
	pthread_mutex_init(&data->bool_lock1, NULL);
	pthread_mutex_init(&data->write, NULL);
	while (i < data->nb_meals)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].data = data;
		data->philo[i].meals_eat = 0;
		data->philo[i].is_dead = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].is_full = 0;
		//pthread_mutex_init(&data->forks[i], NULL);
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
}


void	print_state(t_state state, t_philo *philo)
{
	long	time_span;

	// printf("%ld %ld %ld\n", time_span, time_now(),philo->data->start_time);
	time_span = time_now() - ret_long(philo->data, philo->data->start_time);
	// if (ret_boolean(philo->data, philo->data->is_end) && state != dead)
	// {
	// 	//printf("fgdf 2222222\n");
	// 	return ;
	// }
	pthread_mutex_unlock(&philo->data->write);
	// if (state == taking_fork1 && !ret_boolean(philo->data, philo->data->is_end))
	if (state == taking_fork1)
		printf("%-6ld %-6d has taken a fork 1 \n", time_span, philo->id);
	// else if (state == taking_fork2 && !ret_boolean(philo->data, philo->data->is_end))
	else if (state == taking_fork2)
		printf("%-6ld %-6d has taken a fork 2\n", time_span, philo->id);
	// else if (state == eating && ! ret_boolean(philo->data, philo->data->is_end))
	else if (state == eating)
		printf("%-6ld %-6d is eating\n", time_span, philo->id);
	// else if (state == sleeping && ! ret_boolean(philo->data, philo->data->is_end))
	else if (state == sleeping)
		printf("%-6ld %-6d is sleeping\n", time_span, philo->id);
	// else if (state == thinking && ! ret_boolean(philo->data, philo->data->is_end))
	else if (state == thinking)
		printf("%-6ld %-6d is thinking\n", time_span, philo->id);
	else if (state == dead)
		printf("%-6ld %-6d dead allah yar7hmo\n", time_span, philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

void	eat(t_philo *philo)
{
	long	start;

	start = philo->data->start_time;
	print_state(eating, philo);
	// philo->last_meal = time_now();
	ft_usleep(philo->data->time_eat, philo->data);
	set_long(philo->data, &philo->last_meal,time_now() - start);
	pthread_mutex_lock(&philo->data->bool_lock);
	philo->meals_eat++;
	pthread_mutex_unlock(&philo->data->bool_lock);
	// if (ret_long(philo->data, philo->meals_eat) == ret_long(philo->data, philo->data->nb_meals))
	// {
	// 	printf("here %d %ld %ld\n", philo->id, ret_long(philo->data, philo->meals_eat),ret_long(philo->data, philo->data->nb_meals));
	// 	// printf("herer\n");
	// 	set_boolean(philo->data, &philo->is_full, true);
	// }
}
void	*philo_life(void *data)
{
	t_philo	*philo;
	bool	b;

	b = false;
	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(10, philo->data);
	while (true)
	{
		// printf("philo id   %d \n", philo->id);
		// if (ret_boolean(philo->data, philo->is_full) || ret_boolean(philo->data, philo->is_dead))
		// if (ret_boolean(philo->data, philo->is_full) || ret_boolean(philo->data, philo->data->is_end) || ret_boolean(philo->data, philo->is_dead))
		// 	break ;
		pthread_mutex_lock(philo->left_fork);
		print_state(taking_fork1, philo);
		pthread_mutex_lock(philo->right_fork);
		print_state(taking_fork2, philo);
		eat(philo);
		if (philo->is_full || ret_boolean(philo->data, philo->data->is_end))
		{
			//printf("dfgdfg \n");
			// pthread_mutex_unlock(philo->left_fork);
			// 
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_state(sleeping, philo);
		ft_usleep(philo->data->time_sleep, philo->data);
		// if (philo->is_full || ret_boolean(philo->data, philo->data->is_end))
		// {
		// 	//printf("dfgdfg\n");
		// 	break ;
		// }
		print_state(thinking, philo);
		//ft_usleep(10, philo->data);
	}
	// pthread_mutex_unlock(philo->left_fork);
	// pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

void	check_dead(t_data *data)
{
	int		i;
	long	time;

	while (!ret_boolean(data, data->is_end))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			time = time_now() - ret_long(data, data->philo[i].last_meal) - data->start_time;
			if (time > data->time_die)
			{
				// printf("helo %ld %ld %ld \n",time, data->philo[i].last_meal, data->start_time);
				// printf("geerer\n");
				// set_boolean(data, &data->philo[i].is_dead, true);
				// pthread_mutex_lock(&data->bool_lock);
				set_boolean(data, &data->is_end, true);
				// pthread_mutex_unlock(&data->bool_lock);
				print_state(dead, &data->philo[i]);
				return ;
			}
			i++;
		}
	}
}
void	start_dinner(t_data *data)
{
	int	i;
	// long time;

	i = 0;
	// printf("time - t %ld \n", data->start_time);
	data->start_time = time_now();
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i].id_thread, NULL, philo_life, &data->philo[i]);
		i++;
	}
	check_dead(data);
	i = -1;
	while (++i < data->nb_philo)
		pthread_join(data->philo[i].id_thread, NULL);
}
int main(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		ft_printerror("moel-fat l7imari\n");
	if (argc < 5 ||  argc > 6)
		return (write(2, "number argument error ", 22), -1);
	handle_input(data, argv);
	data_init(data);
	start_dinner(data);
	// printf("nb philo %d time die %d time eat %d time sleep %d nb meals %d\n",data.nb_philo, data.time_die, data.time_eat, data.time_die, data.nb_meals);
	return (0);
}
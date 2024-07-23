/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:56:17 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/23 16:40:46 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_num(char s)
{
	if (s >= '0' && s <= '9')
		return (true);
	return (false);
}

// void	pthread_mutex_locck(pthread_mutex_t *t, t_data *data)
// {
// 	if (pthread_mutex_lock(&data->lock))
// 	{
// 		printf("mutex error \n");
// 		exit(1);
// 	}
// }
bool	ret_boolean(t_data *data, bool *set)
{
		bool val;
		
		pthread_mutex_lock(&data->bool_lock);
		val = *set;
		pthread_mutex_unlock(&data->bool_lock);

		return (val);
}



void	set_boolean(t_data *data, bool *set, bool val)
{
		// printf("ennter \n");
		pthread_mutex_lock(&data->bool_lock);
		*set = val;
		pthread_mutex_unlock(&data->bool_lock);
		// printf("sort \n");

}

void	set_long(t_data *data, long *set, long val)
{
		pthread_mutex_lock(&data->bool_lock);
		*set = val;
		pthread_mutex_unlock(&data->bool_lock);
}

long	ret_long(t_data *data, long *set)
{
		long	val;
		
		pthread_mutex_lock(&data->bool_lock);
		val = *set;
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

	// (void)data;
	i = time_now();
	// printf("usleep ----------<<<<.>>>>\n");
	while (time_now() - i < mili)
	{
		// printf("usleep ----------<<<<.>>>>\n");	
		if (ret_boolean(data,&data->is_end))
			break ;
		usleep(1);
	}
}
void	data_init(t_data *data)
{
	int	i;

	i = 0;
	data->is_end = false;
	// data->nb_meals = -1;
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
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].data = data;
		data->philo[i].meals_eat = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].is_full = false;
		data->philo[i].id = i + 1;
		/**/
		// data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
    	// data->philo[i].left_fork = &data->forks[i];
		// if (data->philo[i].id % 2 == 0)
		// {
		// 	data->philo[i].right_fork = &data->forks[i];
		// 	data->philo[i].left_fork = &data->forks[(i + 1) % data->nb_philo];
		// }
		/**/
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		i++;
	}
}


void	print_state(t_state state, t_philo *philo)
{
	long	time_span;

	// printf("%ld %ld %ld\n", time_span, time_now(),philo->data->start_time);
	time_span = time_now() - ret_long(philo->data, &philo->data->start_time);
	if (ret_boolean(philo->data, &philo->data->is_end) && state != dead)
		return ;
	pthread_mutex_lock(&philo->data->write);
	if (state == taking_fork1 && !ret_boolean(philo->data, &philo->data->is_end))
		printf("%-4ld %-4d has taken a fork\n", time_span, philo->id);
	else if (state == taking_fork2 && !ret_boolean(philo->data, &philo->data->is_end))
		printf("%-4ld %-4d has taken a fork\n", time_span, philo->id);
	else if (state == eating && !ret_boolean(philo->data, &philo->data->is_end))
		printf("%ld %d is eating\n", time_span, philo->id);
	else if (state == sleeping && !ret_boolean(philo->data, &philo->data->is_end))
		printf("%-4ld %-4d is sleeping\n", time_span, philo->id);
	else if (state == thinking && !ret_boolean(philo->data, &philo->data->is_end))
		printf("%-4ld %-4d is thinking\n", time_span, philo->id);
	else if (state == dead)
		printf("%-6ld %-6d dead\n", time_span, philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

void	eat(t_philo *philo)
{
	long	start;

	start = philo->data->start_time;
	print_state(eating, philo);
	ft_usleep(philo->data->time_eat, philo->data);
	set_long(philo->data, &philo->last_meal,time_now() - start);
	pthread_mutex_lock(&philo->data->bool_lock1);
	philo->meals_eat++;
	pthread_mutex_unlock(&philo->data->bool_lock1);
	if (ret_long(philo->data, &philo->data->nb_meals) != -1 && ret_long(philo->data, &philo->meals_eat) == ret_long(philo->data, &philo->data->nb_meals))
	{
		//printf("chba3 dkhal hna id %d  eats %ld nb meals %ld\n ", philo->id, philo->meals_eat, philo->data->nb_meals);
		set_boolean(philo->data, &philo->is_full, true);
	}
}
void	*philo_life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (ret_long(philo->data, &philo->data->start_time) == 0)
		;
	if (philo->id % 2 == 0)
		ft_usleep(10, philo->data);
	while (true)
	{
		if (ret_boolean(philo->data, &philo->is_full) || ret_boolean(philo->data, &philo->data->is_end))
			break ;
		pthread_mutex_lock(philo->left_fork);
		print_state(taking_fork1, philo);
		pthread_mutex_lock(philo->right_fork);
		print_state(taking_fork2, philo);
		eat(philo);
		// if (philo->is_full || ret_boolean(philo->data, &philo->data->is_end))
		if (ret_boolean(philo->data, &philo->data->is_end))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_state(sleeping, philo);
		ft_usleep(philo->data->time_sleep, philo->data);
		// if (ret_boolean(philo->data, &philo->is_full) || ret_boolean(philo->data, &philo->data->is_end))
		if (ret_boolean(philo->data, &philo->data->is_end))
			break ;
		print_state(thinking, philo);
	}
	return (NULL);
}

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
				if (data->nb_philo == 1)
					pthread_mutex_unlock(data->philo[i].left_fork);
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
	// long time;

	i = 0;
	// printf("time - t %ld \n", data->start_time);
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
		// pthread_detach(data->philo[i].id_thread);
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
	// printf("nb philo %d time die %d time eat %d time sleep %d nb meals %d\n",data.nb_philo, data.time_die, data.time_eat, data.time_die, data.nb_meals);
	return (0);
}
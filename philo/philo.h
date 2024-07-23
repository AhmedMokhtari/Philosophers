/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:56:13 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/23 18:09:03 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo t_philo;

typedef struct s_data
{
	long			nb_philo;
	long			time_die;
	long			time_sleep;
	long			time_eat;
	long			nb_meals;
	long			start_time;
	bool			is_end;
	pthread_mutex_t *forks;
	pthread_mutex_t lock;
	pthread_mutex_t bool_lock;
	pthread_mutex_t bool_lock1;
	pthread_mutex_t write;
	t_philo			*philo;
}	t_data;

typedef enum e_state
{
	taking_fork1,
	taking_fork2,
	eating,
	sleeping,
	thinking,
	dead
}	t_state;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	bool			is_full;
	long			meals_eat;
	pthread_t		id_thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data			*data;
}	t_philo;

void	data_init(t_data *data);
void	ft_printerror(char *s);
void	*ft_malloc(size_t size);
int		ft_atoi(char *s);
bool	is_space(char s);
bool	is_valid(char *str);
bool	is_num(char s);
bool	ret_boolean(t_data *data, bool *set);
void	set_boolean(t_data *data, bool *set, bool val);
void	set_long(t_data *data, long *set, long val);
long	ret_long(t_data *data, long *set);
void	ft_usleep(long mili, t_data *data);
long	time_now(void);
void	handle_input(t_data *data, char **argv);
void	eat(t_philo *philo);
void	*philo_life(void *data);
void	print_state(t_state state, t_philo *philo);

#endif

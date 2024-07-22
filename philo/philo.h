/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:56:13 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/22 15:21:54 by amokhtar         ###   ########.fr       */
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
	bool			is_dead;
	int				meals_eat;
	pthread_t		id_thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_data			*data;
}	t_philo;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 09:56:13 by amokhtar          #+#    #+#             */
/*   Updated: 2024/08/03 11:34:04 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <pthread.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	long	nb_philo;
	long	time_die;
	long	time_sleep;
	long	time_eat;
	long	nb_meals;
	long	time_think;
	long	start_time;
	bool	is_end;
	bool	is_failed;
	sem_t	*forks;
	sem_t	*all_ready;
	sem_t	*full;
	sem_t	*end;
	sem_t	*write;
	t_philo	*philo;
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
	t_data			*data;
}	t_philo;

int		ft_atoi(char *s);
bool	is_space(char s);
bool	is_num(char s);
void	error(char *s);
long	time_now(void);
void	ft_usleep(long mili, t_philo *philo);
void	philo_life(t_philo *philo);
void	print_state(t_state state, t_philo *philo);
void	free_data(t_data *data);
void	kill_all(t_data *data, int *p);
bool	handle_input(t_data *data, char **argv);
bool	data_init(t_data *data, int i);
void	*check_full(t_data *data);
void	unlink_sem(void);
bool	check_dead(t_philo *philo);

#endif

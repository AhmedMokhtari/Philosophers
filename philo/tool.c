/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:22:48 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/24 10:51:21 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_printerror(char *s, t_data *data, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free(data->philo);
	free(data->forks);
	free(data);
	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	write(2, "\n", 1);
}

void	error(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	write(2, "\n", 1);
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
			sum = (sum * 10) + (s[i] - '0');
			if (sum > INT_MAX)
				return (error("error in args INT Max"), -1);
		}
		i++;
	}
	return ((int)sum);
}

bool	is_space(char s)
{
	if ((s >= 9 && s <= 13) || s == 32)
		return (true);
	return (false);
}

bool	is_num(char s)
{
	if (s >= '0' && s <= '9')
		return (true);
	return (false);
}

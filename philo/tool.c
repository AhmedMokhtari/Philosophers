/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:22:48 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/23 18:00:44 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			sum = (sum * 10) + (s[i] - '0');
			if (sum > INT_MAX)
				ft_printerror("error in args INT Max");
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

long	time_now(void)
{
	struct timeval	val;
	long			time;

	gettimeofday(&val, NULL);
	time = (val.tv_sec * 1000) + (val.tv_usec / 1000);
	return (time);
}

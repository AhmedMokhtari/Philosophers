/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amokhtar <amokhtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 10:01:57 by amokhtar          #+#    #+#             */
/*   Updated: 2024/07/30 10:05:31 by amokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 19:48:48 by davi-g            #+#    #+#             */
/*   Updated: 2023/12/04 18:06:24 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_atoi(const char *str)
{
	unsigned int		pos;
	unsigned long long	num;

	pos = 0;
	num = 0;
	while (str[pos] >= '0' && str[pos] <= '9')
	{
		num = num * 10 + (str[pos] - '0');
		pos++;
	}
	if (num > INT_MAX)
		return (-1);
	return (num);
}

int	is_number(char *a)
{
	size_t	i;

	if (!a)
		return (0);
	i = 0;
	while (a[i])
	{
		if (!(a[i] >= '0' && a[i] <= '9') || ft_atoi(a) == -1)
			return (1);
		i++;
	}
	return (0);
}

time_t	get_time(time_t option)
{
	struct timeval	time;
	time_t			t;

	t = 0;
	gettimeofday(&time, 0);
	t = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	if (option == -1)
		return (t);
	else
		return (t - option);
}

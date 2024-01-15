/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkthread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 00:49:38 by davi-g            #+#    #+#             */
/*   Updated: 2023/12/04 17:53:57 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_stop(t_philo *philos, int i)
{
	pthread_mutex_lock(&philos->sys->dead);
	philos->sys->stop = i;
	pthread_mutex_unlock(&philos->sys->dead);
}

int	check_simulation_stopped(t_philo *philos)
{
	int	s;

	s = 0;
	pthread_mutex_lock(&philos->sys->dead);
	if (philos->sys->stop == 1)
		s = 1;
	pthread_mutex_unlock(&philos->sys->dead);
	return (s);
}

int	check_dead(t_philo philos)
{
	time_t	time;

	time = get_time(-1);
	if (time > philos.time_last_eat + philos.params->time_die)
	{
		send_msg(&philos, "died");
		return (1);
	}
	return (0);
}

int	check_all(t_philo *philos)
{
	set_stop(philos, 0);
	start_delay(philos->sys->time_start);
	if (philos->params->num_philo > 1)
	{
		while (1)
		{
			if (check_param(philos) == 1)
			{
				set_stop(philos, 1);
				return (1);
			}
			if ((size_t)philos->params->error == philos->params->num_philo)
			{
				set_stop(philos, 1);
				return (1);
			}
			usleep(235);
		}
	}
	else
	{
		start_delay(philos->sys->time_start + philos->params->time_die + 1);
		return (1);
	}
	return (0);
}

int	check_param(t_philo *philos)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	philos->params->error = 0;
	while (i < philos->params->num_philo)
	{
		if (check_dead(philos[i]) == 1)
			return (1);
		pthread_mutex_lock(&philos->sys->meals);
		if (philos[i].num_eat == philos[i].params->num_must_eat)
			j++;
		pthread_mutex_unlock(&philos->sys->meals);
		i++;
	}
	philos->params->error = (int)j;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:06:56 by davi-g            #+#    #+#             */
/*   Updated: 2023/12/04 18:42:29 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	send_msg(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->sys->print);
	if (check_simulation_stopped(philo) == 1)
	{
		pthread_mutex_unlock(&philo->sys->print);
		return (1);
	}
	printf("%s%ld %s%zu %s%s\n%s", GREEN, get_time(philo->sys->time_start),
		CYAN, philo->id, MAGENTA, msg, RESET);
	pthread_mutex_unlock(&philo->sys->print);
	return (0);
}

void	start_delay(time_t start_time)
{
	while (get_time(-1) < start_time)
		continue ;
}

void	stop_all(t_philo *philos)
{
	size_t	i;

	i = 0;
	while (i < philos->params->num_philo)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	stop_mutex(philos);
	free(philos->sys->forks);
	free(philos);
}

void	stop_mutex(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i < philo->params->num_philo)
	{
		pthread_mutex_destroy(&philo->sys->forks[i]);
		i++;
	}
}

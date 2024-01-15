/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davi-g <davi-g@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:05:59 by davi-g            #+#    #+#             */
/*   Updated: 2023/12/04 18:44:17 by davi-g           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_eat(t_philo *philos)
{
	pthread_mutex_lock(&philos->sys->forks[philos->left_fork]);
	if (send_msg(philos, "has taken a fork") == 1)
		return (1);
	pthread_mutex_lock(&philos->sys->forks[philos->right_fork]);
	if (send_msg(philos, "has taken a fork") == 1)
		return (1);
	if (send_msg(philos, "is eating") == 1)
		return (1);
	philos->time_last_eat = get_time(-1);
	pthread_mutex_lock(&philos->sys->meals);
	philos->num_eat++;
	pthread_mutex_unlock(&philos->sys->meals);
	ft_sleep(philos, philos->params->time_eat);
	pthread_mutex_unlock(&philos->sys->forks[philos->left_fork]);
	pthread_mutex_unlock(&philos->sys->forks[philos->right_fork]);
	if (send_msg(philos, "is sleeping") == 1)
		return (1);
	ft_sleep(philos, philos->params->time_sleep);
	if (send_msg(philos, "is thinking") == 1)
		return (1);
	return (0);
}

int	ft_sleep(t_philo *philo, time_t time_sleep)
{
	time_t			start;

	start = get_time(-1);
	while (get_time(start) < time_sleep)
	{
		if (check_simulation_stopped(philo) == 1)
			return (1);
		usleep(50);
	}
	return (0);
}

void	*philo_one(t_philo *philos)
{
	pthread_mutex_lock(&philos->sys->forks[philos->left_fork]);
	send_msg(philos, "has taken a fork");
	ft_sleep(philos, philos->params->time_die);
	pthread_mutex_unlock(&philos->sys->forks[philos->left_fork]);
	send_msg(philos, "died");
	return (0);
}

void	*routine(void *system)
{
	t_philo	*philos;

	philos = (t_philo *)system;
	philos->time_last_eat = philos->sys->time_start;
	start_delay(philos->sys->time_start);
	if (philos->params->num_philo == 1)
	{
		philo_one(philos);
		return (0);
	}
	else if (philos->id % 2 == 0)
		ft_sleep(philos, 5);
	while (check_simulation_stopped(philos) == 0)
	{
		if (ft_eat(philos) == 1)
			return (0);
		if (philos->params->num_must_eat != -1
			&& philos->num_eat == philos->params->num_must_eat)
			return (0);
	}
	return (0);
}

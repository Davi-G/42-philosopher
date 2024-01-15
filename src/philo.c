/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:37:34 by davi-g            #+#    #+#             */
/*   Updated: 2023/12/04 18:01:09 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start(t_param *params, t_philo	*philos)
{
	size_t		i;
	t_system	system;

	system.time_start = (get_time(-1) + 50);
	philos = create_philo(philos, params->num_philo, params, &system);
	if (start_mutex(&system, params->num_philo) != 0)
		return (1);
	i = 0;
	while (i < params->num_philo)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
		{
			write(1, "Error creating thread\n", 22);
			return (1);
		}
		i++;
	}
	check_all(philos);
	stop_all(philos);
	return (0);
}

int	start_mutex(t_system *system, size_t num_philos)
{
	size_t	i;

	i = 0;
	system->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!system->forks)
		return (1);
	while (i < num_philos)
	{
		pthread_mutex_init(&system->forks[i], NULL);
		i++;
	}
	if (pthread_mutex_init(&system->meals, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&system->print, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&system->dead, NULL) != 0)
		return (1);
	return (0);
}

void	give_forks(t_philo *philo, size_t num_philos)
{
	size_t	id;

	id = philo->id - 1;
	philo->left_fork = id;
	philo->right_fork = (id + 1) % num_philos;
	if (id % 2 == 0)
	{
		philo->left_fork = (id + 1) % num_philos;
		philo->right_fork = id;
	}
}

t_philo	*create_philo(t_philo *philos, size_t num_philos,
						t_param *params, t_system *system)
{
	size_t	id;
	size_t	i;

	i = 0;
	id = 1;
	philos = (t_philo *)malloc(sizeof(t_philo) * num_philos);
	if (!philos)
		return (0);
	while (i < num_philos)
	{
		philos[i].id = id++;
		philos[i].num_eat = 0;
		philos[i].time_last_eat = get_time(-1);
		philos[i].params = params;
		philos[i].sys = system;
		give_forks(&philos[i], num_philos);
		i++;
	}
	return (philos);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:11:32 by davi-g            #+#    #+#             */
/*   Updated: 2023/12/04 18:11:15 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>

# define RESET		"\e[0m"
# define YELLOW		"\e[33m"
# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"

typedef struct s_param
{
	size_t			num_philo;
	time_t			time_die;
	time_t			time_eat;
	time_t			time_sleep;
	long			num_must_eat;
	int				error;
}	t_param;

typedef struct s_system
{
	size_t			i;
	time_t			time_start;
	pthread_t		controller;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	meals;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
}	t_system;

typedef struct s_philo
{
	t_param			*params;
	t_system		*sys;
	size_t			id;
	int				left_fork;
	int				right_fork;
	int				num_eat;
	time_t			time_last_eat;
	pthread_t		thread;
}	t_philo;

void		start_delay(time_t start_time);
int			start(t_param *params, t_philo *philos);
t_philo		*create_philo(t_philo *philos, size_t num_philos,
				t_param *params, t_system *system);
int			check_params(t_philo *philos);
int			check_dead(t_philo philos);
int			send_msg(t_philo *philo, char *msg);
int			start_mutex(t_system *system, size_t num_philos);
int			ft_eat(t_philo *philos);
int			ft_sleep(t_philo *philo, time_t time_sleep);
void		*routine(void *system);
void		give_forks(t_philo *philo, size_t num_philos);
void		set_values(t_param *params, char **av, size_t id);
void		parse(int ac, char **av, t_param *params);
void		*philo_one(t_philo *philos);
int			check_error(t_param *params);
void		print_params(t_param params);
long		ft_atoi(const char *str);
int			is_number(char *a);
int			check_simulation_stopped(t_philo *philos);
void		*check_routine(void	*data);
time_t		get_time(time_t option);
void		stop_all(t_philo *philos);
int			check_param(t_philo *philos);
int			check_all(t_philo *philos);
void		set_stop(t_philo *philos, int i);
void		stop_mutex(t_philo *philo);
void		start_delay(time_t start_time);

#endif

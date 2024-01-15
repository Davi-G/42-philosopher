/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:01:33 by davi-g            #+#    #+#             */
/*   Updated: 2023/12/04 17:58:51 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_values(t_param *params, char **av, size_t id)
{
	if (id == 1)
		params->num_philo = ft_atoi(av[1]);
	if (id == 2)
		params->time_die = ft_atoi(av[2]);
	if (id == 3)
		params->time_eat = ft_atoi(av[3]);
	if (id == 4)
		params->time_sleep = ft_atoi(av[4]);
	if (av[5])
		params->num_must_eat = ft_atoi(av[5]);
	else
		params->num_must_eat = -1;
}

void	parse(int ac, char **av, t_param *params)
{
	size_t	i;

	i = 1;
	if (ac > 6)
		params->error = 2;
	else if (ac < 5)
		params->error = 1;
	else
	{
		while (av[i] && i < 6)
		{
			if (is_number(av[i]) == 1)
			{
				params->error = 3;
				break ;
			}
			set_values(params, av, i);
			i++;
		}
	}
}

int	check_error(t_param *params)
{
	if (params->error == 1)
		write(1, "Error: too few arguments\n", 25);
	else if (params->error == 2)
		write(1, "Error: too many arguments\n", 26);
	else if (params->error == 3)
		write(1, "Error: invalid argument\n", 24);
	else if (params->num_must_eat == 0)
	{
		write(1, "Error: invalid number of meals\n", 31);
		return (1);
	}
	else if (params->num_philo > 200 || params->num_philo <= 0)
	{
		write(1, "Error: invalid number of philosophers\n", 38);
		return (1);
	}
	return (0);
}

void	print_params(t_param params)
{
	printf("---------------------------------------\n\n");
	printf("num_philo: %zu\n", params.num_philo);
	printf("time_die: %zu\n", params.time_die);
	printf("time_eat: %zu\n", params.time_eat);
	printf("time_sleep: %zu\n", params.time_sleep);
	printf("num_must_eat: %ld\n", params.num_must_eat);
	printf("\n---------------------------------------\n\n");
}

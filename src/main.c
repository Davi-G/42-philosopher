/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagomez <dagomez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:11:41 by davi-g            #+#    #+#             */
/*   Updated: 2023/12/04 17:56:47 by dagomez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_void(void)
{
	system("leaks -q philo");
}

int	main(int ac, char **av)
{
	t_param	params;
	t_philo	philos;

	params.error = 0;
	parse(ac, av, &params);
	if (check_error(&params) == 1 || params.error != 0)
		return (1);
	start(&params, &philos);
	return (0);
}

//	atexit(ft_void);
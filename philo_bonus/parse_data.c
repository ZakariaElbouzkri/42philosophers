/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:11:43 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/12 10:40:30 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *nbr)
{
	long res;

	if (*nbr == '-' || *nbr == '+')
		if (*nbr++ == '-' || !*nbr)
			return (-1);
	res = 0;
	while (*nbr)
	{
		if (*nbr >= '0' && *nbr <= '9' && res < INT_MAX)
		{
			res *= 10;
			res += (*nbr - '0');
		}
		else
			return (-1);
		nbr++;
	}
	return ((res <= INT_MAX) * res + (res > INT_MAX) * (-1));
}


int	init_data(long *args, char **av)
{
	int i;

	i = -1;
	while (av[++i])
	{
		args[i] = ft_atol(av[i]);
		if (args[i] < 0)
			return (0);
	}
	return (1);
}

void	init_semaphores(t_data *data)
{
	sem_unlink(FORKS);
	data->forks = sem_open(FORKS, O_RDWR|O_CREAT, 0777, data->nbr_of_philo);
	sem_unlink(PR);
	data->pr = sem_open(PR, O_RDWR|O_CREAT, 0777, 1);
	sem_unlink(STP);
	data->stop = sem_open(STP, O_RDWR|O_CREAT, 0777, 0);
}

int parse_data(t_data *data, int ac, char **av)
{
	long	*args;

	args = 	malloc(sizeof(long) * (ac));
	if (!args)
		return (0);
	if (!init_data(args, av))
		return (free(args), 0);
	data->nbr_of_philo = args[0];
	data->time_to_die  = args[1];
	data->time_to_eat = args[2];
	data->time_to_sleep = args[3];
	data->eat_times = (ac == 6) * args[4] + (ac != 6) * (-1);
	data->t0 = current_time();
	init_semaphores(data);
	return (free(args), 1);
}


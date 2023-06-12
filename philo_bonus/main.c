/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:08:45 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/12 12:37:58 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usage(void)
{
	printf("Error\n");
}

t_philo	*create_philosphers(t_data *data)
{
	t_philo	*ph;
	int		i;

	i = -1;
	ph = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!ph)
	{
		sem_close(data->forks);
		sem_close(data->pr);
		return (NULL);
	}
	while (++i < data->nbr_of_philo)
	{
		ph[i].id = i + 1;
		ph[i].eat_times = (data->eat_times != -1) * 0;
		ph[i].last_m = current_time();
		ph[i].data = data;
		ph[i].name = ft_itoa(i + 1);
	}
	return (ph);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*ph;

	if (ac != 5 && ac != 6)
		return (usage(), 1);
	if (!parse_data(&data, ac, &av[1]))
		return (usage(), 1);
	ph = create_philosphers(&data);
	if (!ph)
		return (usage(), 1);
	create_processes(ph, &data);
	kill_processes(ph, &data);
	return (0);
}

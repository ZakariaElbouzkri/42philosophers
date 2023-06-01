/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:23:51 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/01 17:10:12 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(char *evnt, t_philo *philo)
{
	printf("%ld %d %s\n", (current_time() - philo->data->t0),
		philo->id, evnt);
}

void	*routine(void *data)
{
	t_philo *ph;

	ph = (t_philo *)data;
	if (!(ph->id & 1))
		ft_usleep(10);
	while (ph->eat_times != ph->data->eat_times)
	{
		if (ph->data->dead == 1)
			return (NULL);
		sem_wait(ph->data->forks);
		safe_print("has taken a fork", ph);
		sem_wait(ph->data->forks);
		safe_print("has taken a fork", ph);
		ph->last_m = current_time();
		safe_print("is eating", ph);
		ft_usleep(ph->data->time_to_eat);
		ph->eat_times += (ph->eat_times >= 0);
		sem_post(ph->data->forks);
		sem_post(ph->data->forks);
		safe_print("is sleeping", ph);
		ft_usleep(ph->data->time_to_sleep);
		safe_print("is thinking", ph);
	}
	return (NULL);
}

int	send_to_table(t_philo *ph, t_data *data)
{
	int i;

	i = -1;
	while ((++i) < data->nbr_of_philo)
	{
		if ((ph[i].pid = fork()))
			routine(&ph[i]);
	}
	// check_death(ph, data);
	return (0);
}

int	philosophers(t_data *data)
{
	t_philo *philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!philos)
		return (1);
	i = -1;
	while ((++i) < data->nbr_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].last_m = data->t0;
		philos[i].eat_times = 0;
	}
	return (send_to_table(philos, data));
}

int main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (argc != 5 && argc != 6)
		return (printf("error\n"), 1);
	if (!init_data(&data, argc, &argv[1]))
		return (printf("error\n"), 1);
	if (!data.nbr_of_philo)
		return (0);
	return (philosophers(&data));
}

// [5 800 200 200 7]
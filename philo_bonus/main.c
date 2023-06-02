/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:23:51 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/02 14:18:48 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(char *evnt, t_philo *philo, t_data *data)
{
	sem_wait(data->pr);
	printf("%ld %d %s\n", (current_time() - data->t0),
		philo->id, evnt);
	sem_post(data->pr);
}

void	routine(t_philo *ph, t_data *data)
{
	while (ph->eat_times != data->eat_times)
	{
		sem_wait(data->forks);
		safe_print("has taking a fork", ph, data);
		sem_wait(data->forks);
		safe_print("has taking a fork", ph, data);
		ph->last_m = current_time();
		safe_print("is eating", ph, data);
		ft_usleep(data->time_to_eat);
		ph->eat_times += (data->eat_times >= 0);
		sem_post(data->forks);
		sem_post(data->forks);
		safe_print("is sleeping", ph, data);
		ft_usleep(data->time_to_sleep);
		safe_print("is thinking", ph, data);
	}
}

int	send_to_table(t_philo *ph, t_data *data)
{
	int		i;
	int		status;

	i = -1;
	while ((++i) < data->nbr_of_philo)
	{
		if (!(ph[i].pid = fork()))
			routine(&ph[i], data);
	}
	while (true)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			status = WEXITSTATUS(status);
			if (status != 0)
				printf("%ld philo %d died\n", current_time() - data->t0, status);
			break;
		}
	}
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:23:51 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/13 10:37:17 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(char *evnt, t_philo *philo, int s)
{
	pthread_mutex_lock(&philo->data->pr);
	printf("%ld\t%d\t%s\n", (current_time() - philo->data->t0),
		philo->id, evnt);
	if (s)
		pthread_mutex_unlock(&philo->data->pr);
}

void	*routine(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	if (!(ph->id % 2))
		usleep(ph->data->time_to_eat);
	while (ph->data->eat_times != ph->eat_times)
	{
		pthread_mutex_lock(&ph->fork);
		safe_print(TAKE_FORK, ph, 1);
		pthread_mutex_lock(ph->r_fork);
		safe_print(TAKE_FORK, ph, 1);
		pthread_mutex_lock(&ph->data->d);
		ph->last_m = current_time();
		pthread_mutex_unlock(&ph->data->d);
		safe_print(EAT, ph, 1);
		ft_usleep(ph->data->time_to_eat);
		ph->eat_times += (ph->data->eat_times >= 0);
		pthread_mutex_unlock(&ph->fork);
		pthread_mutex_unlock(ph->r_fork);
		safe_print(SLEEP, ph, 1);
		ft_usleep(ph->data->time_to_sleep);
		safe_print(THINK, ph, 1);
	}
	return (NULL);
}

int	send_to_table(t_philo *ph, t_data *data)
{
	int	i;

	i = -1;
	while ((++i) < data->nbr_of_philo)
		if (pthread_create(&ph[i].thread, NULL, routine, &ph[i]))
			return (free(ph), printf("thread creation error\n"), 1);
	i = -1;
	while ((++i) < data->nbr_of_philo)
		if (pthread_detach(ph[i].thread))
			return (free(ph), printf("thread detach error\n"), 1);
	check_death(ph, data);
	i = -1;
	while (++i < data->nbr_of_philo)
		pthread_mutex_destroy(&ph[i].fork);
	pthread_mutex_destroy(&data->d);
	pthread_mutex_destroy(&data->pr);
	pthread_mutex_destroy(&data->pr);
	free(ph);
	return (0);
}

int	philosophers(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!philos)
		return (1);
	i = -1;
	while ((++i) < data->nbr_of_philo)
	{
		philos[i].id = i + 1;
		if (pthread_mutex_init(&philos[i].fork, NULL))
			return (free(philos), printf("mutex_init error\n"), 1);
		philos[i].data = data;
		philos[i].last_m = data->t0;
		philos[i].eat_times = 0;
		if ((i + 1) == data->nbr_of_philo)
			philos[i].r_fork = &philos[0].fork;
		else
			philos[i].r_fork = &philos[i + 1].fork;
	}
	return (send_to_table(philos, data));
}

int	main(int argc, char **argv)
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

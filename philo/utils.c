/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:42:33 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/05 17:03:23 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(size_t t_ms)
{
	size_t	start;

	start = current_time();
	while (current_time() - start < t_ms)
		usleep(100);
}

void	check_death(t_philo *ph, t_data *data)
{
	int	i;

	i = -1;
	while (true)
	{
		pthread_mutex_lock(&data->d);
		if ((long)(current_time() - ph[++i].last_m) >= data->time_to_die)
		{
			pthread_mutex_lock(&data->pr);
			if (ph[i].data->eat_times != ph[i].eat_times)
				printf("%ld %d %s\n", current_time() - data->t0, ph[i].id, DIE);
			ft_usleep(100);
			break ;
		}
		pthread_mutex_unlock(&data->d);
		if ((i + 1) == data->nbr_of_philo)
			i = -1;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 09:42:33 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/01 17:07:49 by zel-bouz         ###   ########.fr       */
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
	size_t t;

	i = 0;
	while (true)
	{
		t = current_time();
		if ((long)(t - ph[i].last_m) >= data->time_to_die)
		{
			data->dead = 1;
			ft_usleep(10);
			if (ph[i].eat_times != data->eat_times)
				printf("%ld philo %d died\n", t - data->t0, ph[i].id);
			return ;
		}
		i++;
		if ((i + 1) == data->nbr_of_philo)
			i = 0;
	}
}

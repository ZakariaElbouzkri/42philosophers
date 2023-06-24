/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:56:55 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/24 20:30:30 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(char *evnt, t_philo *ph, int s)
{
	sem_wait(ph->data->pr);
	printf("%ld\t%d\t%s\n", current_time() - ph->data->t0, ph->id, evnt);
	if (s)
		sem_post(ph->data->pr);
}

void	*check_death(void *ph)
{
	while (true)
	{
		sem_wait(((t_philo *)ph)->death);
		if ((long)(current_time() - ((t_philo *)ph)->last_m)
			>= ((t_philo *)ph)->data->time_to_die)
		{
			safe_print(DIE, ph, 0);
			exit(1);
		}
		sem_post(((t_philo *)ph)->death);
	}
}

void	routine(t_philo *ph, t_data *data)
{
	sem_unlink(ph->name);
	ph->death = sem_open(ph->name, O_CREAT | O_RDWR, 0777, 1);
	pthread_create(&ph->tid, NULL, check_death, ph);
	pthread_detach(ph->tid);
	while (ph->eat_times != data->eat_times)
	{
		sem_wait(data->forks);
		safe_print(TAKE_FORK, ph, 1);
		sem_wait(data->forks);
		safe_print(TAKE_FORK, ph, 1);
		sem_wait(ph->death);
		ph->last_m = current_time();
		sem_post(ph->death);
		safe_print(EAT, ph, 1);
		ft_usleep(data->time_to_eat);
		ph->eat_times += (data->eat_times >= 0);
		sem_post(data->forks);
		sem_post(data->forks);
		safe_print(THINK, ph, 1);
		ft_usleep(data->time_to_sleep);
		safe_print(THINK, ph, 1);
	}
	exit(0);
}

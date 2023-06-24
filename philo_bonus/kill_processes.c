/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:04:36 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/24 20:34:37 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	kill_all(t_data *data, t_philo *ph, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		kill(ph[i].pid, SIGKILL);
	i = -1;
	while (++i < data->nbr_of_philo)
	{
		sem_close(ph[i].death);
		free(ph[i].name);
	}
	sem_close(data->forks);
	sem_close(data->pr);
	free(ph);
}

void	kill_processes(t_philo *ph, t_data *data)
{
	int	j;
	int	status;

	j = -1;
	while (++j < data->nbr_of_philo)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status))
			{
				kill_all(data, ph, data->nbr_of_philo);
				return ;
			}
		}
	}
	kill_all(data, ph, 0);
}

void	create_processes(t_philo *ph, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_of_philo)
	{
		ph[i].pid = fork();
		if (ph[i].pid < 0)
		{
			perror("fork");
			kill_all(data, ph, i);
			exit(1);
		}
		if (ph[i].pid == 0)
			routine(&ph[i], data);
	}
}

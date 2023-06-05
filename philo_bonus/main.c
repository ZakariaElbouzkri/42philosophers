/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:23:51 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/05 18:37:13 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(char *evnt, t_philo *philo, t_data *data)
{
	sem_wait(data->pr);
	printf("%ld philo %d %s\n", (current_time() - data->t0),
		philo->id, evnt);
	sem_post(data->pr);
}

void	*death_check(void *data)
{
	t_philo	*ph;

	ph = data;
	while (true)
	{
		sem_wait(ph->death);
		if ((long)(current_time() - ph->last_m) >= ph->data->time_to_die)
			exit(ph->id);
		sem_post(ph->death);
	}
}

void	routine(t_philo *ph, t_data *data)
{
	pthread_t	tid;

	pthread_create(&tid, NULL, death_check, ph);
	pthread_detach(tid);
	while (ph->eat_times != data->eat_times)
	{
		sem_wait(data->forks);
		sem_wait(data->forks);
		safe_print("has taking a fork", ph, data);
		safe_print("has taking a fork", ph, data);
		sem_wait(ph->death);
		ph->last_m = current_time();
		sem_post(ph->death);
		safe_print("is eating", ph, data);
		ft_usleep(data->time_to_eat);
		ph->eat_times += (data->eat_times >= 0);
		sem_post(data->forks);
		sem_post(data->forks);
		safe_print("is sleeping", ph, data);
		ft_usleep(data->time_to_sleep);
		safe_print("is thinking", ph, data);
	}
	exit(0);
}

int	send_to_table(t_philo *ph, t_data *data)
{
	int		i;
	int		status;

	i = -1;
	while ((++i) < data->nbr_of_philo)
	{
		ph[i].pid = fork();
		if (ph[i].pid == -1){
			perror("fork");
			exit(0);
		}
		if (!(ph[i].pid))
			routine(&ph[i], data);
	}
	int j = -1;
	while (++j < data->nbr_of_philo)
	{
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status))
			{
				sem_wait(data->pr);
				i = -1;
				while (++i < data->nbr_of_philo)
					kill(ph[i].pid, SIGKILL);
				printf("%ld %d %s\n", current_time() - data->t0,
					status, DIE);
				exit(0);
			}
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
		philos[i].data = data;
		sem_unlink(DT);
		philos[i].death = sem_open(DT, O_CREAT|O_EXCL, 0777, 1);
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
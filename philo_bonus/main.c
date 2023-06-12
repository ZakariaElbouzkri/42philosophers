/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:08:45 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/12 11:28:32 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usage()
{
	printf("Error\n");
}

t_philo	*create_philosphers(t_data *data)
{
	t_philo *ph;
	int i;

	i = -1;
	ph = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!ph)
		return (NULL);
	while (++i < data->nbr_of_philo)
	{
		ph[i].id = i + 1;
		ph[i].eat_times = (data->eat_times != -1) * 0;
		ph[i].last_m = current_time();
		ph[i].data = data;
		ph[i].name = ft_itoa(i+1);

	}
	return (ph);
}

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
		if ((long)(current_time() - ((t_philo *)ph)->last_m) >= ((t_philo *)ph)->data->time_to_die)
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
	ph->death = sem_open(ph->name, O_CREAT|O_RDWR, 0777, 1);
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

int	create_processes(t_philo *ph, t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nbr_of_philo)
	{
		ph[i].pid = fork();
		if (ph[i] .pid < 0)
		{
			perror("fork");
			return (1);
		}
		if (ph[i].pid == 0)
			routine(&ph[i], data);
	}
	int j = -1;
	int status;
	while (++j < data->nbr_of_philo)
	{
		waitpid(-1 , &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status))
			{
				i = -1;
				while (++i < data->nbr_of_philo)
					kill(ph[i].pid, SIGKILL);
				exit(0);
			}
		}
	}
	return (0);
}

int main(int ac, char **av)
{
	t_data data;
	t_philo *ph;

	if (ac != 5 && ac != 6)
		return (usage(), 1);
	if (!parse_data(&data, ac, &av[1]))
		return (usage(), 1);
	ph = create_philosphers(&data);
	if (!ph)
		return (usage(), 1);
	return (create_processes(ph, &data));

}

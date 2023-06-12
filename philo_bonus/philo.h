/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:09:30 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/12 11:24:11 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

# define FORKS "fork"
# define PR "print"
# define STP "stop"
# define DT "philo"
# define TAKE_FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_data
{
	long			nbr_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			eat_times;
	int				dead;
	sem_t			*forks;
	sem_t			*stop;
	sem_t			*pr;
	size_t			t0;	
}	t_data;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	pthread_t		tid;
	t_data			*data;
	size_t			last_m;
	sem_t			*death;
	char			*name;
	long			eat_times;
} t_philo;

int parse_data(t_data *data, int ac, char **av);
int	init_data(long *args, char **av);
long	ft_atol(char *nbr);

char	*ft_itoa(int nbr);

void	ft_usleep(size_t t_ms);
size_t current_time();

#endif

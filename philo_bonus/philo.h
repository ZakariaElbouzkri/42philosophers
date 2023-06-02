/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:22:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/02 14:10:50 by zel-bouz         ###   ########.fr       */
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

#define NAME "frk"

typedef struct s_data
{
	long			nbr_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			eat_times;
	int				dead;
	sem_t			*forks;
	sem_t			pr;
	size_t			t0;	
}	t_data;

typedef struct s_philo
{
	int				id;
	pid_t			pid;
	pthread_t		tid;
	t_data			*data;
	size_t			last_m;
	long			eat_times;
} t_philo;


// parser
long	check_num(char *s);
int		fill_args(char **av, long *args);
int		init_data(t_data *data, int ac, char **av);
void	ft_usleep(size_t t_ms);
size_t	current_time(void);
void	check_death(t_philo *ph, t_data *data);
void	safe_print(char *evnt, t_philo *philo, t_data *data);

#endif

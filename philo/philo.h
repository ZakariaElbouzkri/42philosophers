/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 20:22:10 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/05 17:03:29 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <ctype.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

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
	size_t			t0;
	pthread_mutex_t	pr;
	pthread_mutex_t	d;
	pthread_mutex_t	ate;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*r_fork;
	t_data			*data;
	size_t			last_m;
	long			eat_times;
}	t_philo;

// parser
long	check_num(char *s);
int		fill_args(char **av, long *args);
int		init_data(t_data *data, int ac, char **av);
void	ft_usleep(size_t t_ms);
size_t	current_time(void);
void	check_death(t_philo *ph, t_data *data);
void	safe_print(char *evnt, t_philo *philo);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zel-bouz <zel-bouz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 09:44:06 by zel-bouz          #+#    #+#             */
/*   Updated: 2023/06/12 12:31:44 by zel-bouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(char *s)
{
	if (!*s)
		return (0);
	return (1 + ft_strlen(++s));
}

char	*ft_itoa(int nbr)
{
	int		len;
	int		n;
	char	*ret;

	n = nbr;
	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	ret = malloc(sizeof(char) * len);
	ret[len] = '\0';
	while (nbr && len >= 0)
	{
		ret[--len] = ((nbr % 10) + '0');
		nbr /= 10;
	}
	return (ret);
}

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

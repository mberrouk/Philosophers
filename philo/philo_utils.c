/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 21:04:56 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/17 00:38:31 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, 0x00) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	write_message(char *s, t_threads *info, int id)
{
	pthread_mutex_lock(&info->mutexs->print);
	if (info->kill)
	{	
		pthread_mutex_unlock((&info->mutexs->print));
		return (1);
	}
	printf(s, (unsigned int)get_time() - info->t0, id + 1);
	pthread_mutex_unlock((&info->mutexs->print));
	return (0);
}

void	ft_usleep(unsigned int job)
{
	unsigned int	time;

	time = get_time();
	while (get_time() - time < job)
		usleep(250);
}

static int	ft_convert(char *s1, int sign)
{
	int				i;
	unsigned long	r;

	r = 0;
	i = 0;
	while (s1[i] >= 48 && s1[i] <= 57)
	{
		if (r > __INT_MAX__)
			break ;
		r = r * 10 + (s1[i] - '0');
		i++;
	}
	if (r > __INT_MAX__)
	{
		if (sign < 0 && r != 2147483648)
			return (0);
		return (-1);
	}
	return (r * sign);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
			i++;
	if (str[i] == '-' || str[i] == '+')
	{	
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (ft_convert(&str[i], sign));
}

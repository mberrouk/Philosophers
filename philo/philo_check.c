/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:40:38 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/17 02:02:29 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	err_msg(char *str, int status)
{
	write(STDERR_FILENO, "Error ", 5);
	if (str)
		write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
	return (status);
}

int	check_meals(t_threads *threads)
{
	pthread_mutex_lock(&threads->mutexs->meal);
	if (threads->meals * threads->data->n_p)
	{
		pthread_mutex_unlock(&threads->mutexs->meal);
		return (1);
	}
	pthread_mutex_unlock(&threads->mutexs->meal);
	return (0);
}

void	*_death(t_threads *threads)
{
	int	tim;
	int	i;

	while (1)
	{
		i = 0;
		while (i < threads->data->n_p)
		{
			if (threads->data->eat_tims != -1 && check_meals(threads))
				return (0x00);
			pthread_mutex_unlock(&threads->mutexs->meal);
			pthread_mutex_lock(&threads->mutexs->tim[i]);
			tim = threads->last_meal[i];
			if (tim > 0)
				tim = get_time() - tim;
			pthread_mutex_unlock(&threads->mutexs->tim[i]);
			if (tim >= threads->data->to_die)
				return (death_sentence(threads, i));
			i++;
		}
	}
}

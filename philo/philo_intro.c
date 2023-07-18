/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_intro.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:37:42 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/17 01:18:39 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_step(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		if (!av[i][j])
			return (0);
		if (av[i][j] == '-' || av[i][j] == '+')
		{
			if (av[i][j] == '+')
				j++;
			if (av[i][j] == '-' || !av[i][j])
				return (0);
		}
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	init_data(t_data *data, char **av)
{
	data->n_p = ft_atoi(av[1]);
	if (data->n_p <= 0)
		return (0);
	data->to_die = ft_atoi(av[2]);
	if (data->to_die <= 0)
		return (0);
	data->to_eat = ft_atoi(av[3]);
	if (data->to_eat <= 0)
		return (0);
	data->to_slp = ft_atoi(av[4]);
	if (data->to_slp <= 0)
		return (0);
	if (av[5])
	{
		data->eat_tims = ft_atoi(av[5]);
		if (data->eat_tims <= 0)
			return (0);
	}
	else
		data->eat_tims = -1;
	return (1);
}

int	init_mutexs(t_data *data, t_locks *mutexs)
{
	int	i;

	if (pthread_mutex_init(&(mutexs->print), NULL) \
		|| pthread_mutex_init(&(mutexs->id), NULL) \
		|| pthread_mutex_init(&(mutexs->meal), NULL))
		return (err_msg(" : mutex Initialisation Error", 1));
	mutexs->fork = malloc(sizeof(pthread_mutex_t) * data->n_p);
	if (!mutexs->fork)
		return (err_msg(" : malloc failed", 1));
	mutexs->tim = malloc(sizeof(pthread_mutex_t) * data->n_p);
	if (!mutexs->tim)
		return (err_msg(" : malloc failed", 1));
	i = 0;
	while (i < data->n_p)
	{
		if (pthread_mutex_init(&(mutexs->fork[i]), NULL))
			return (err_msg(" : mutex Initialisation Error", 1));
		if (pthread_mutex_init(&(mutexs->tim[i]), NULL))
			return (err_msg(" : mutex Initialisation Error", 1));
		i++;
	}
	return (0);
}

int	init_threads_data(t_data *data, t_threads *threads, t_locks *mutexs)
{
	int	i;

	threads->data = data;
	threads->mutexs = mutexs;
	threads->last_meal = malloc(sizeof(int) * data->n_p);
	if (!threads->last_meal)
		return (err_msg(" : malloc failed", 1));
	i = 0;
	while (i < data->n_p)
		threads->last_meal[i++] = 0;
	if (data->eat_tims != -1)
	{
		threads->meals = 0;
	}
	return (init_mutexs(data, mutexs));
}

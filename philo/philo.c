/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:25:57 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/17 02:40:56 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_sentence(t_threads *threads, int id)
{
	pthread_mutex_lock(&threads->mutexs->print);
	threads->kill = 1;
	printf("%u ms: %d is died\n", get_time() - threads->t0, id + 1);
	pthread_mutex_unlock(&threads->mutexs->print);
	return (0x00);
}

int	philo_sleep(t_threads *info, int id, int meals)
{
	pthread_mutex_unlock(&info->mutexs->tim[id]);
	ft_usleep(info->data->to_eat);
	pthread_mutex_unlock(&info->mutexs->fork[id]);
	pthread_mutex_unlock(&info->mutexs->fork[(id + 1) % info->data->n_p]);
	if (info->data->eat_tims != -1 && meals == info->data->eat_tims)
		return (1);
	if (get_time() - info->last_meal[id] >= info->data->to_die)
		return (1);
	if (write_message("%lu ms: %d is sleeping\n", info, id))
		return (1);
	ft_usleep(info->data->to_slp);
	if (write_message("%lu ms: %d is thinking\n", info, id))
		return (1);
	return (0);
}

int	philo_eating(t_threads *info, int id, int *meals)
{
	pthread_mutex_lock(&info->mutexs->tim[id]);
	if (write_message("%lu ms: %d is eating\n", info, id))
	{
		_unlock(info, id, 3);
		return (1);
	}
	info->last_meal[id] = get_time();
	if (info->data->eat_tims != -1)
	{
		pthread_mutex_lock(&info->mutexs->meal);
		info->meals++;
		pthread_mutex_unlock(&info->mutexs->meal);
		(*meals)++;
		if (*meals == info->data->eat_tims)
			info->last_meal[id] = -1;
	}
	return (0);
}

void	*routine(t_threads *info)
{
	int	id;
	int	meals;

	meals = 0;
	pthread_mutex_lock(&info->mutexs->id);
	id = info->id;
	pthread_mutex_unlock(&info->mutexs->id);
	while (1)
	{
		pthread_mutex_lock(&info->mutexs->fork[id]);
		if (write_message("%lu ms: %d has taken a fork\n", info, id)
			|| info->data->n_p == 1)
		{
			_unlock(info, id, 1);
			return (0x00);
		}
		pthread_mutex_lock(&info->mutexs->fork[(id + 1) % info->data->n_p]);
		if (write_message("%lu ms: %d has taken a fork\n", info, id))
		{
			_unlock(info, id, 2);
			return (0x00);
		}
		if (philo_eating(info, id, &meals) || philo_sleep(info, id, meals))
			return (0x00);
	}
}

int	ft_threads_create(t_threads *threads)
{
	int	i;

	threads->t = malloc(sizeof(pthread_t) * threads->data->n_p);
	if (!threads->t)
		return (err_msg(" : malloc failed", 1));
	if (pthread_create(&threads->supervisor, NULL, (void *)_death, threads))
		return (err_msg(" : Failed to create threads", 1));
	i = 0;
	threads->t0 = get_time();
	threads->kill = 0;
	while (i < threads->data->n_p)
	{
		pthread_mutex_lock(&threads->mutexs->tim[i]);
		threads->last_meal[i] = get_time();
		pthread_mutex_unlock(&threads->mutexs->tim[i]);
		pthread_mutex_lock(&threads->mutexs->id);
		threads->id = i;
		pthread_mutex_unlock(&threads->mutexs->id);
		if (pthread_create(&threads->t[i], NULL, (void *)routine, threads))
			return (err_msg(" : Failed to create threads", 1));
		usleep(100);
		i++;
	}
	return (0);
}

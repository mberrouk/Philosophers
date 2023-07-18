/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:23:00 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/17 02:36:19 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_all(t_threads *threads)
{
	int	i;

	i = 0;
	if (pthread_join(threads->supervisor, NULL))
		return (err_msg(" : join failed", 1));
	while (i < threads->data->n_p)
	{
		if (pthread_join(threads->t[i], NULL))
			return (err_msg(" : join failed", 1));
		i++;
	}
	return (0);
}

void	detach_all(t_threads *threads)
{
	int	i;

	i = 0;
	if (threads->data->n_p == 1)
		return ;
	while (i < threads->data->n_p)
	{
		pthread_detach(threads->t[i]);
		i++;
	}
}

void	mutexes_clear(t_locks *mutxes, int n_philo)
{
	int	i;

	if (&((*mutxes).id))
		pthread_mutex_destroy(&mutxes->id);
	if (&((*mutxes).print))
		pthread_mutex_destroy(&mutxes->print);
	i = 0;
	while (i < n_philo)
	{
		pthread_mutex_destroy(&mutxes->tim[i]);
		pthread_mutex_destroy(&mutxes->fork[i]);
		i++;
	}
}

void	free_all(t_threads *threads)
{
	free(threads->mutexs->fork);
	free(threads->last_meal);
	free(threads->data);
	free(threads->mutexs);
	free(threads);
}

void	_unlock(t_threads *info, int id, int drp)
{
	if (drp > 2)
		pthread_mutex_unlock(&info->mutexs->tim[id]);
	if (drp > 1)
		pthread_mutex_unlock(&info->mutexs->fork[(id + 1) % info->data->n_p]);
	pthread_mutex_unlock(&info->mutexs->fork[id]);
}

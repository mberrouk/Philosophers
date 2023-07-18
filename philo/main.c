/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:22:13 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/17 02:01:39 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_data		*data;
	t_threads	*threads;
	t_locks		*mutexs;

	data = malloc(sizeof(t_data));
	threads = malloc(sizeof(t_threads));
	mutexs = malloc(sizeof(t_locks));
	if (!data || !threads || !mutexs)
		return (err_msg(" : malloc failed", 1));
	if (ac < 5 || ac > 6)
		return (err_msg(" : invalid number of arguments", 1));
	if (!init_step(av) || !init_data(data, av))
		return (err_msg(" : invalid arguments", 2));
	if (init_threads_data(data, threads, mutexs))
		return (1);
	if (ft_threads_create(threads))
		return (1);
	join_all(threads);
	detach_all(threads);
	mutexes_clear(mutexs, data->n_p);
	free_all(threads);
	return (0);
}

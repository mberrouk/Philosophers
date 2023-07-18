/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberrouk <mberrouk@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:41:06 by mberrouk          #+#    #+#             */
/*   Updated: 2023/07/17 02:01:15 by mberrouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int	n_p;
	int	to_die;
	int	to_eat;
	int	to_slp;
	int	eat_tims;
}	t_data;

typedef struct s_locks
{
	pthread_mutex_t	id;
	pthread_mutex_t	print;
	pthread_mutex_t	*tim;
	pthread_mutex_t	*fork;
	pthread_mutex_t	meal;
}	t_locks;

typedef struct s_threads
{
	t_data			*data;
	t_locks			*mutexs;
	pthread_t		*t;
	pthread_t		supervisor;
	int				*last_meal;
	int				meals;
	int				id;
	int				kill;
	unsigned int	t0;
}	t_threads;

/**
 * --> philo_check.c
 */
int		err_msg(char *str, int status);
int		ft_strlen(char *str);
int		check_meals(t_threads *threads);
void	*_death(t_threads *threads);

/**
 * --> philo_intro.c
 */
int		init_step(char **av);
int		init_data(t_data *data, char **av);
int		init_threads_data(t_data *data, t_threads *threads, t_locks *mutexs);
int		init_mutexs(t_data *data, t_locks *mutexs);
int		init_threads_data(t_data *data, t_threads *threads, t_locks *mutexs);

/**
 * --> philo.c
 */
void	*death_sentence(t_threads *threads, int id);
void	*_death(t_threads *threads);
int		philo_sleep(t_threads *info, int id, int meals);
void	*routine(t_threads *info);
int		ft_threads_create(t_threads *threads);

/**
 * --> philo_utils.c
 */
int		get_time(void);
int		write_message(char *s, t_threads *info, int id);
void	ft_usleep(unsigned int job);
int		ft_check_meals(t_data data, t_threads *threads);
int		ft_atoi(char *str);

/**
 * --> philo_clean.c 
 */
void	mutexes_clear(t_locks *mutxes, int n_philo);
void	detach_all(t_threads *threads);
void	free_all(t_threads *threads);
int		join_all(t_threads *threads);
void	_unlock(t_threads *info, int id, int drp);

#endif 

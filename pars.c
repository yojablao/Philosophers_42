/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:59:45 by yojablao          #+#    #+#             */
/*   Updated: 2024/08/27 16:47:08 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse(t_main *data, char **av, int ac)
{
	if (ac < 5 || ac > 6)
		return (0);
	if ((!check(av[1], 0) || !check(av[2], 1) \
			||!check(av[3], 1) || !check(av[4], 1)))
		return (0);
	if (ac == 6)
	{
		if (!check(av[5], 1))
			return (0);
		data->data.max_meals = my_atoi(av[5]);
	}
	else
		data->data.max_meals = -1;
	data->data.nb_of_thread = my_atoi(av[1]);
	data->data.time_to_die = my_atoi(av[2]);
	data->data.time_to_eat = my_atoi(av[3]);
	data->data.time_to_sleep = my_atoi(av[4]);
	data->data.finish_meals = 0;
	return (true);
}

bool	mutex_init(t_mutex *mutex)
{
	if(pthread_mutex_init(&mutex->write_msg, NULL) == -1)
		return (1);
	if(pthread_mutex_init(&mutex->time, NULL) == -1)
		return (1);
	pthread_mutex_init(&mutex->mx_meals, NULL);
	return (0);
}

bool	alloc(t_main *philo)
{
	philo->mutex = malloc(sizeof(t_mutex));
	if (!philo->mutex)
		return (true);
	philo->fork = malloc(sizeof(pthread_mutex_t) * philo->data.nb_of_thread);
	if (!philo->fork)
		return (true);
	philo->threads = malloc(sizeof(t_philo) * philo->data.nb_of_thread);
	if (!philo->threads)
		return (true);
	philo->tab = malloc((philo->data.nb_of_thread) * sizeof(pthread_t));
	if (!philo->tab)
		return (true);
	return (false);
}

bool	init(t_main *philo)
{
	int	i;

	i = -1;
	if (alloc(philo) || mutex_init(philo->mutex))
		return (1);
	while (++i < philo->data.nb_of_thread)
		pthread_mutex_init(&philo->fork[i], NULL);
	i = -1;
	while (++i < philo->data.nb_of_thread)
	{
		if (i + 1 == philo->data.nb_of_thread)
			philo->threads[i].l_fork = &philo->fork[0];
		else
			philo->threads[i].l_fork = &philo->fork[i + 1];
		philo->threads[i].r_fork = &philo->fork[i];
		philo->threads[i].philo = malloc(sizeof(pthread_t));
		philo->tab[i] = philo->threads[i].philo;
		philo->threads[i].id = i;
		philo->threads[i].mutxs = philo->mutex;
		philo->threads[i].data = &philo->data;
		philo->threads[i].last_eat = 0;
		philo->threads[i].meals = 0;
		philo->threads[i].die = 0;
	}
	return (0);
}

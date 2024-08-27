/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:31:57 by yojablao          #+#    #+#             */
/*   Updated: 2024/08/27 17:46:45 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	s_time(long data)
{
	return (gettime() - data);
}

int	all_eat(t_main *philo)
{
	int	i;

	i = 0;
	while (i < philo->data.nb_of_thread)
	{
		if (philo->threads[i].meals < philo->data.max_meals)
			return (1);
		i++;
	}
	pthread_mutex_lock(&philo->mutex->write_msg);
	return (0);
}

void	if_die(t_main *philo)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < philo->data.nb_of_thread)
		{
			pthread_mutex_lock(&philo->mutex->time);
			if (s_time(0) - philo->threads[i].last_eat > \
					philo->data.time_to_die)
			{
				pthread_mutex_lock(&philo->mutex->write_msg);
				printf("%ld %ld died\n", s_time(philo->data.start_time), \
					philo->threads[i].id + 1);
				return ;
			}
			pthread_mutex_unlock(&philo->mutex->time);
		}
		pthread_mutex_lock(&philo->mutex->mx_meals);
		if (philo->data.max_meals > -1)
			if (philo->data.finish_meals >= philo->data.nb_of_thread)
				return ((void)pthread_mutex_lock(&philo->mutex->write_msg));
		pthread_mutex_unlock(&philo->mutex->mx_meals);
	}
}

int	getfork_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	printing(philo, s_time(philo->data->start_time), "l_fork");
	pthread_mutex_lock(philo->r_fork);
	printing(philo, s_time(philo->data->start_time), "r_fork");
	printing(philo, s_time(philo->data->start_time), "eat");
	pthread_mutex_lock(&philo->mutxs->time);
	philo->last_eat = s_time(0);
	pthread_mutex_unlock(&philo->mutxs->time);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(&philo->mutxs->mx_meals);
	if (philo->data->max_meals != -1)
	{
		philo->meals += 1;
		if (philo->meals >= philo->data->max_meals)
			philo->data->finish_meals++;
	}
	pthread_mutex_unlock(&philo->mutxs->mx_meals);
	return (0);
}

int	sleep_think(t_philo *philo)
{
	printing(philo, s_time(philo->data->start_time), "sleep");
	ft_usleep(philo->data->time_to_sleep);
	printing(philo, s_time(philo->data->start_time), "think");
	return (0);
}

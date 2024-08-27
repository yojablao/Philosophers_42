/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:43:20 by yojablao          #+#    #+#             */
/*   Updated: 2024/08/27 16:45:27 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printing(t_philo *data, long lol, char *cases)
{
	if (pthread_mutex_lock(&data->mutxs->write_msg) != 0)
		return ;
	if (strcmp(cases, "l_fork") == 0)
		printf("%ld %ld has taken a fork\n", lol, data->id + 1);
	else if (strcmp(cases, "r_fork") == 0)
		printf("%ld %ld has taken a fork\n", lol, data->id + 1);
	else if (strcmp(cases, "eat") == 0)
		printf("%ld %ld is eating \n\n", lol, data->id + 1);
	else if (strcmp(cases, "sleep") == 0)
		printf("%ld %ld is sleeping\n", lol, data->id + 1);
	else if (strcmp(cases, "think") == 0)
		printf("%ld %ld  is thinking\n", lol, data->id + 1);
	pthread_mutex_unlock(&data->mutxs->write_msg);
}

int	ft_usleep(long time)
{
	long	start_time;

	start_time = gettime();
	while ((gettime() - start_time) < time)
		usleep(100);
	return (1);
}

void	*philo_routine(void *main)
{
	t_philo	*philo;

	philo = (t_philo *)main;
	if ((philo->id +1) % 2 == 0)
		usleep(500);
	while (1)
	{
		if (getfork_eat(philo) == 1)
			return (NULL);
		sleep_think(philo);
	}
	return (NULL);
}

void	philosopher(t_main *philo)
{
	int	i;

	i = -1;
	if (init(philo) != 0)
		return ;
	philo->data.start_time = s_time(0);
	while (++i < philo->data.nb_of_thread)
	{
		philo->threads[i].last_eat = s_time(0);
		if (pthread_create(&philo->threads[i].philo, NULL, \
			&philo_routine, &philo->threads[i]) != 0)
			return ;
		if (pthread_detach(philo->threads[i].philo) != 0)
			return ;
	}
	if_die(philo);
}

// void leak(){system("leaks philo");}
int	main(int ac, char **av)
{
	// atexit(leak);
	t_main	philo;

	if (!parse(&philo, av, ac))
		return (printf("Invalid arguments\n"), 1);
	if (ac > 6 || ac < 5)
		return (printf("Incorrect number of arguments\n"), 0);
	philosopher(&philo);
	free_all(&philo);
	return (0);
}

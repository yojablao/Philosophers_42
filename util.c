/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yojablao <yojablao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:54:30 by yojablao          #+#    #+#             */
/*   Updated: 2024/08/27 16:42:19 by yojablao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
		return (0);
	return ((t.tv_sec * 1000 + (t.tv_usec / 1000)));
}

int	check(char *s, int flag)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	if (s[0] == '+')
		s++;
	while (s[i] != '\0')
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	if (my_atoi(s) > INT_MAX)
		return (0);
	if ((my_atoi(s) > 200 || my_atoi(s) <= 0) && flag == 0)
		return (0);
	if (my_atoi(s) < 1 && flag == 1)
		return (0);
	return (1);
}

long	my_atoi(const char *str)
{
	int					i;
	long				result;

	result = 0;
	i = 0;
	if (str[0] == '+')
		str++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result);
}

void	free_all(t_main *main)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&main->mutex->write_msg);
	pthread_mutex_destroy(&main->mutex->time);
	pthread_mutex_destroy(&main->mutex->mx_meals);
	while (++i < main->data.nb_of_thread)
		pthread_mutex_destroy(&main->fork[i]);
	i = -1;
	free(main->mutex);
	free(main->threads);
	free(main->fork);
	while (++i < main->data.nb_of_thread)
		free(main->tab[i]);
	free(main->tab);
}

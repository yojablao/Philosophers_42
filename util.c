
#include "philo.h"
int check(char *s ,int flag)
{
	long result;
	int i;

	result = 0;
	i = 0;
	if(s[0] == '+')
		s++;
	while(s[i] != '\0')
	{
		if(!(s[i] >= '0' && s[i] <= '9'))
			return (0);
		i++;
	}
	if(my_atoi(s) > INT_MAX )
		return(0);
	if(my_atoi(s) > 200 && flag == 0)
		return(0);
	if(my_atoi(s) < 1 && flag == 1)
		return(0);
		
	return(1);
}

long	my_atoi(const char *str)
{
	int					i;
	long				result;

	result = 0;
	i= 0;
	if(str[0] == '+')
		str++;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result);
}
void free_all(t_main *main)
{
    int i;

    pthread_mutex_destroy(&main->mutex->write_msg);
    pthread_mutex_destroy(&main->mutex->sleep_msg);
    pthread_mutex_destroy(&main->mutex->eat_msg);
    pthread_mutex_destroy(&main->mutex->time);
    pthread_mutex_destroy(&main->mutex->mx_meals);

    for (i = 0; i < main->data.nb_of_thread; i++)
        pthread_mutex_destroy(&main->fork[i]);

    free(main->threads);
    free(main->fork);
    free(main->mutex);
}

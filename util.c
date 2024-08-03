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
	long				test;
	long				holder;

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

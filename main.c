#include "philo.h"

long gettime()
{
    struct timeval t;

    if(gettimeofday(&t, NULL) == -1)
        return 0;
    return ((t.tv_sec * 1000 + (t.tv_usec / 1000)));
}
void    printing(t_philo *data, long lol,char *cases)
{
    if(pthread_mutex_lock(&data->mutxs->write_msg) != 0)
        return ;
        if(strcmp(cases, "l_fork") == 0)
            printf("%ld %ld has taken a fork\n", lol  ,data->id+1);
        else if(strcmp(cases, "r_fork") == 0)
            printf("%ld %ld has taken a fork\n", lol ,data->id+1);
        else if(strcmp(cases, "eat") == 0)
            printf("%ld %ld is eating \n\n",lol,data->id +1);
        else if(strcmp(cases, "sleep") == 0)
            printf("%ld %ld is sleeping\n",lol,data->id + 1);
        else if(strcmp(cases, "think") == 0)
            printf("%ld %ld  is thinking\n",lol,data->id + 1);
    pthread_mutex_unlock(&data->mutxs->write_msg);
 
}
int ft_usleep(long int time)
{
    long int start_time;

    start_time = gettime();
    while ((gettime() - start_time )  < time)
        usleep(100);

    return (1);
}

void *philo_routine(void *main)
{
    t_philo *philo = (t_philo *)main;
    if((philo->id +1) % 2 == 0)
        usleep(500);
    
    while(1)
    {

        if(getfork_eat(philo) == 1)
            return (NULL);
        sleep_think(philo);
    }
    
    return NULL;
}



void    philosopher(t_main *philo)
{
    int i = -1;
    if(init(philo) != 0)
        return;
    philo->data.start_time = s_time(0);
    while(++i < philo->data.nb_of_thread)
    {
        philo->threads[i].last_eat = s_time(0);
         if(pthread_create(&philo->threads[i].philo,NULL,&philo_routine,&philo->threads[i]) != 0 || pthread_detach(philo->threads[i].philo) != 0)
            return;
    }
    if_die(philo);
}
int main(int ac ,char **av)
{
    t_main philo;

    if (!parse(&philo, av, ac))
        return (printf("Invalid arguments\n"), 1);

    if (ac > 6 || ac < 5)
        return (printf("Incorrect number of arguments\n"), 0);

    philosopher(&philo);
    free_all(&philo);  // Ensure resources are freed at the end
    return 0;

}

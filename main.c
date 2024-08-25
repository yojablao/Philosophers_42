#include "philo.h"

long gettime()
{
    struct timeval t;

    gettimeofday(&t, NULL);
    return ((t.tv_sec * 1000 + (t.tv_usec / 1000)));
}
void    printing(t_philo *data, long lol,char *cases)
{
    if(pthread_mutex_lock(&data->mutxs->write_msg) != 0)
        return ;
        if(strcmp(cases, "l_fork") == 0)
            printf("%ld %ld has taken a fork\n", lol  ,data->id);
        else if(strcmp(cases, "r_fork") == 0)
            printf("%ld %ld has taken a fork\n", lol ,data->id);
        else if(strcmp(cases, "eat") == 0)
            printf("%ld %ld is eating\n",lol,data->id);
        else if(strcmp(cases, "sleep") == 0)
            printf("%ld %ld is sleeping\n",lol,data->id);
        else if(strcmp(cases, "think") == 0)
            printf("%ld %ld  is thinking\n",lol,data->id);
    pthread_mutex_unlock(&data->mutxs->write_msg);
 
}
int ft_usleep(long int time)
{
    long int start_time;

    start_time = gettime();
    while ((gettime() - start_time) * 1000 < time)
        usleep(100);

    return (1);
}

void *philo_routine(void *main)
{
    t_philo *philo = (t_philo *)main;

    if(philo->id == 0)
        philo->data->start_time = gettime();
    if(philo->id % 2 == 0)
        ft_usleep(100);

        philo->last_eat = gettime();
    while(1)
    {
        if(getfork_eat(philo) == 1)
            return (NULL);
        pthread_mutex_lock(&philo->mutxs->time);
        philo->last_eat = gettime();
        printf("%ld\n",philo->last_eat);
        pthread_mutex_unlock(&philo->mutxs->time);
        sleep_think(philo);
    }
    
    return NULL;
}



void    philosopher(t_main *philo)
{
    int i = -1;
    if(init(philo) != 0)
        return;
    while(++i < philo->data.nb_of_thread)
    {
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
#include "philo.h"

int     parse(t_main *data ,char **av, int ac)
{

    if (ac < 5 || ac > 6)
        return (0);
    if((!check(av[1] , 0) || !check(av[2] , 1) ||
            !check(av[3] , 1) || !check(av[4] , 1)))
    {

                return 0;
    }
    if(ac == 6)
    {
        if(!check(av[5] , 1))
            return 0;
            data->data.max_meals = my_atoi(av[5]);
    } 
    else
            data->data.max_meals = -1;
    data->data.nb_of_thread = my_atoi(av[1]);
    data->data.time_to_die = my_atoi(av[2]);
    data->data.time_to_eat = my_atoi(av[3]);
    data->data.time_to_sleep = my_atoi(av[4]);
    data->data.finish_meals = 0;

    return(true);
} 

bool init(t_main *philo)
{
    int i = -1;
    if (!(philo->fork = malloc(sizeof(pthread_mutex_t) * philo->data.nb_of_thread)))
        return 1;
    if (!(philo->threads = malloc(sizeof(t_philo) * philo->data.nb_of_thread)))
        return 1;
    if (!(philo->mutex = malloc(sizeof(t_mutex))))
        return 1;
    
    pthread_mutex_init(&philo->mutex->write_msg, NULL);
    pthread_mutex_init(&philo->mutex->sleep_msg, NULL);
    pthread_mutex_init(&philo->mutex->die_msg, NULL);
    pthread_mutex_init(&philo->mutex->eat_msg, NULL);
    pthread_mutex_init(&philo->mutex->time, NULL);
    pthread_mutex_init(&philo->mutex->mx_meals, NULL);

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
        philo->threads[i].id = i;
        philo->threads[i].mutxs = philo->mutex;
        philo->threads[i].data = &philo->data;
        philo->threads[i].last_eat = 0;
        philo->threads[i].meals = 0;
        philo->threads[i].die = 0;
        philo->threads[i].start = 1;
    }

    return 0;
}

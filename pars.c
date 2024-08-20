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
         if (ac == 6)
            data->data.max_meals = my_atoi(av[5]);
        else
            data->data.max_meals = -1;
    } 
    data->die = 0;
    data->data.nb_of_thread = my_atoi(av[1]);
    data->data.time_to_die = my_atoi(av[2]);
    data->data.time_to_eat = my_atoi(av[3]);
    data->data.time_to_sleep = my_atoi(av[4]);

    return(true);
} 
// void    init_data(t_data *dest,t_data src)
// {
//     dest->nb_of_thread = src.nb_of_thread;
//     dest->time_to_die = src.time_to_die;
//     dest->time_to_eat = src.time_to_eat;
//     dest->time_to_sleep = src.time_to_sleep;
//     dest->die = false;
//     dest->meals = 0;

// } 
// bool init(t_main *philo)
// {
//     int i = -1;
//     if(!(philo->fork = malloc(sizeof(pthread_mutex_t) * philo->data.nb_of_thread)))
//         return 1;
//     if(!(philo->thread = malloc(sizeof(t_philo ) * philo->data.nb_of_thread)))
//         return 1;
//     pthread_mutex_init(&philo->write_msg,NULL);
//     pthread_mutex_init(&philo->die_msg,NULL);
//     pthread_mutex_init(&philo->eat_msg,NULL);
//     while(++i < philo->data.nb_of_thread)
//         pthread_mutex_init(&philo->fork[i],NULL);
//     i = -1;

//     while(++i < philo->data.nb_of_thread)
//     {
//         if(i+1 == philo->data.nb_of_thread)
//             philo->thread[i].l_fork = &philo->fork[0];
//         else
//             philo->thread[i].l_fork = &philo->fork[i + 1];
//         philo->thread[i].philo =  malloc(sizeof(pthread_t));
//         philo->thread[i].id = i;
//         philo->thread[i].mutxs = philo;
//         philo->thread[i].data = &philo->data;
//         philo->thread[i].r_fork = &philo->fork[i];
//         philo->thread[i].last_eat = 0;
//         philo->thread[i].meals = 0;
//         philo->thread[i].die = 0;
//         philo->thread[i].start = 0;
//     }

//     return 0;

// }
bool init(t_main *philo)
{
    int i = -1;
    if (!(philo->fork = malloc(sizeof(pthread_mutex_t) * philo->data.nb_of_thread)))
        return 1;
    if (!(philo->thread = malloc(sizeof(t_philo) * philo->data.nb_of_thread)))
        return 1;

    pthread_mutex_init(&philo->write_msg, NULL);
    pthread_mutex_init(&philo->die_msg, NULL);
    pthread_mutex_init(&philo->eat_msg, NULL);
    pthread_mutex_init(&philo->time, NULL);
    pthread_mutex_init(&philo->mx_meals, NULL);

    while (++i < philo->data.nb_of_thread)
        pthread_mutex_init(&philo->fork[i], NULL);
    i = -1;

    while (++i < philo->data.nb_of_thread)
    {
        if (i + 1 == philo->data.nb_of_thread)
            philo->thread[i].l_fork = &philo->fork[0];
        else
            philo->thread[i].l_fork = &philo->fork[i + 1];
        
        philo->thread[i].philo = malloc(sizeof(pthread_t));
        philo->thread[i].id = i;
        philo->thread[i].mutxs = philo;
        philo->thread[i].data = &philo->data;
        philo->thread[i].r_fork = &philo->fork[i];
        philo->thread[i].last_eat = 0;
        philo->thread[i].meals = 0;
        philo->thread[i].die = 0;
        philo->thread[i].start = 1;
    }

    return 0;
}
#include "philo.h"

int     parse(t_data **datat ,char **av, int ac)
{
    *datat = malloc(sizeof(t_data));
    t_data *data = *datat;
    if (ac < 5 && ac > 6)
        return (0);
        printf("1\n");
    if((!check(av[1] , 0) || !check(av[2] , 1) ||
            !check(av[3] , 1) || !check(av[4] , 1)))
    {

                return 0;
    }
        printf("1\n");
    if(ac == 6)
    {
        if(!check(av[5] , 1))
            return 0;
        data->max_meals = atoi(av[5]);
    }
        printf("1\n");
    data->nb_of_thread = my_atoi(av[1]);
    data->time_to_die = my_atoi(av[2]);
    data->time_to_eat = my_atoi(av[3]);
    data->time_to_sleep = my_atoi(av[4]);
    data->die = 0;
        printf("1\n");
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
void init(t_data *philo)
{
    int i = 0;
        printf("2\n");
    if(!(philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nb_of_thread)))
        return;
        printf("2\n");
    if(!(philo->thread = malloc(sizeof(t_philo) * philo->nb_of_thread)))
        return;
        printf("1\n");
    while(i < philo->nb_of_thread)
    {
        philo->thread[i].philo =  malloc(sizeof(pthread_t));
        philo->thread[i].id = i;
        philo->thread[i].data = philo;
        philo->thread[i].last_eat = 0;
        i++;
        // philo->thread[i].r_fork = malloc(sizeof(pthread_mutex_t));
        // philo->thread[(i + 1) % philo->nb_of_thread].l_fork = malloc(sizeof(pthread_mutex_t));
    }
        printf("1\n");
    pthread_mutex_init(&philo->write_msg,NULL);
    pthread_mutex_init(&philo->die_msg,NULL);
    pthread_mutex_init(&philo->eat_msg,NULL);
        printf("1\n");
    i = -1;
        printf("1\n");
    while(++i < philo->nb_of_thread)
        pthread_mutex_init(&philo->forks[i],NULL);
        printf("1\n");
    i = -1;
    while(++i < philo->nb_of_thread)
    {
        philo->thread[i].r_fork = philo->forks[i];
        philo->thread[i].l_fork = philo->forks[(i + 1) % philo->nb_of_thread];
    }
        printf("1\n");

}
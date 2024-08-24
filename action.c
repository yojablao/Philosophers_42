#include "philo.h"
// int     snitch(t_philo *philo)
// {
//     long    time =gettime;
// 10 90
// }
int  getfork_eat(t_philo *philo)
{
        pthread_mutex_lock(philo->l_fork);
        printing(philo,*philo->data,"l_fork");
        // if(sta == 1)
        // printf("%ld\n",philo->data->time_to_eat * 1000);
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(&philo->mutxs->eat_msg);

        printing(philo,*philo->data,"r_fork");
        printing(philo,*philo->data,"eat");
        ft_usleep(philo->data->time_to_eat * 1000);
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(&philo->mutxs->eat_msg);
        // pthread_mutex_lock(&philo->mutxs->time);
        philo->last_eat = gettime();
        // pthread_mutex_unlock(&philo->mutxs->time);
        // pthread_mutex_lock(&philo->mutxs->eat_msg);
        // pthread_mutex_lock(&philo->mutxs->mx_meals);
        philo->meals += 1;
        if(!(philo->meals < philo->data->max_meals ))
        {
            philo->die = 1;
            return(1);
            
        }
        // pthread_mutex_unlock(&philo->mutxs->mx_meals);
        return 0;
}

int  sleep_think(t_philo *philo)
{
    printing(philo,*philo->data, "sleep");
    ft_usleep(philo->data->time_to_sleep * 1000);
    printing(philo,*philo->data, "think");
    philo->start = gettime();
        return 0;
}

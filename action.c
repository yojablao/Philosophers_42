#include "philo.h"
// int     snitch(t_philo *philo)
// {
//     long    time =gettime;
// 10 90
// }
long    s_time(t_data data)
{
    return(gettime() - data.start_time);
}
// int if_dei(t_philo *philo ,t_data *data)
// {
//     pthread_mutex_lock(&philo->mutxs->time);
//     if( gettime() - philo->start > data->time_to_die)
//     {
//         pthread_mutex_unlock(&philo->mutxs->time);
        
//     }
//     pthread_mutex_unlock(&philo->mutxs->time);
//         return (0);
// }
int  getfork_eat(t_philo *philo)
{
        pthread_mutex_lock(philo->l_fork);
        printing(philo,*philo->data,"l_fork");
        // if(if_dei(philo,philo->data) == 1)
        //     return(printing(philo,*philo->data,"die"),1);
        pthread_mutex_lock(philo->r_fork);
        pthread_mutex_lock(&philo->mutxs->eat_msg);
        printing(philo,*philo->data,"r_fork");
        printing(philo,*philo->data,"eat");
        ft_usleep(philo->data->time_to_eat * 1000);
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(&philo->mutxs->eat_msg);
        // pthread_mutex_lock(&philo->mutxs->time);
        philo->last_eat = s_time(data);
        // pthread_mutex_unlock(&philo->mutxs->time);
        // pthread_mutex_lock(&philo->mutxs->eat_msg);
        // pthread_mutex_lock(&philo->mutxs->mx_meals);
        philo->meals += 1;
        if(!(philo->meals < philo->data->max_meals ))
        {
            philo->die = 1;
            return(1);
        }
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

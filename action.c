#include "philo.h"

long    s_time(long data)
{
    return(gettime() - data);
}
bool check_meals(int a,int b)
{
    if(a > b && a != -1)
        return 1;
    return 0;

}
bool    check_time(long time,long   max_time)
{
    if(time > max_time)
        return 1;
    return 0;

}
void if_die(t_main *philo)
{
    int i;
    bool flage;

    while (1)
    {
        i = -1;
        flage = true;

        while (++i < philo->data.nb_of_thread)
        {
            pthread_mutex_lock(&philo->mutex->time);
            if (gettime() - philo->threads[i].last_eat > philo->data.time_to_die)
            {
                printing(&philo->threads[i], s_time(philo->data.start_time), "died");
                pthread_mutex_unlock(&philo->mutex->time);
                return ;
            }

            pthread_mutex_unlock(&philo->mutex->time);

            pthread_mutex_lock(&philo->mutex->mx_meals);

            // Check if all philosophers have eaten enough times
            if (philo->data.max_meals != -1 && philo->threads[i].meals < philo->data.max_meals)
                flage = false;

            pthread_mutex_unlock(&philo->mutex->mx_meals);
        }

        if (philo->data.max_meals != -1 && flage)
        {
            pthread_mutex_lock(&philo->mutex->write_msg);
            printf("All philosophers have eaten enough times.\n");
            // pthread_mutex_unlock(&philo->mutex->write_msg);
            return ;
        }

        ft_usleep(100); // Sleep for a short time before checking again
    }
}


int  getfork_eat(t_philo *philo)
{
        pthread_mutex_lock(philo->l_fork);
        printing(philo,s_time(philo->data->start_time),"l_fork");
        pthread_mutex_lock(philo->r_fork);
        // pthread_mutex_lock(&philo->mutxs->eat_msg);
        printing(philo,s_time(philo->data->start_time),"r_fork");
        printing(philo,s_time(philo->data->start_time),"eat");
        ft_usleep(philo->data->time_to_eat * 1000);
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        // pthread_mutex_unlock(&philo->mutxs->eat_msg);
        pthread_mutex_lock(&philo->mutxs->mx_meals);
        philo->meals += 1;
        pthread_mutex_unlock(&philo->mutxs->mx_meals);
        return 0;
}

int  sleep_think(t_philo *philo)
{
    printing(philo,s_time(philo->data->start_time), "sleep");
    ft_usleep(philo->data->time_to_sleep * 1000);
    printing(philo,s_time(philo->data->start_time), "think");
    philo->start = gettime();
        return 0;
}

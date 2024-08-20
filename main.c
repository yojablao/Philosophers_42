#include "philo.h"

long gettime()
{
    struct timeval t;

    gettimeofday(&t, NULL);
    return ((t.tv_sec * 1000 + (t.tv_usec / 1000)));
}
void    printing(t_philo *data, char *cases)
{
    static long int time;

    pthread_mutex_lock(&data->mutxs->write_msg);
    time = gettime();
    if(strcmp(cases, "l_fork") == 0)
        printf("%ld %ld has taken a  l fork\n", gettime() -  data->data->start_time  ,data->id);
    if(strcmp(cases, "r_fork") == 0)
        printf("%ld %ld has taken a  r fork\n", gettime() -  data->data->start_time  ,data->id);
    else if(strcmp(cases, "eat") == 0)
        printf("%ld %ld is eating\n", gettime() - data->data->start_time,data->id);
    else if(strcmp(cases, "sleep") == 0)
        printf("%ld %ld is sleeping\n", gettime() -  data->data->start_time,data->id);
    else if(strcmp(cases, "think") == 0)
        printf("%ld %ld  is thinking\n",gettime() -  data->data->start_time,data->id);
    else if(strcmp(cases, " die") == 0)
        printf("%ld %ld died\n",gettime() -  data->data->start_time,data->id);
    pthread_mutex_unlock(&data->mutxs->write_msg);
}
int	ft_usleep(long int time)
{
	long int	start_time;

	start_time = gettime();
	while ((gettime() - start_time) * 1000 < time)
        usleep(150);
	return (1);
}

void endit(t_main *philo)
{
    int i = -1;
    while(++i < philo->data.nb_of_thread)
        pthread_join(philo->thread[i].philo,NULL);
}

void *philo_routine(void *main)
{
    t_philo *philo = (t_philo *)main;

    if(philo->id == 0)
        philo->mutxs->data.start_time = gettime();
    while(philo->meals <= philo->data->max_meals)
    {
        pthread_mutex_lock(philo->l_fork);
        printing(philo,"l_fork");
        pthread_mutex_lock(philo->r_fork);
        printing(philo,"r_fork");
        pthread_mutex_unlock(philo->l_fork);
        pthread_mutex_unlock(philo->r_fork);
        pthread_mutex_lock(&philo->mutxs->eat_msg);
        printing(philo,"eat");
        ft_usleep(philo->data->time_to_eat * 1000);
        pthread_mutex_unlock(&philo->mutxs->eat_msg);
        pthread_mutex_lock(&philo->mutxs->time);
        philo->last_eat = gettime();
        pthread_mutex_unlock(&philo->mutxs->time);
        pthread_mutex_lock(&philo->mutxs->mx_meals);
        philo->meals++;
        pthread_mutex_unlock(&philo->mutxs->mx_meals);
        printing(philo, "sleep");
        ft_usleep(philo->data->time_to_sleep * 1000);
        printing(philo, "think");
        pthread_mutex_lock(&philo->mutxs->time);
        philo->start = gettime();
        pthread_mutex_unlock(&philo->mutxs->time);
    }
    return NULL;
}

void    if_die(t_main *main)
{
        int i;
             
    ft_usleep(main->data.time_to_die);
    while (main->die == false)
    {
        i = -1;
        while(++i < main->data.nb_of_thread)
        {
            // printf("lol");
            pthread_mutex_lock(&main->time);
            pthread_mutex_lock(&main->mx_meals);
            if( main->thread[i].start >  main->data.time_to_die + main->thread[i].meals || main->data.max_meals <= main->thread[i].meals)
            {
                pthread_mutex_lock(&main->die_msg);
                main->die = true;
                printing(&main->thread[i],"die");    
                pthread_mutex_unlock(&main->die_msg);
                pthread_mutex_unlock(&main->time);
                pthread_mutex_unlock(&main->mx_meals);
                return;
            }       
            pthread_mutex_unlock(&main->time);
            pthread_mutex_unlock(&main->mx_meals);
        }
    }
}
int main(int ac ,char **av)
{

    int i = -1;
    if(ac > 6 || ac < 5)
        return(printf("0lol\n"),0);

    t_main philo;
    if( !parse(&philo,av,ac))
        return(printf("2lol\n"),1);
    if(init(&philo) != 0)
        return(printf("5rejna\n"),1);
    while(++i < philo.data.nb_of_thread)
        if(pthread_create(&philo.thread[i].philo,NULL,&philo_routine,&philo.thread[i]) != 0 )
            return 1;
    if_die(&philo);

    endit(&philo);
        
    return 0;

}
#include "philo.h"

long gettime()
{
    struct timeval t;

    gettimeofday(&t, NULL);
    return ((t.tv_sec * 1000 + (t.tv_usec / 1000)));
}
void    printing(t_philo *data, t_data lol,char *cases)
{
    // static long int time = gettime();


    if(pthread_mutex_lock(&data->mutxs->write_msg) != 0)
        return ;
    if(strcmp(cases, "l_fork") == 0)
        printf("%ld %ld has taken a fork\n", gettime() -  lol.start_time  ,data->id);
    else if(strcmp(cases, "r_fork") == 0)
        printf("%ld %ld has taken a  r fork\n", gettime() -  lol.start_time  ,data->id);
    else if(strcmp(cases, "eat") == 0)
        printf("%ld %ld is eating\n", gettime() - lol.start_time,data->id);
    else if(strcmp(cases, "sleep") == 0)
        printf("%ld %ld is sleeping\n", gettime() -  lol.start_time,data->id);
    else if(strcmp(cases, "think") == 0)
        printf("%ld %ld  is thinking\n",gettime() -  lol.start_time,data->id);
    else if(strcmp(cases, " die") == 0)
        printf("%ld %ld died\n",gettime() -  data->data->start_time,data->id);
    pthread_mutex_unlock(&data->mutxs->write_msg);
 
}
int	ft_usleep(long int time)
{
	long int	start_time;

	start_time = gettime();
    
        usleep(time);
    if(((gettime() - start_time) * 1000 ) < time)
        usleep(100);
	return (1);
}

void    free_all(t_main *philo)
{
    int i = -1;
    while(++i < philo->data.nb_of_thread)
        pthread_mutex_destroy(&philo->fork[i]);
    pthread_mutex_destroy(&philo->write_msg);
    pthread_mutex_destroy(&philo->die_msg);
    free(philo->fork);
    free(philo->thread);
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
        philo->data->start_time = gettime();
    if(philo->id % 2 == 0)
        ft_usleep(philo->data->time_to_die * 500);
    while(philo->die == 0)
    {
        if(getfork_eat(philo) == 1)
            return (NULL);
        sleep_think(philo);
    }
    
    return NULL;
}

int    stop(t_main *main)
{
    int i;
             
    // ft_usleep(main->data.time_to_die);
    i = -1;
    while (main->die == false)
    {
        while(++i < main->data.nb_of_thread)
        {
        //     printf("lol\n");
        //     pthread_mutex_lock(&main->time);
        //     pthread_mutex_lock(&main->mx_meals);
            if( main->thread[i].start >  main->data.time_to_die + main->thread[i].meals || main->data.max_meals <= main->thread[i].meals)
            {
                // pthread_mutex_lock(&main->die_msg);
                // main->die = true;
                // pthread_mutex_unlock(&main->die_msg);
                pthread_mutex_unlock(&main->time);
                pthread_mutex_unlock(&main->mx_meals);
                return 1;
            }       
        //     pthread_mutex_unlock(&main->time);
        //     pthread_mutex_unlock(&main->mx_meals);
        }
    }
    return 0;
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
    // if(stop(&philo) == 1)
    //      return(printing(&philo.thread[i],"die"),free_all(&philo) , 1);
    endit(&philo);

        
    return 0;

}
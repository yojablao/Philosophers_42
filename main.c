#include "philo.h"

long gettime()
{
    struct timeval t;

    gettimeofday(&t, NULL);
    return ((t.tv_sec * 1000 + (t.tv_usec / 1000)));
}

void    printing(char *s, long time, char *cases,long    id)
{
    (void)s;
    if(strcmp(cases, "l_fork") == 0)
        printf("%ld, %ld has taken a left fork\n", time * 1000 ,id);
    else if(strcmp(cases, "r_fork") == 0)
        printf("%ld, %ld has taken a right fork\n", time * 1000 ,id);
    else if(strcmp(cases, "eat") == 0)
        printf("%ld, %ld is eating\n", time * 1000,id);
    else if(strcmp(cases, "sleep") == 0)
        printf("%ld, %ld is sleeping\n", time * 1000,id);
    else if(strcmp(cases, "think") == 0)
        printf("%ld, %ld  is thinking\n",time* 1000,id);
    else if(strcmp(cases, " die") == 0)
        printf("%ld, %ld died\n",time * 1000,id);
}


void stop_all(t_data    *main)
{
    int i = -1;
    
    pthread_mutex_lock(&main->die_msg);
    pthread_mutex_lock(&main->write_msg);
    pthread_mutex_lock(&main->eat_msg);
    while(++i < main->nb_of_thread)
        pthread_mutex_lock(&main->forks[i]);
} 
void    if_die(t_philo *philo)
{
    if(gettime() - philo->start >  philo->data->time_to_die)
    {

        // stop_all(&*philo->main_struct);
        pthread_mutex_lock(&philo->data->die_msg);
        philo->data->die = true;
        // printf("%d",philo->data->die);  
        printing(NULL,gettime(),"die",philo->id);
        // pthread_mutex_unlock(&philo->data->die);
    }
}
int    get_forks(t_philo *philo)
{
    philo->start = gettime();
    pthread_mutex_lock(&philo->r_fork);
    // sleep(10);
    printing(NULL,gettime(),"r_fork",philo->id);
    pthread_mutex_lock(&philo->l_fork);
    // if_die(philo);
    printing(NULL,gettime(),"l_fork",philo->id);
    if(philo_eat(philo) == 1)
        return(1);
    pthread_mutex_unlock(&philo->l_fork);
    pthread_mutex_unlock(&philo->r_fork);
    return 0;

}
int    philo_eat(t_philo *philo)
{
    // if( (gettime() - philo->start)  >  philo->data->time_to_die)
    // {
    //     // pthread_mutex_lock(&philo->data->die_msg);
    //     // stop_all(&philo->data);
    //     printf("die\n");
    //     philo->data->die = 1;
    //     return(1);
    // }
    pthread_mutex_lock(&philo->data->eat_msg);
    // printing(NULL,get,"%d\n",philo->data->die);
    printing(NULL,gettime(),"eat",philo->id);
    usleep(philo->data->time_to_eat *1000);
    pthread_mutex_unlock(&philo->data->eat_msg);
    return 0;

}
int   philo_sleep(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->write_msg);
    printing(NULL,gettime() ,"sleep",philo->id);
    usleep(philo->data->time_to_sleep * 1000 );
    printing(NULL,gettime() ,"think",philo->id);
    philo->start = gettime();
    pthread_mutex_unlock(&philo->data->write_msg);
    return (0);
}
void *philo_routine(void *main)
{
    t_philo *philo = (t_philo *)main;
    if(philo->id % 2 == 0)
        usleep(philo->data->time_to_die * 1000);
    philo->start = gettime();
    while(1)
    {
        if(philo->data->die == 1)
            return 0;
        if(get_forks(philo) == 1)
            break;
        philo_sleep(philo);
        printing(NULL,gettime()/1000 ,"think",philo->id);
        philo->start = gettime();
    }
    printf("out");
    return NULL;
    
}

int main(int ac ,char **av)
{

    int i = 0;
    if(ac > 6 || ac < 5)
        return(printf("0lol\n"),0);

    t_data *philo;
    if( !parse(&philo,av,ac))
        return(printf("2lol\n"),1);
    init(philo);
    while (i < philo->nb_of_thread)
    {
        pthread_create(&philo->thread[i].philo,NULL,&philo_routine,&philo->thread[i]);
        i++;
    }
   while(--i >= 0)
        pthread_join(philo->thread[i].philo,NULL);
    return 0;

}
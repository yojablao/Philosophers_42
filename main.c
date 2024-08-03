#include "philo.h"

// int	init_mutex(t_rules *rules)
// {
// 	int	i;

// 	i = 0;
// 	while (i < rules->philo_count)
// 	{
// 		if (pthread_mutex_init(&(rules->forks[i]), NULL))
// 			return (1);
// 		i++;
// 	}
// 	if (pthread_mutex_init(&(rules->writing), NULL))
// 		return (1);
// 	if (pthread_mutex_init(&(rules->meal_check), NULL))
// 		return (1);
// 	return (0);
// }

// t_philo	*ft_lstnew(int id,t_philo *car)
// {
// 	t_philo	*node;
//     // car = car->next;

//     node = malloc(sizeof (t_philo ));
//     // memcpy(&car,&node,sizeof(t_philo));
//     init(node);
// 	node->id = id;
//     return(node);
// }
// // void    *routine(void *car)
// // {
// //     static int i = 0;

// //     pthread_mutex_lock(&(((t_philo *)car)->mutex));
// //     i++;
// //     t_philo *philo = ft_lstnew(i,(t_philo*)car);
// //     // init()
   
// //     printf("1:my id is -> %li\n",philo->id);
// //     printf("2;my time_to_die -> %li\n",philo->time_to_die);
// //     printf("3:my time_to_fuel is -> %li\n",philo->time_to_fuel);
// //     printf("4:how mine time_to_fuel -> %li\n",philo->time_to_fuel);
// //     printf("5:my time_to_race                                                         -> %li\n",philo->time_to_race);
// //     while (philo->time_to_fuel >= 0)
// //     {
        
// //         printf("5:raceing                                                         -> %li\n",philo->time_to_fuel);
// //         // usleep(10);
// //         philo->time_to_fuel--;
        
// //     }
    
// //     // philo->id++;
// //     pthread_mutex_unlock(&(((t_philo*)car)->mutex));


// //     return NULL;
// // }


// void    *bank(void *s)
// {
//     t_main *philo = (t_main *)s;
//     pthread_mutex_lock(&philo->eat);
//     if(philo->data.full > philo->data.nb_of_thread)
//     {
//         philo->data.full -= philo->data.nb_of_thread;
//         printf("done my amont is %ld\n",philo->data.full);
//     }
//     else
//         printf("fail\n");

//     pthread_mutex_unlock(&philo->eat);
//     return  NULL;

// }
int     parse(t_data *data ,char **av, int ac)
{
    if(ac < 5 && ac > 6)
        return(0);
    if((!check(av[1] , 0) || !check(av[2] , 1) ||
            !check(av[3] , 1) || !check(av[4] , 1)))
    {

                return 0;
    }
    if(ac == 6)
    {
        if(!check(av[5] , 1))
            return 0;
        data->max_meals = av[5];
    }
    data->nb_of_thread = my_atoi(av[1]);
    data->time_to_die = my_atoi(av[2]);
    data->time_to_eat = my_atoi(av[3]);
    data->time_to_sleep = my_atoi(av[4]);
    data->die = false;
    return(true);
}
void    init_data(t_data *dest,t_data src)
{
    dest->nb_of_thread = src.nb_of_thread;
    dest->time_to_die = src.time_to_die;
    dest->time_to_eat = src.time_to_eat;
    dest->time_to_sleep = src.time_to_sleep;
    dest->die = false;
    dest->meals = 0;

}
void init(t_main *philo)
{
    int i = 0;
    philo->thread = malloc(sizeof(t_philo *) * philo->data.nb_of_thread);
    while(i <= philo->data.nb_of_thread)
    {
        philo->thread[i].philo =  malloc(sizeof(pthread_t));
        philo->thread[i].id = i;
        philo->thread[i].r_fork = i;
        philo->thread[i].l_fork = (i + 1) % philo->data.nb_of_thread;
        philo->thread[i].data =  malloc(sizeof(t_data));
        init_data(&philo->thread[i].data,philo->data);
        i++;
    }
    i = 0;
    while(i <= philo->data.nb_of_thread)
    {
        pthread_mutex_init(&philo->fork[i],NULL);
        i++;
    }

}
void *philo_routine(void *main)
{
    t_philo *philo = (t_philo *)main;
    if(philo->id == 0)
        usleep(philo->data.time_to_eat);
    
}
int main(int ac ,char **av)
{

    int i = 0;

    if(ac > 6 || ac < 5)
        return(printf("0lol\n"),0);

    t_main philo;

    pthread_mutex_init(&philo.eat,NULL);
    if( !parse(&philo.data,av,ac))
        return(printf("2lol\n"),1);
    init(&philo);
    philo.data.nb_of_thread = atoi(av[1]);
    philo.data.full = atoi(av[2]);
        // printf("done\n");
    while (i < philo.data.nb_of_thread)
    {
        pthread_create(&philo.thread[i].philo,NULL,&philo_routine,&philo.thread[i]);
        i++;
    }
        // printf("done\n");
    while (--i >= 0)
        pthread_join(philo.thread[i].philo,NULL);
        // printf("done\n");
    return 0;

}
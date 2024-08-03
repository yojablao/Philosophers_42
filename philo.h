#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
// # include "lib/libft/libft.h"
struct t_main;
typedef struct s_data
{
    long    nb_of_thread;
    long    meals;
    long    max_meals;
    long    time_to_eat;
    long    time_to_sleep;
    long    time_to_die;
    bool    die;

}t_data;
typedef     struct  s_philo
{
    long    id;
    pthread_t   philo;
    int l_fork;
    int r_fork;
    struct t_data  *data;
}t_philo;

int check(char *s, int flag);
long	my_atoi(const char *str);
typedef     struct  main_struct
{
    t_data  data;
    pthread_mutex_t eat;
    pthread_mutex_t fork[250];
    pthread_mutex_t write;
    t_philo   *thread;
}t_main;


int pars(char **av, int ac);

#endif
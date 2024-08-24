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

typedef struct s_philo t_philo;
typedef struct s_data t_data;

typedef struct s_data
{
    long            nb_of_thread;
    long            max_meals;
    long            time_to_eat;
    long            time_to_sleep;
    long            time_to_die;
    long            start_time;
}  t_data ;

t_data          data;
typedef struct  s_main
{
    t_data          data;
    t_philo         *thread;
    pthread_mutex_t *fork;
    pthread_mutex_t mx_meals;
    pthread_mutex_t eat_msg;
    pthread_mutex_t sleep_msg;
    pthread_mutex_t time;
    pthread_mutex_t write_msg;
    pthread_mutex_t die_msg;
    bool            die;

}   t_main;


typedef struct s_philo
{
    bool            die;
    long            last_eat;
    long            meals;
    long            start;
    pthread_t       philo;
    long            id;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    t_data          *data;
    t_main      *mutxs;

}   t_philo;
void    printing(t_philo *data, t_data lol,char *cases);
void *philo_routine(void *main);
int     check(char *s, int flag);
long    my_atoi(const char *str);
bool    init(t_main *philo);
long gettime();
int  getfork_eat(t_philo *philo);
int  sleep_think(t_philo *philo);
int	ft_usleep(long int time);
int     parse(t_main *data, char **av, int ac);
 
#endif


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

typedef struct s_data
{
    bool            die;
    pthread_mutex_t eat_msg;
    pthread_mutex_t write_msg;
    pthread_mutex_t die_msg;
    pthread_mutex_t *forks;
    t_philo         *thread;
    // t_philo         monitor;
    long            nb_of_thread;
    long            max_meals;
    long            time_to_eat;
    long            time_to_sleep;
    long            time_to_die;
}  t_data ;

struct s_philo
{
    long            id;
    long            meals;
    pthread_t       philo;
    pthread_mutex_t r_fork;
    pthread_mutex_t l_fork;
    long            last_eat;
    long            start;
    t_data          *data;
};
int    philo_eat(t_philo *philo);
int     check(char *s, int flag);
long    my_atoi(const char *str);
void    init(t_data *philo);
int     parse(t_data **data, char **av, int ac);

#endif


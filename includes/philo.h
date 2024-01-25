#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

typedef enum e_state
{
    EATING,
    SLEEPING,
    THINKING,
    DEAD, 
    LEFT, 
    RIGHT
}   t_state;

typedef struct s_philosopher
{
    pthread_t       ph_th;
    int             id;
    int             left_fork;
    int             right_fork;
    int             n_eaten;
    struct timeval  last_meal;
    struct s_args   *args;
}  t_philosopher;

typedef struct s_args
{
    struct timeval  start_time;
    int		        time_to_die;
    int		        time_to_eat;
    int		        time_to_sleep;
    int		        num_of_philosophers;
    int		        n_meals;
    unsigned int    is_dead;
    unsigned int    all_ate;
    t_philosopher   philosophers[250];
    pthread_mutex_t forks[250];
    pthread_mutex_t write_mutex;
}   t_args;

// utils.c
int     ft_atoi(const char *nptr);
unsigned long get_time_ms(struct timeval start_time);

// init_structs.c
void    s_args_init(t_args *args, int argc, char *argv[]);
void s_arrays_init(t_args *args);

// routine.c
void    *routine(void *arg);
void    *routine_basic(void *arg); //testing purpose, to be removed before the final submission

// errors.c
int argc_error_check(int argc);

//  free.c
void    free_mutexes(t_args *args);

// write_messages.c
void    write_message_estd(t_args *args, t_philosopher *philo, t_state state);
void    write_message_forks(t_args *args, t_philosopher *philo, t_state state);

// print.c - TESTING purpose --> to be removed before the final submission
void printf_test(t_args *args);

#endif
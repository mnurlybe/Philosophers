#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

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
    int id;
    pthread_t ph_th;
    int left_fork;
    int right_fork;
    struct s_args *args;
    pthread_mutex_t *forks;
}  t_philosoper;

typedef struct s_args
{
    int		        num_of_philosophers;
    int		        time_to_die;
    int		        time_to_eat;
    int		        time_to_sleep;
    int		        num_of_times_each_philosopher_must_eat;
    long long       start_time;
    pthread_mutex_t write_mutex;
}   t_args;

typedef struct s_arrays
{
    t_philosoper    philosophers[250];
    pthread_mutex_t forks[250];
}  t_arrays;


// utils.c
int     ft_atoi(const char *nptr);
long long get_start_timestamp(void);
long long get_current_timestamp(long long start_time);

// init_structs.c
void    s_args_init(t_args *args, int argc, char *argv[]);
void s_arrays_init(t_args *args, t_arrays *arrays);

// routine.c
void    *routine(void *arg);

// errors.c
int argc_error_check(int argc);

//  free.c
void    free_mutexes(t_arrays *arrays, t_args *args);

// write_messages.c
void    write_message_estd(t_philosoper *philo, t_state state);
void    write_message_forks(t_philosoper *philo, t_state state);

// print.c - TESTING purpose --> to be removed before the final submission
void printf_test(t_args *args);

#endif
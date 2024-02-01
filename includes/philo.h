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
    FORK
}   t_state;

typedef struct s_philosopher
{
    pthread_t       th;
    int             id;
    unsigned int    left_fork;
    unsigned int    right_fork;
    unsigned int    n_eaten;
    unsigned long   ph_start_time;
    unsigned long   last_meal;
    struct s_args   *args;
    pthread_mutex_t ph_act_mutex;
}  t_philosopher;

typedef struct s_args
{
    int    n_of_ph;
    unsigned int    time_to_die;
    unsigned int    time_to_eat;
    unsigned int    time_to_sleep;
    int		        n_meals;
    unsigned int    end;
    unsigned long  start_time;
    pthread_t       stop_th;
    t_philosopher   philosophers[250];
    pthread_mutex_t forks[250];
    pthread_mutex_t write_mutex;
    pthread_mutex_t end_mutex;
}   t_args;

// errors.c
int argc_error_check(int argc);
int argv_error_check(int argc, char **argv);

// init_structs.c
t_args    *init_args(int argc, char **argv);

// print.c - TESTING purpose --> to be removed before the final submission
void printf_test(t_args *args);
void print_philo(t_philosopher *philo);

//  free.c
void    free_mutexes(t_args *args);

// utils.c
int     ft_atoi(const char *nptr);
unsigned long gettimeofday_long(void);
unsigned long get_time_ms(unsigned long start_time);
void    swap_forks(t_args *args);

//routine_new.c
void *philo_routine(void *args);

//stop_philo.c
void    *stop_checker(void *args);

// write_messages.c
void    write_message_estd(t_philosopher *philo, t_state state);
void    write_message_forks(t_philosopher *philo);

#endif
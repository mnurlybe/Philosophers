#include "includes/philo.h"

/**
 * initialize the struct with the arguments that were passed to the program
*/
void    s_args_init(t_args *args, int argc, char *argv[])
{
    args->num_of_philosophers = ft_atoi(argv[1]);
    args->time_to_die = ft_atoi(argv[2]);
    args->time_to_eat = ft_atoi(argv[3]);
    args->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        args->num_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    else
        args->num_of_times_each_philosopher_must_eat = -1;
    pthread_mutex_init(&args->write_mutex, NULL);
}

/**
 * Initialize the mutexes for forks array in t_arrays struct
 * and
 * the philosopher's information for each t_philosopher
 * and store it in the philosophers array in t_arrays struct;
*/
void s_arrays_init(t_args *args, t_arrays *arrays)
{
    int i;

    // initialize mutexes for each fork
    i = -1;
    while (++i < args->num_of_philosophers)
        pthread_mutex_init(&arrays->forks[i], NULL);

    //initialize each philosopher: s_philosopher struct 
    i = 0;
    while (i < args->num_of_philosophers)
    {
        arrays->philosophers[i].id = i;
        arrays->philosophers[i].left_fork = i;
        arrays->philosophers[i].right_fork = (i + 1) % args->num_of_philosophers;
        arrays->philosophers[i].args = args;
        arrays->philosophers[i].forks = arrays->forks;
        printf("philo id: %d, left_fork: %d, right_fork: %d\n", arrays->philosophers[i].id, arrays->philosophers[i].left_fork, arrays->philosophers[i].right_fork);
        i++;
    }
}
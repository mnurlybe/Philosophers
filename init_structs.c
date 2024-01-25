#include "includes/philo.h"

/**
 * Initialize the mutexes for forks array in t_arrays struct
 * and
 * the philosopher's information for each t_philosopher
 * and store it in the philosophers[250] array in t_args struct;
*/

//initialize each philosopher: s_philosopher struct 
void s_arrays_init(t_args *args)
{
    int i;

    i = 0;
    while (i < args->num_of_philosophers)
    {
        args->philosophers[i].id = i;
        args->philosophers[i].left_fork = i;
        args->philosophers[i].right_fork = (i + 1) % args->num_of_philosophers;
        if (args->n_meals > 0)
            args->philosophers[i].n_eaten = 0;
        else
            args->philosophers[i].n_eaten = -1;
        i++;
    }
}

void    s_args_init(t_args *args, int argc, char *argv[])
{
    int i;

    // init input arguments
    args->num_of_philosophers = ft_atoi(argv[1]);
    args->time_to_die = ft_atoi(argv[2]);
    args->time_to_eat = ft_atoi(argv[3]);
    args->time_to_sleep = ft_atoi(argv[4]);
    args->all_ate = FALSE;
    args->is_dead = FALSE;
    if (argc == 6)
        args->n_meals = ft_atoi(argv[5]);
    else
        args->n_meals = -1;

    // initialize mutexes
    pthread_mutex_init(&args->write_mutex, NULL);

    // initialize mutexes for each fork
    i = -1;
    while (++i < args->num_of_philosophers)
        pthread_mutex_init(&(args->forks[i]), NULL);

    s_arrays_init(args);
}
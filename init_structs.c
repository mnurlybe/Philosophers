#include "includes/philo.h"

int init_philo(t_args *args)
{
    int i;

    i = 0;
    while (i < args->n_of_ph)
    {
        args->philosophers[i].id = i;
        args->philosophers[i].left_fork = i;
        args->philosophers[i].right_fork = (i + 1) % args->n_of_ph;
        if (args->n_meals > 0)
            args->philosophers[i].n_eaten = 0;
        else
            args->philosophers[i].n_eaten = -1;
        args->philosophers[i].args = args;
        args->philosophers[i].ph_start_time = args->start_time;
        args->philosophers[i].last_meal = args->start_time;
        if (pthread_mutex_init(&args->philosophers[i].ph_act_mutex, NULL) != 0)
            return (FALSE);
        i++;
    }
    return (TRUE);
}

int init_mutexes(t_args *args)
{
    int i;

    i = -1;
    if (pthread_mutex_init(&args->write_mutex, NULL) != 0)
        return (FALSE);
    if (pthread_mutex_init(&args->end_mutex, NULL) != 0)
        return (FALSE);
    while (++i < args->n_of_ph)
    {
        if (pthread_mutex_init(&(args->forks[i]), NULL) != 0)
            return (FALSE);
    }
    return (TRUE);
}

t_args    *init_args(int argc, char **argv)
{
    t_args  *args;

    args = malloc(sizeof(t_args) * 1);
    if (!args)
        return (NULL);
    args->n_of_ph = ft_atoi(argv[1]);
    args->time_to_die = ft_atoi(argv[2]);
    args->time_to_eat = ft_atoi(argv[3]);
    args->time_to_sleep = ft_atoi(argv[4]);
    args->end = FALSE;
    if (argc == 6)
        args->n_meals = ft_atoi(argv[5]);
    else
        args->n_meals = -1;
    args->start_time = gettimeofday_long();
    if (!init_mutexes(args))
        return (NULL);
    if (!init_philo(args))
        return (NULL);
    return (args);
}

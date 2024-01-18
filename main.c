#include "includes/philo.h"

/**
 * Arguments:
 * Number_of_philisophers
 * time_to_die
 * time_to_eat
 * time_to_sleep
 * number_of_times_each_philosopher_must_eat
*/

int start_philosophers(t_arrays *arrays, t_args *args)
{
    int i;

    // get the start time of the simulation
    args->start_time = get_start_timestamp();

    // create threads for each philosopher
    i = -1;
    while (++i < args->num_of_philosophers)
        pthread_create(&arrays->philosophers[i].ph_th, NULL, &routine, &arrays->philosophers[i]);

    // wait for all philosopher threads to finish
    i = -1;
    while (++i < args->num_of_philosophers)
        pthread_join(arrays->philosophers[i].ph_th, NULL);

    return 0;
}

int main(int argc, char *argv[])
{
    t_args args;
    t_arrays array;

    if (argc_error_check(argc))
        return 1;
    s_args_init(&args, argc, argv);
    s_arrays_init(&args, &array);
    // printf_test(&args);
    start_philosophers(&array, &args);
    free_mutexes(&array, &args);
    return 0;
}
#include "includes/philo.h"

/**
 * Arguments:
 * Number_of_philisophers
 * time_to_die
 * time_to_eat
 * time_to_sleep
 * number_of_times_each_philosopher_must_eat (optional)
*/

int start_program(t_args *args)
{
    t_philosopher *philosophers;
    int i;

    philosophers = args->philosophers;

    // get the start time of the simulation
    gettimeofday(&args->start_time, NULL);

    // create threads for each philosopher
    i = -1;
    while (++i < args->num_of_philosophers)
    {
        philosophers[i].args = args;
        pthread_create(&(philosophers[i].ph_th), NULL, &routine_basic, &philosophers[i]);
    }

    // wait for all philosopher threads to finish
    i = -1;
    while (++i < args->num_of_philosophers)
        pthread_join(philosophers[i].ph_th, NULL);

    return 0;
}

int main(int argc, char *argv[])
{
    t_args args;

    if (argc_error_check(argc))
        return 1;
    s_args_init(&args, argc, argv);
    printf_test(&args);
    start_program(&args);
    free_mutexes(&args);
    return 0;
}
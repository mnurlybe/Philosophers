#include "includes/philo.h"

/**
 * free all the mutexes
*/
void    free_mutexes(t_arrays *arrays, t_args *args)
{
    int i;

    // destroy mutexes for each fork
    i = -1;
    while (++i < args->num_of_philosophers)
        pthread_mutex_destroy(&arrays->forks[i]);
    
    // destroy mutex for write
    pthread_mutex_destroy(&args->write_mutex);
}
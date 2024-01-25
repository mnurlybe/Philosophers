#include "includes/philo.h"

/**
 * print the arguments that were passed to the program
*/
void printf_test(t_args *args)
{
    printf("Number of philosophers: %d\n", args->num_of_philosophers);
    printf("Time to die: %d\n", args->time_to_die);
    printf("Time to eat: %d\n", args->time_to_eat);
    printf("Time to sleep: %d\n", args->time_to_sleep);
    printf("Number of times each philosopher must eat: %d\n", args->n_meals);
}

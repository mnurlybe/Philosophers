#include "includes/philo.h"

void printf_test(t_args *args)
{
    int i;

    printf("ARGS INFO:\n\n");
    printf("Number of philosophers: %d\n", args->n_of_ph);
    printf("Time to die: %d\n", args->time_to_die);
    printf("Time to eat: %d\n", args->time_to_eat);
    printf("Time to sleep: %d\n", args->time_to_sleep);
    printf("Number of meals: %d\n", args->n_meals);
    printf("Start_time: %ld\n", args->start_time);
    printf("Fork %d address: %p\n", 0, &args->forks[0]);
    printf("\n\n");
    printf("PHILOSOPHERS INFO:\n\n");
    i = 0;
    while (i < args->n_of_ph)
    {
        printf("Id: %d\n", args->philosophers[i].id);
        printf("lf: %d, rf: %d\n", args->philosophers[i].left_fork, args->philosophers[i].right_fork);
        printf("lf address %p\n", &args->philosophers[i].args->forks[args->philosophers[i].left_fork]);
        printf("rf address %p\n", &args->philosophers[i].args->forks[args->philosophers[i].right_fork]);
        printf("n_eaten: %d\n", args->philosophers[i].n_eaten);
        printf("start_time: %ld\n", args->philosophers[i].ph_start_time);
        printf("args n_of_philosophers: %d\n\n", args->philosophers[i].args->n_of_ph);
        i++;
    }
}

void print_philo(t_philosopher *philo)
{
    printf("\n\n PHILO THREAD\n\n");
    printf("Id: %d\n", philo->id);
    printf("lf: %d, rf: %d\n", philo->left_fork, philo->right_fork);
    printf("lf address %p\n", &philo->args->forks[philo->left_fork]);
    printf("rf address %p\n", &philo->args->forks[philo->right_fork]);
    printf("n_eaten: %d\n", philo->n_eaten);
    printf("start_time: %ld\n", philo->ph_start_time);
    printf("args n_of_philosophers: %d\n\n", philo->args->n_of_ph);
}

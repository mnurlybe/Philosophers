#include "includes/philo.h"

// void action_in_process(int time)
// {
//     long long i;

//     i = get_time_ms();
//     while(1)
//     {
//         if ((get_time_ms() - i) >= time)
//             break;
//         usleep(50);
//     }
// }

// routine with a loop
void    *routine(void *arg)
{
    t_args  *args;
    t_philosopher *philo;

    philo = (t_philosopher *)arg;
    args = philo->args;
    gettimeofday(&philo->last_meal, NULL);

    while (1)
    {
        // eating
        if ((philo->id + 1) % 2 == 0)
        {
            pthread_mutex_lock(&args->forks[philo->left_fork]);
            write_message_forks(args, philo, LEFT);
            pthread_mutex_lock(&args->forks[philo->right_fork]);
            write_message_forks(args, philo, RIGHT);
        }
        else
        {
            // printf("HELLO\n");
            pthread_mutex_lock(&args->forks[philo->right_fork]);
            write_message_forks(args, philo, RIGHT);
            pthread_mutex_lock(&args->forks[philo->left_fork]);
            write_message_forks(args, philo, LEFT);
        }
        // pthread_mutex_lock(&args->meal_mutex);
        write_message_estd(args, philo, EATING);
        // pthread_mutex_unlock(&args->meal_mutex);
        action_in_process(args->time_to_eat);
        (philo->n_eaten)++;
        // printf("philo %d ate %d times\n", philo->id + 1, philo->n_eaten);
        pthread_mutex_unlock(&args->forks[philo->left_fork]);
        pthread_mutex_unlock(&args->forks[philo->right_fork]);

        // check if all ate
        // printf("all_ate flag: %d\n", args->all_ate);
        if (args->all_ate)
            break;

        // Sleeping
        write_message_estd(args, philo, SLEEPING);
        action_in_process(args->time_to_sleep);

        // Thinking
        write_message_estd(args, philo, THINKING);
    }
    return NULL;
}

/**
 * base routine without loop
*/

void    *routine_basic(void *args)
{
    t_philosopher *philo;

    philo = (t_philosopher *)args;

    usleep(1000000);

    int id = philo->id;
    int left_fork = philo->left_fork;
    int right_fork = philo->right_fork;

    // synchronization
    if (id % 2 == 0)
    {
        pthread_mutex_lock(&args->forks[left_fork]);
        write_message_forks(args, philo, LEFT);
        pthread_mutex_lock(&args->forks[right_fork]);
        write_message_forks(args, philo, RIGHT);
    }
    else
    {
        pthread_mutex_lock(&args->forks[right_fork]);
        write_message_forks(args, philo, RIGHT);
        pthread_mutex_lock(&args->forks[left_fork]);
        write_message_forks(args, philo, LEFT);
    }

    write_message_estd(args, philo, EATING);

    // printf("%lld Philosopher %d is eating\n", get_current_timestamp(start_time), id + 1);
   
    // Simulate eating
    usleep(rand() % 1000000);


    pthread_mutex_unlock(&args->forks[left_fork]);
    pthread_mutex_unlock(&args->forks[right_fork]);

    // printf("%lld Philosopher %d is done eating\n", get_current_timestamp(start_time), id + 1);
    return NULL;
}
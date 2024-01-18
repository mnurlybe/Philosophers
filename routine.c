#include "includes/philo.h"

void    *routine(void *arg)
{
    t_philosoper *philo;

    philo = (t_philosoper *)arg;
    usleep(1000000);
    int id = philo->id;
    int left_fork = philo->left_fork;
    int right_fork = philo->right_fork;
    long long start_time = philo->args->start_time;

    // synchronization
    if (id % 2 == 0)
    {
        pthread_mutex_lock(&philo->forks[left_fork]);
        write_message_forks(philo, LEFT);
        pthread_mutex_lock(&philo->forks[right_fork]);
        write_message_forks(philo, RIGHT);
    }
    else
    {
        pthread_mutex_lock(&philo->forks[right_fork]);
        write_message_forks(philo, RIGHT);
        pthread_mutex_lock(&philo->forks[left_fork]);
        write_message_forks(philo, LEFT);
    }

    write_message_estd(philo, EATING);

    // printf("%lld Philosopher %d is eating\n", get_current_timestamp(start_time), id + 1);
   
    // Simulate eating
    usleep(rand() % 1000000);


    pthread_mutex_unlock(&philo->forks[left_fork]);
    pthread_mutex_unlock(&philo->forks[right_fork]);

    printf("%lld Philosopher %d is done eating\n", get_current_timestamp(start_time), id + 1);
    return NULL;
}
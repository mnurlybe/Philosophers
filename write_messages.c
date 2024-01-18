#include "includes/philo.h"

/**
 * prints a message to the console for eating, sleeping, thinking or dying states.
 * these messages are protected by mutex to prevent them from being printed at the same time.
*/
void    write_message_estd(t_philosoper *philo, t_state state)
{
    if (state == EATING)
    {
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%lld Philosopher %d is eating\n", get_current_timestamp(philo->args->start_time), philo->id + 1);
        pthread_mutex_unlock(&philo->args->write_mutex);
    }
    else if (state == SLEEPING)
    {
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%lld Philosopher %d is sleeping\n", get_current_timestamp(philo->args->start_time), philo->id + 1);
        pthread_mutex_unlock(&philo->args->write_mutex);
    }
    else if (state == THINKING)
    {
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%lld Philosopher %d is thinking\n", get_current_timestamp(philo->args->start_time), philo->id + 1);
        pthread_mutex_unlock(&philo->args->write_mutex);
    }
    else if (state == DEAD)
    {
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%lld Philosopher %d died\n", get_current_timestamp(philo->args->start_time), philo->id + 1);
        pthread_mutex_unlock(&philo->args->write_mutex);
    }
}

void write_message_forks(t_philosoper *philo, t_state state)
{
    if (state == LEFT)
        printf("%lld Philosopher %d has taken the left fork %d\n", get_current_timestamp(philo->args->start_time), philo->id + 1, philo->left_fork + 1); 
    else if (state == RIGHT)
        printf("%lld Philosopher %d has taken the right fork %d\n", get_current_timestamp(philo->args->start_time), philo->id + 1, philo->right_fork + 1);
}
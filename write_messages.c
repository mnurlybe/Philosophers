#include "includes/philo.h"

/**
 * prints a message to the console for eating, sleeping, thinking or dying states.
 * these messages are protected by mutex to prevent them from being printed at the same time.
*/
void    write_message_estd(t_philosopher *philo, t_state state)
{
    if (state == EATING)
    {
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%ld %d is eating\n", get_time_ms(philo->ph_start_time), philo->id + 1);
        pthread_mutex_unlock(&philo->args->write_mutex);
    }
    else if (state == SLEEPING)
    {
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%ld %d is sleeping\n", get_time_ms(philo->ph_start_time), philo->id + 1);
        pthread_mutex_unlock(&philo->args->write_mutex);
    }
    else if (state == THINKING)
    {
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%ld %d is thinking\n", get_time_ms(philo->ph_start_time), philo->id + 1);
        pthread_mutex_unlock(&philo->args->write_mutex);
    }
    else if (state == DEAD)
    {
        pthread_mutex_lock(&philo->args->write_mutex);
        printf("%ld %d died\n", get_time_ms(philo->ph_start_time), philo->id + 1);
        pthread_mutex_unlock(&philo->args->write_mutex);
    }
}

void write_message_forks(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->args->write_mutex);
    printf("%ld %d has taken a fork\n", get_time_ms(philo->ph_start_time), philo->id + 1); 
    pthread_mutex_unlock(&philo->args->write_mutex);
}
#include "includes/philo.h"

/**
 * prints a message to the console for eating, sleeping, thinking or dying states.
 * these messages are protected by mutex to prevent them from being printed at the same time.
*/
void    write_message_estd(t_args *args, t_philosopher *philo, t_state state)
{
    if (state == EATING)
    {
        pthread_mutex_lock(&args->write_mutex);
        printf("%lld %d is eating\n", get_time_ms(args->start_time), philo->id + 1);
        pthread_mutex_unlock(&args->write_mutex);
    }
    else if (state == SLEEPING)
    {
        pthread_mutex_lock(&args->write_mutex);
        printf("%lld %d is sleeping\n", get_time_ms(args->start_time), philo->id + 1);
        pthread_mutex_unlock(&args->write_mutex);
    }
    else if (state == THINKING)
    {
        pthread_mutex_lock(&args->write_mutex);
        printf("%lld %d is thinking\n", get_time_ms(args->start_time), philo->id + 1);
        pthread_mutex_unlock(&args->write_mutex);
    }
    else if (state == DEAD)
    {
        pthread_mutex_lock(&args->write_mutex);
        printf("%lld %d died\n", get_time_ms(args->start_time), philo->id + 1);
        pthread_mutex_unlock(&args->write_mutex);
    }
}

void write_message_forks(t_args *args, t_philosopher *philo, t_state state)
{
    if (state == LEFT)
        printf("%lld %d has taken a fork\n", get_time_ms(args->start_time), philo->id + 1); 
    else if (state == RIGHT)
        printf("%lld %d has taken a fork\n", get_time_ms(args->start_time), philo->id + 1);
}
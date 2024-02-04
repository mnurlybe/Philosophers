#include "includes/philo.h"

void    update_last_meal(t_philosopher *philo)
{
    pthread_mutex_unlock(&(philo->ph_act_mutex));
    philo->last_meal = gettimeofday_long();
    pthread_mutex_lock(&(philo->ph_act_mutex));
}
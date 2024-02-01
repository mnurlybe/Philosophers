/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:16:38 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/01 20:51:16 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void    *only_one_philo(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
    write_message_forks(philo);
    usleep(philo->args->time_to_die * 1000);
    write_message_estd(philo, DEAD);
    pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
    return (NULL);
}

int eat_sleep_think(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
    write_message_forks(philo);
    pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
    write_message_forks(philo);
    write_message_estd(philo, EATING);
    pthread_mutex_lock(&philo->ph_act_mutex);
    philo->last_meal = gettimeofday_long();
    pthread_mutex_unlock(&philo->ph_act_mutex);
    usleep(philo->args->time_to_eat * 1000);
    write_message_estd(philo, SLEEPING);
    pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
    pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
    usleep(philo->args->time_to_sleep * 1000);
    write_message_estd(philo, THINKING);
    return (TRUE);
}

void *philo_routine(void *arg)
{
    t_philosopher *philo;
    
    philo = (t_philosopher *)arg;

    // print_philo(philo);
    if (philo->args->n_of_ph == 1)
        return (only_one_philo(philo));
    else
    {
        while (philo->args->end == FALSE)
        {
            if (eat_sleep_think(philo) == FALSE)
                break;
        }
    }
    return (NULL);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:16:38 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/03 16:07:58 by mnurlybe         ###   ########.fr       */
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

int get_end_status(t_args *args)
{
    int status;

    status = FALSE;
    pthread_mutex_lock(&args->end_mutex);
    if (args->end == TRUE)
        status = TRUE;
    pthread_mutex_unlock(&args->end_mutex);
    return (status);
}

int action_in_process(t_args *args, unsigned int time_to_act)
{
    unsigned long local_start_time;

    local_start_time = get_time_ms(args->start_time);
    while((get_time_ms(args->start_time) - local_start_time) < time_to_act)
    {
        if (get_end_status(args) == TRUE)
            return (FALSE);
        usleep(50);
    }
    return (TRUE);
}

int eat_sleep_think(t_philosopher *philo)
{
    if (get_end_status(philo->args))
        return (FALSE);
    pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
    write_message_forks(philo);
    pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
    write_message_forks(philo);
    write_message_estd(philo, EATING);
    pthread_mutex_lock(&philo->ph_act_mutex);
    philo->last_meal = gettimeofday_long();
    pthread_mutex_unlock(&philo->ph_act_mutex);
    if (!action_in_process(philo->args, philo->args->time_to_eat))
    {
        pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
        pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);   
        return (FALSE);
    }
    pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
    pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
    write_message_estd(philo, SLEEPING);
    if (!action_in_process(philo->args, philo->args->time_to_sleep))
        return (FALSE);
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
        if (philo->id % 2)
            usleep(1000);
        while (get_end_status(philo->args) == FALSE)
        {
            if (eat_sleep_think(philo) == FALSE)
                break;
            // printf("End status %d\n", philo->args->end);
        }   
    }
    return (NULL);
}
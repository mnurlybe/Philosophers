/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:16:38 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/04 16:29:50 by mnurlybe         ###   ########.fr       */
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
        usleep(500);
    }
    return (TRUE);
}

int sleep_think(t_philosopher *philo)
{
    if (is_dead(philo) || get_end_status(philo->args))
        return (FALSE);
    write_message_estd(philo, SLEEPING);
    if (action_in_process(philo->args, philo->args->time_to_sleep) == FALSE)
        return (FALSE);
    if (is_dead(philo) || get_end_status(philo->args))
        return (FALSE);
    write_message_estd(philo, THINKING);
    return (TRUE);
}

void put_forks(t_philosopher *philo)
{
    pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
    pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);  
}

int take_forks(t_philosopher *philo)
{   
    if (is_dead(philo) || get_end_status(philo->args))
        return (FALSE);
    pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
    if (is_dead(philo) || get_end_status(philo->args))
    {
        pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
        return (FALSE);
    }
    write_message_forks(philo);
    pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
    if (is_dead(philo) || get_end_status(philo->args))
    {
        put_forks(philo);
        return (FALSE);
    }
    write_message_forks(philo);
    return (TRUE);
}

int eat(t_philosopher *philo)
{
    if (take_forks(philo) == FALSE)
        return (FALSE);
    write_message_estd(philo, EATING);
    update_last_meal(philo);
    if (action_in_process(philo->args, philo->args->time_to_eat) == FALSE)
    {
        put_forks(philo);   
        return (FALSE);
    }
    put_forks(philo);
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
        update_last_meal(philo);
        if (philo->id % 2 == 0)
        {
            write_message_estd(philo, THINKING);
            usleep((philo->args->time_to_eat / 2) * 1000);
        }
        while (get_end_status(philo->args) == FALSE)
        {
            if (eat(philo) == FALSE)
                return (NULL);
            if (is_dead(philo) || get_end_status(philo->args))
                return (NULL);
            if (sleep_think(philo) == FALSE)
                return (NULL);
        }   
    }
    return (NULL);
}
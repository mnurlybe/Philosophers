/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:42:14 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/03 15:03:25 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int is_dead(t_philosopher *philo)
{
    unsigned long time;
    
    time = gettimeofday_long();
    if ((time - philo->last_meal) >= philo->args->time_to_die)
        return (TRUE);
    return (FALSE);
}

void    *stop_checker(void *arg)
{
    t_args  *args;
    args = (t_args*)arg;
    
    pthread_mutex_lock(&args->end_mutex);
    args->end = FALSE;
    pthread_mutex_unlock(&args->end_mutex);
    int i;
    while (1)
    {
        i = -1;
        while (++i < args->n_of_ph)
        {
            pthread_mutex_lock(&args->philosophers[i].ph_act_mutex);
            if (is_dead(&(args->philosophers[i])))
            {
                pthread_mutex_lock(&args->end_mutex);
                args->end = TRUE;
                write_message_estd(&(args->philosophers[i]), DEAD);
                pthread_mutex_unlock(&args->end_mutex);
                pthread_mutex_unlock(&args->philosophers[i].ph_act_mutex);
                return (NULL);
            }
            pthread_mutex_unlock(&args->philosophers[i].ph_act_mutex);
        }
        usleep(1000);
    }
    return (NULL);
}
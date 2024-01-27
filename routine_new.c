/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:16:38 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/01/27 21:03:18 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void *philo_routine(void *args)
{
    t_philosopher *philo;
    
    philo = (t_philosopher *)args;

    // print_philo(philo);
    if (philo->args->n_of_ph == 1)
    {
        
    }
    return (NULL);
}
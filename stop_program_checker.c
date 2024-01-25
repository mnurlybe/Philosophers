/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_program_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:03:13 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/01/21 16:03:24 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * Fucntion checks if all philosophers ate n_meal.
 * If yes, then all_ate flag is set to 1 and
 * program stops.
*/

void    meals_checker(t_args *args, t_philosopher *philo)
{
    int i;
    int counter;

    counter = 0;
    while (args->all_ate == 0)
    {
        i = -1;
        // pthread_mutex_lock(&args->meal_mutex);
        while(++i < args->num_of_philosophers)
        {
            if (philo[i].n_eaten >= args->n_meals)
                counter++;
        }
        // pthread_mutex_unlock(&args->meal_mutex);
        if (counter == args->num_of_philosophers)
        {
            args->all_ate = 1;
            break;
        }
    }
}

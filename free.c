/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:59:46 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/04 17:59:48 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	free_mutexes(t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_of_ph)
	{
		pthread_mutex_destroy(&args->forks[i]);
		pthread_mutex_destroy(&args->philosophers[i].ph_act_mutex);
	}
	pthread_mutex_destroy(&args->write_mutex);
	pthread_mutex_destroy(&args->end_mutex);
}

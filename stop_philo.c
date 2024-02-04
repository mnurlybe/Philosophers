/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 20:42:14 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/04 18:08:36 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	is_dead(t_philosopher *philo)
{
	unsigned long	time;

	time = gettimeofday_long();
	if ((time - philo->last_meal) >= philo->args->time_to_die)
		return (TRUE);
	return (FALSE);
}

int	all_full(t_args *args)
{
	int	counter;
	int	i;

	counter = 0;
	i = -1;
	while (++i < args->n_of_ph)
	{
		if (args->philosophers[i].n_eaten >= args->n_meals)
			counter++;
	}
	if (counter == i)
		return (TRUE);
	return (FALSE);
}

void	change_end_status(t_args *args, int status)
{
	pthread_mutex_lock(&args->end_mutex);
	if (status == 0)
		args->end = FALSE;
	else if (status == 1)
		args->end = TRUE;
	pthread_mutex_unlock(&args->end_mutex);
}

void	*stop_checker(void *arg)
{
	t_args	*args;
	int		i;

	args = (t_args *)arg;
	change_end_status(args, FALSE);
	while (args->end == FALSE)
	{
		i = -1;
		while (++i < args->n_of_ph)
		{
			if (args->n_meals != -1 && all_full(args))
			{
				change_end_status(args, TRUE);
				return (NULL);
			}
			if (is_dead(&(args->philosophers[i])))
			{
				change_end_status(args, TRUE);
				write_message_estd(&(args->philosophers[i]), DEAD);
				return (NULL);
			}
		}
		usleep(1000);
	}
	return (NULL);
}

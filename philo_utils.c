/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:01:27 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/04 18:13:28 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	update_last_meal(t_philosopher *philo)
{
	pthread_mutex_unlock(&(philo->ph_act_mutex));
	philo->last_meal = gettimeofday_long();
	pthread_mutex_lock(&(philo->ph_act_mutex));
}

void	*only_one_philo(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
	write_message_forks(philo);
	usleep(philo->args->time_to_die * 1000);
	write_message_estd(philo, DEAD);
	pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
	return (NULL);
}

int	get_end_status(t_args *args)
{
	int	status;

	status = FALSE;
	pthread_mutex_lock(&args->end_mutex);
	if (args->end == TRUE)
		status = TRUE;
	pthread_mutex_unlock(&args->end_mutex);
	return (status);
}

int	action_in_process(t_args *args, unsigned int time_to_act)
{
	unsigned long	local_start_time;

	local_start_time = get_time_ms(args->start_time);
	while ((get_time_ms(args->start_time) - local_start_time) < time_to_act)
	{
		if (get_end_status(args) == TRUE)
			return (FALSE);
		usleep(500);
	}
	return (TRUE);
}

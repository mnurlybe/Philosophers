/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:16:38 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/04 18:11:10 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	sleep_think(t_philosopher *philo)
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

void	put_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
}

int	take_forks(t_philosopher *philo)
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

int	eat(t_philosopher *philo)
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
	if (philo->args->n_meals != -1)
		philo->n_eaten++;
	put_forks(philo);
	return (TRUE);
}

void	*philo_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
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

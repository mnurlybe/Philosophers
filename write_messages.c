/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:04:46 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/04 18:12:37 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	write_message_estd(t_philosopher *philo, t_state state)
{
	pthread_mutex_lock(&philo->args->write_mutex);
	if (state == EATING)
	{
		printf("%ld %d is eating\n", get_time_ms(philo->ph_start_time),
			philo->id + 1);
	}
	else if (state == SLEEPING)
	{
		printf("%ld %d is sleeping\n", get_time_ms(philo->ph_start_time),
			philo->id + 1);
	}
	else if (state == THINKING)
	{
		printf("%ld %d is thinking\n", get_time_ms(philo->ph_start_time),
			philo->id + 1);
	}
	else if (state == DEAD)
	{
		printf("%ld %d died\n", get_time_ms(philo->ph_start_time), philo->id
			+ 1);
	}
	pthread_mutex_unlock(&philo->args->write_mutex);
}

void	write_message_forks(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->args->write_mutex);
	printf("%ld %d has taken a fork\n", get_time_ms(philo->ph_start_time),
		philo->id + 1);
	pthread_mutex_unlock(&philo->args->write_mutex);
}

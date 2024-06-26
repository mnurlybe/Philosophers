/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:00:48 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/04 18:12:06 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/**
 * Arguments:
 * Number_of_philisophers
 * time_to_die
 * time_to_eat
 * time_to_sleep
 * number_of_times_each_philosopher_must_eat (optional)
 */

int	start_program(t_args *args)
{
	int	i;

	args->start_time = gettimeofday_long();
	i = -1;
	while (++i < args->n_of_ph)
	{
		args->philosophers[i].ph_start_time = args->start_time;
		args->philosophers[i].last_meal = args->start_time;
		pthread_create(&args->philosophers[i].th, NULL, &philo_routine,
			&args->philosophers[i]);
	}
	if (args->n_of_ph > 1)
		pthread_create(&(args->stop_th), NULL, &stop_checker, args);
	i = -1;
	while (++i < args->n_of_ph)
		pthread_join(args->philosophers[i].th, NULL);
	if (args->n_of_ph > 1)
		pthread_join(args->stop_th, NULL);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_args	*args;

	if (argc_error_check(argc) || argv_error_check(argc, argv))
		return (1);
	args = init_args(argc, argv);
	if (!args)
		return (1);
	if (args->n_meals != 0)
		start_program(args);
	free_mutexes(args);
	free(args);
	return (0);
}

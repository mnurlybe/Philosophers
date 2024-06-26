/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:10:01 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/04 18:10:07 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0

typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	FORK
}					t_state;

typedef struct s_philosopher
{
	pthread_t		th;
	int				id;
	unsigned int	left_fork;
	unsigned int	right_fork;
	int				n_eaten;
	unsigned long	ph_start_time;
	unsigned long	last_meal;
	struct s_args	*args;
	pthread_mutex_t	ph_act_mutex;
}					t_philosopher;

typedef struct s_args
{
	int				n_of_ph;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				n_meals;
	unsigned int	end;
	unsigned long	start_time;
	pthread_t		stop_th;
	t_philosopher	philosophers[250];
	pthread_mutex_t	forks[250];
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	end_mutex;
}					t_args;

// errors.c
int					argc_error_check(int argc);
int					argv_error_check(int argc, char **argv);

// init_structs.c
t_args				*init_args(int argc, char **argv);

// routine_new.c
void				*philo_routine(void *args);

// stop_philo.c
void				*stop_checker(void *args);
int					is_dead(t_philosopher *philo);

//  free.c
void				free_mutexes(t_args *args);

// write_messages.c
void				write_message_estd(t_philosopher *philo, t_state state);
void				write_message_forks(t_philosopher *philo);

// philo_utils.c
void				update_last_meal(t_philosopher *philo);
int					action_in_process(t_args *args, unsigned int time_to_act);
int					get_end_status(t_args *args);
void				*only_one_philo(t_philosopher *philo);

// utils.c
int					ft_atoi(const char *nptr);
unsigned long		gettimeofday_long(void);
unsigned long		get_time_ms(unsigned long start_time);

// print.c - TESTING purpose --> to be removed before the final submission
void				printf_test(t_args *args);
void				print_philo(t_philosopher *philo);
#endif

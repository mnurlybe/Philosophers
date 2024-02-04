/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:02:58 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/04 18:02:59 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_atoi(const char *nptr)
{
	int	num;
	int	sign;

	sign = 1;
	num = 0;
	while (*nptr && (*nptr == ' ' || *nptr == '\n' || *nptr == '\t'
			|| *nptr == '\v' || *nptr == '\f' || *nptr == '\r'))
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	return (num * sign);
}

unsigned long	gettimeofday_long(void)
{
	struct timeval	tv;
	unsigned long	ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (ms);
}

unsigned long	get_time_ms(unsigned long start_time)
{
	unsigned long	now;

	now = gettimeofday_long();
	return (now - start_time);
}

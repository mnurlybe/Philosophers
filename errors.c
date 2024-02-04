/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnurlybe <mnurlybe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:59:32 by mnurlybe          #+#    #+#             */
/*   Updated: 2024/02/04 18:13:03 by mnurlybe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/**
 * Check input errors
 */
int	argc_error_check(int argc)
{
	if (argc < 5 || argc > 6)
	{
		write(2, "Error: wrong number of arguments\n", 34);
		return (TRUE);
	}
	return (FALSE);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	argv_error_check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_digit(argv[i]) || ft_atoi(argv[i]) < 0)
		{
			write(2, "Error: invalid input\n", 22);
			return (TRUE);
		}
		if (i == 1 && (ft_atoi(argv[i]) <= 0 || ft_atoi(argv[i]) > 250))
		{
			write(2, "Error: wrong number of philosophers\n", 37);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

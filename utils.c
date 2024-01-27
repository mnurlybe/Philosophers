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

unsigned long gettimeofday_long(void)
{
	struct timeval	tv;
	unsigned long	ms;

	gettimeofday(&tv, NULL);
	ms = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (ms);
}

// unsigned long get_time_ms(struct timeval start_time)
// {
// 	unsigned long	beginning;
// 	unsigned long	end;
//     struct timeval now;

//     gettimeofday(&now, NULL);
// 	beginning = (start_time.tv_sec * 1000) + (start_time.tv_usec / 1000);
// 	end = (now.tv_sec * 1000) + (now.tv_usec / 1000);
// 	return (end - beginning);
// }

void    swap_forks(t_args *args)
{
    int i;
    unsigned int tmp;

    i = -1;
    while (++i < args->n_of_ph)
    {
        if (args->philosophers[i].id % 2 == 0)
        {
            tmp = args->philosophers[i].left_fork;
            args->philosophers[i].left_fork = args->philosophers[i].right_fork;
            args->philosophers[i].right_fork = tmp;
        }
    }
}

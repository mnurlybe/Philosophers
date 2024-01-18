#include "includes/philo.h"

int argc_error_check(int argc)
{
    if (argc < 5 || argc > 6)
    {
        write(2, "Error: wrong number of arguments\n", 34);
        return 1;
    }
    return 0;
}

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

/**
 * usage of gettime of the day function
*/

// int main(int argc, char *argv[])
// {
//     struct timeval tv;
//     double milliseconds;
//     gettimeofday(&tv, NULL);
//     printf("Seconds since Jan. 1, 1970: %ld\n", tv.tv_sec);
//     printf("Microseconds: %ld\n", tv.tv_usec);
//     milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
//     printf("Milliseconds: %f\n", milliseconds);
//     return 0;
// }

/**
 * Race condition example
*/

// int mails = 0;
// pthread_mutex_t mutex;

// void *thread_function()
// {
//     pthread_mutex_lock(&mutex);
//     for (int j = 0; j < 1000000000; j++)
//         mails++;
//     pthread_mutex_unlock(&mutex);
// }

// int main(int argc, char *argv[])
// {
//     pthread_t thread[2];
//     pthread_mutex_init(&mutex, NULL);
//     for (int i = 0; i < 2; i++)
//     {
//         if (pthread_create(&thread[i], NULL, &thread_function, NULL) != 0)
//             return 1;
//     }
//     for (int i = 0; i < 2; i++)
//     {
//         if (pthread_join(thread[i], NULL) != 0)
//             return 2;
//     }
//     pthread_mutex_destroy(&mutex);
//     printf("You've got number of %d mails\n", mails);
//     return 0;
// }

/**
 * get a return value from a thread
*/
// void *thread_function()
// {
//     int value = (rand() % 6) + 1;
//     int *result = malloc(sizeof(int));
//     *result = value; 
//     // printf("Random value: %d\n", value);
//     printf("address %p\n", result);
//     return (void*)result;
// }


// int main(int argc, char *argv[])
// {
//     int *res;
//     srand(time(NULL));
//     pthread_t thread;
//     if (pthread_create(&thread, NULL, &thread_function, NULL) != 0)
//         return 1;
//     if (pthread_join(thread, (void**)&res) != 0)
//         return 2;
//     printf("Thread returned: %d\n", *res);
//     printf("Thread returned address %p\n", res);
//     free(res);
//     return 0;
// }


/**
 * How to pass arguments to a thread
*/
// int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

// void *thread_function(void *arg)
// {
//     sleep(1);
//     // int index = *(int*)arg;
//     printf("%d ", *(int*)arg);
//     // free(arg);
// }

// int main(int argc, char *argv[])
// {
//     pthread_t thread[10];
//     // int i;
//     for (int i = 0; i < 10; i++)
//     {
//         // int *i_malloc = malloc(sizeof(int));
//         // *i_malloc = i;
//         if (pthread_create(&thread[i], NULL, &thread_function, &primes[i]) != 0)
//             perror("Failed to create thread");
//     }
//     for (int i = 0; i < 10; i++)
//     {
//         if (pthread_join(thread[i], NULL) != 0)
//             perror("Failed to join thread");
//     }
//     return 0;
// }

/**
 * Practical example for using threads
*/

// int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

// void *thread_function(void *arg)
// {
//     int index = *(int*)arg;
//     int sum = 0;
//     for (int j = 0; j < 5; j++)
//         sum += primes[index + j];
//     printf("local sum: %d\n", sum);
//     *(int*)arg = sum;
//     return arg;
// }

// int main(int argc, char *argv[])
// {
//     pthread_t thread[2];
//     for (int i = 0; i < 2; i++)
//     {
//         int *i_malloc = malloc(sizeof(int));
//         *i_malloc = i * 5;
//         if (pthread_create(&thread[i], NULL, &thread_function, i_malloc) != 0)
//             perror("Failed to create thread");
//     }
//     int global_sum = 0;
//     for (int i = 0; i < 2; i++)
//     {
//         int *result;
//         if (pthread_join(thread[i], (void **) &result) != 0)
//             perror("Failed to join thread");
//         global_sum += *result;
//         free(result);
//     }
//     printf("Sum of primes: %d\n", global_sum);
//     return 0;
// }   
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

/**
 * create a small simluation of the philo problem that would demonstrate how to use mutexes on a fork state, to make sure no two philos can have the same fork at the same time
*/
// typedef struct s_philo
// {
//     int id;
//     pthread_t philo_thread;
//     pthread_mutex_t *left_fork;
//     pthread_mutex_t *right_fork;
//     int is_eating;
//     int is_sleeping;
//     void *next;
// } t_philo;

// void    print_philo_info(t_philo *philo)
// {
// for (int i = 0; i < 5; i++)
//     {
//         printf("philo id: %d\n", philo[i].id + 1);
//         printf("philo left fork: %p\n", philo[i].left_fork);
//         printf("philo right fork: %p\n", philo[i].right_fork);
//     }
// }

pthread_mutex_t forks[1];

void    *philo(void *arg)
{
    sleep(1);
    int id = *((int *)arg);
    int left_fork = id;
    int right_fork = (id + 1) % 5;
    printf("philo id: %d, left_fork: %d, right_fork: %d\n", id, left_fork, right_fork);

    // synchronization 1: even start from the left fork, and odd start from the right fork
    // if (id % 2 == 0) {
    //     pthread_mutex_lock(&forks[left_fork]);
    //     pthread_mutex_lock(&forks[right_fork]);
    // } else {
    //     pthread_mutex_lock(&forks[right_fork]);
    //     pthread_mutex_lock(&forks[left_fork]);
    // }

    // synchronization 2: all philos start from the right fork, but the last one start from the left fork
    // if (id == 4)
    // {
    //     pthread_mutex_lock(&forks[left_fork]);
    //     pthread_mutex_lock(&forks[right_fork]);
    // }
    // else
    // {
    //     pthread_mutex_lock(&forks[right_fork]);
    //     pthread_mutex_lock(&forks[left_fork]);
    // }

    // synchronization 3: first philo takes both forks, all philos takes the right fork first if available, then wait for the LF to be available
    // if (id == 0)
    // {
    //     pthread_mutex_lock(&forks[left_fork]);
    //     printf("Philosopher %d has taken the left fork %d\n", id + 1, left_fork + 1);  
    //     pthread_mutex_lock(&forks[right_fork]);
    //     printf("Philosopher %d has taken the right fork %d\n", id + 1, right_fork + 1); 
    // }
    // else
    // {
    //     pthread_mutex_lock(&forks[right_fork]);
    //     printf("Philosopher %d has taken the right fork %d\n", id + 1, right_fork + 1);
    //     pthread_mutex_lock(&forks[left_fork]);
    //     printf("Philosopher %d has taken the left fork %d\n", id + 1, left_fork + 1);  
    // }

    // printf("Philosopher %d is eating\n", id);
   
    // // Simulate eating
    // usleep(rand() % 1000000);


    // pthread_mutex_unlock(&forks[left_fork]);
    // pthread_mutex_unlock(&forks[right_fork]);

    // printf("Philosopher %d is done eating\n", id);
    return NULL;
}

int main(void)
{
    // t_philo philo[5];
    int num_of_ph = 5;
    pthread_mutex_t write_message;
    pthread_t philo_thread[num_of_ph];

    // initialize mutexes for each fork
    for (int i = 0; i < num_of_ph; i++)
        pthread_mutex_init(&forks[i], NULL);
    pthread_mutex_init(&write_message, NULL);

    // create threads for each philosopher
    for (int i = 0; i < num_of_ph; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&philo_thread[i], NULL, &philo, id);
    }
    
    // wait for all philosopher threads to finish
    for (int i = 0; i < num_of_ph; i++)
        pthread_join(philo_thread[i], NULL);

    // destroy mutexes for each fork
    for (int i = 0; i < num_of_ph; i++)
        pthread_mutex_destroy(&forks[i]);
    pthread_mutex_destroy(&write_message);

    // assign values to fork state: 0 not taken, 1 taken
    // for (int i = 0; i < 5; i++)
    //     fork[i] = 0;

    // for (int i = 0; i < 5; i++)
    // {
    //     philo[i].id = i;
    //     pthread_mutex_init(&fork[i], NULL);
    //     philo[i].left_fork = &fork[i];
    //     philo[i].right_fork = &fork[(i + 1) % 5];
    //     philo[i].is_eating = 0;
    //     philo[i].is_sleeping = 0;
    // }
    // pthread_mutex_init(&write_message, NULL);
    // print_philo_info(philo);
    return 0;
}
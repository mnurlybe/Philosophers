This is the Philo_42 project plan:

1. small_philo_simulation file:  in this file I have created a small simulation just with the eating and stop eating conditions. This was to understand how to lock the fork with the mutex in order to prevent philosophers taking the same fork at the same time. 
2. There were 3 types of synchronizations tested: I will choose the synchronization #1. 
Synchronization #1 general condition: philosopher #1 takes the left fork first then the right fork, when the rest philosophers thakes the right fork first, then the left fork.
3. Here is the plan: 
    1. Print the milliseconds count starting from the beginning of the simulation. The first action will print 0 milliseconds. 
    2. Add this to the write messages:
        timestamp_in_ms X has taken a fork;
        timestamp_in_ms X is eating;
        timestamp_in_ms X is sleeping;
        timestamp_in_ms X is thinking;
        timestamp_in_ms X died;
    X - is the philosipher number starting from 1.
    timestamp_in_ms - is the current timestamp in milliseconds.
    3. Understand how the write message should not be mixed up with another message -> does it also need to be protected with mutex? probably yes.
    4. routine() function: will have all the cycle of eating, sleeping and thinking in a while loop; The loop breaks is philosopher died or all philosophers ate certain amount of time. 
    4. Time for eating and sleeping is given in the beginning of the program, the thinking time is not defined. Therefore, philosopher stops thinking and starts eating whenever he has taken both forks. Understand how to be in a loop of eating, sleeping and thinking. And be able to stop the simulation only when the philosopher dies or when the optinal argument is reached.
    5. I will create an additional thread check_death_th that will check if the philosopher has died. Probably there will be a flag is_dead assigned to each philosopher node. thread Check_death_th will be constantly checking if the flag is 1 or not. If the flag is 1, it print the message that the philosopher id has died and stop the simulation. Understand how it will print the message no more than 10ms after actual death of the philosopher. It can be calculated: Actual death = time_to_die - last_ate; Difference: timestamp_in_ms X died- Actual death. 
    In addition to point 5, there will be another flag for all the philosophers that will tell us if they need to stop the cycle as someone has died or everyone is full. 
    6. Handling optional argument number_of_times_each_philosopher_must_eat: there will be a counter int variable created in each philosopher node that will increment everytime the number of the philosophers has eated. I will create an additional thread for check_num_of_times_eaten, that will be checking if all the counter variables for each philosophers reached the number passed as an argument then the simulation stops.
4. time_to_die argument has specifics. There are certain conditions for odd and even number of philosophers. There is a minimum value for time_to_die needs to be calculated based on the time_to_sleep and time_to_eat values. Otherwise, if it is lower than the minimu requirement some philosopher will die right away. But this could be a way to test the printing time of the timestamp_in_ms X died message.
5. error handling for each thread and mutex functions.
6. valgrind --tool=helgrind --> checks for data races; 



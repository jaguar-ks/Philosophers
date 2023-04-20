# **Philosophers**

1. [*The dining philosopher problem.*](#the-dining-philosopher-problem)
1. [*The assignment.*](#the-assignment)
1. [*Sure you have questions.*](#sure-you-have-questions)
1. [*The **Thread's** functions to use.*](#the-threads-functions-to-use)
1. [*The algo.*](#the-algo)
    1. [The data structures I used.](#the-data-structures-i-used)
    1. [Initialising the linked list.](#initialising-the-linked-list)
    1. [Start the sumilation.](#start-the-sumilation)

## **The dining philosopher problem.**

The Dining Philosophers problem is a classic OS problem that's usually stated in very non-OS terms: There are N philosophers sitting around a circular table eating spaghetti and discussing philosophy. The problem is that each philosopher needs 2 forks to eat, and there are only N forks, one between every 2 philosophers.

[ ![philo](./philo_dinning.png)](https://www.javatpoint.com/os-dining-philosophers-problem)

---

## **The assignment.**

You have to write a program that takes the following arguments:

- **the number of philosophers**: The number of philosophers and also the number of forks.
- **time to die** (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- **time to eat** (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- **time to sleep** (in milliseconds): The time a philosopher will spend sleeping.
- **number of times each philosopher must_eat** (optional argument): If all
philosophers have eaten at least **number_of_times_each_philosopher_must_eat**
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

Each philosopher has a number ranging from 1 to **number_of_philosophers**. Philosopher number 1 sits next to philosopher number **number_of_philosophers**.
Any other philosopher number N sits between philosopher number N - 1 and philosopher number N + 1.

About the logs of your program, any state change of a philosopher must be formatted as follows:

- *The_philosopher_current_timestamp*   *The_philosopher_id*   *The_action_the_philosopher_is_doing* 

Keep in mind displaying state messages should not be mixed up with other messages. Also, the message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.

**The specific rules for the project are:**

- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the fork's state
with a mutex for each of them.

![data_race](./data_race.png)


---

## **Sure you have questions.**

- [What is a **thread**?](https://www.geeksforgeeks.org/thread-in-operating-system/)
- [What is a **mutex**?](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/)
- [what is **data race**?](https://www.mathworks.com/products/polyspace/static-analysis-notes/what-data-races-how-avoid-during-software-development.html#:~:text=Data%20races%20are%20a%20common,to%20undefined%20or%20unpredictable%20behavior.)

---

## **The Thread's functions to use:**

| Function | Description |
| :-----: | :-------- |
| pthread_create | The pthread_create() function is used to create a new thread, with attributes specified by attr, within a process.  If attr is NULL, the default attributes are used. |
| pthread_detach | The pthread_detach() function is used to indicate to the implementation that storage for the thread can be reclaimed when the thread terminates. If the thread has not terminated, pthread_detach() will not cause it to terminate. |
| pthread_join | The pthread_join() function suspends execution of the calling thread until the target thread terminates unless the target thread has already terminated. |
| pthread_mutex_init | The pthread_mutex_init() function creates a new mutex, with attributes specified with attr.  If attr is NULL the default attributes are used. |
| pthread_mutex_destroy | The pthread_mutex_destroy() function frees the resources allocated for the mutex.|
| pthread_mutex_lock | The pthread_mutex_lock() function locks mutex.  If the mutex is already locked, the calling thread will block until the mutex becomes available. |
| pthread_mutex_unlock | If the current thread holds the lock on the mutex, then the pthread_mutex_unlock() function unlocks the mutex.|

> You can find more about each function on its MAN page.
***

## **The algo.**

### *The data structures I used:*

> I use 3 structures in my code:

- **t_nd** a structure that holds the needed data to start the simulation and making sending all the necessary information to the routine :
``` c
typedef struct f_nd
{
	int				*wait; // The integer pointer that used to send to pthread_join() function to store the routine return value
	struct f_inf	inf; // The data entered by the user
	struct f_philo	*phls; // The linked list of the philosophers
}	t_nd;
```
---
- **t_inf** structure to store the data given by the user and other helpful variables :
``` c
typedef struct f_inf
{
	int				nb_ph; // Number of philosophers sitting around the table
	int				t_d; // Time to die if they didn't eat
	int				t_e; // Time each philosopher should spend eating
	int				t_s; // Time each philosopher should spend sleeping
	int				*h_m_e; // The optional argument of how many times each philosopher should eat
	int				lp; // This variable indicates how many times the simulation had looped
	pthread_mutex_t	prnt; // This mutex is used to protect the thread writing the state of the philosopher
	pthread_t		wrtr; // This is the thread used to write the state of the philosopher
	pthread_mutex_t	wt; // This mutex is used to wait for the philosopher who is writing what he is doing
}	t_inf;
```
---
- **t_philo** is a linked list that holds the necessary information about each philosopher in the simulation :
``` c
typedef struct f_philo
{
	pthread_t			thrd_id; // The thread ID
	int					philo_id; // The philosopher ID or his place around the table
	unsigned long long	ct; // The philosopher current time
	int					t_l; // The time left for the philosopher to live
	int					st; // The state of the philosopher or what is he doing at the current time
	pthread_mutex_t		f; // The mutex that represents the fork
	struct f_philo		*nxt; // The pointer to the next philosopher
}	t_philo;
```
---
> **Now before starting the simulation we need to initialise our linked list and fill it with the needed information.**

---

### *Initialising the linked list:*
> The linked list that we are going to work with is a circular linked list so which means that the next of the last node will be the first node in the linked list but most importantly that we going to focus on 2 variables of the node :
```c
unsigned long long	ct; // The philosopher current time
int					t_l; // The time left for the philosopher to live
```
To initialise **the current time** and **the time left to live** first we need to know how many philosophers are in the simulation we have 2 possibilities:
- **The number of philosophers is even**:
> *In this case **the current time** of the philosophers with **the odd numbers** as an ID will start from the **0**, and **the time left to live** will be **the time to die** if they didn't eat. But for the philosophers with **the even number** as an ID **their current time** will start from **(0 + time_to_eat)** because they will have to wait for the philosophers with the odd number in the id to finish eating and put the forks back on the table, and for **the time left to live** will be **(time_to_die** - **time_to_eat)**.*
- **The number of philosophers is odd**:
> *, In this case, we do the same as the previous case the only difference is the last node that represents the last philosopher he had to wait 2 times for the philosopher what the odd before him and the even numbers to finish eating because in the first round, he needs his fork and the fork of the philosopher with the ID=1 and in the next time the philosopher before him with the even ID number is gonna use the last one fork that's why the last philosopher **current time** is going to start from **(time_to_eat * 2)** and his **time left to live** will be **(time_to_die - (time_to_eat * 2))*** 
### **Start the simulation**
After we setup our linked list now we are ready to create the threads and lunch the simulation.
> *In an infinite loop we lunche the threads giving them the routine they should do but after lunching each one we use the **usleep()** function to wait a litlle bit before lunching the other one to send the philosophers with the odd ID number sepretly then the  philosophers with the even ID nuber as you can see in the exampele below.*
```c
pthread_create(&thrd_id, NULL, &routine, &arg);
usleep(100);
```
> *After lunching the threads now let us move to the routine which represent the philosphers life cicle.*
1. First the philosopher try to pick up his own fork than try to borows the fork of one sitting next to him. That means locking the mutexes that represents the forks as the exemple below.
```c
pthread_mutex_lock(&phls->f);
pthread_mutex_lock(&phls->nxt->f);
```
2. If the philosopher succed picking up the forks than we print that the philosopher picked the fork as follows:
```
timestamp_in_ms X has taken a fork
```
3. After pickin up the forks we should check if the philosopher should die or not by checking if the time he had left to live is enough for him to eat if it is enough we print a message that the philosopher is eating as followes:
```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
```
than add **the_time_to_eat** to **the_current_time** and reset **the_time_left_to_die** again to **the_time_to_die** else we add **the_time_left_to_die** to **the_current_time** and set the philosopher state to died and quite the routine.

4. If the philosopher succed to eat that mean he should sleep so we releass the forks and print the philosopher is sleeping as follows:
```
timestamp_in_ms X is sleeping
```
than we check for the death again the same way we checked in th eating situation  by checking if the time he had left to live is enough for him to sleep if the philosopher should not die we add **the_time_to_sleep** to **the_current_time** and subtract it from **the_time_left_to_die** else we add **the_time_left_to_die** to **the_current_time** and set the philosopher state to died and quite the routine.

5. If the philosopher succed to sleep than we print the philosopher is thinking as follows:
```
timestamp_in_ms X is thinking
```
and then quit the life sicle with out sending anything.

6. After sending all the threads to execute the routine function we wait for them using **pthread_join()** function to see what value they return with if at least one of them return the state of a philosopher is died we print the followed message and quite the programme:
```
timestamp_in_ms X died
```

else we repeate the same thing again.

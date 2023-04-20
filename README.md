# **Philosophers**

1. [*The dining philosopher problem.*](#the-dining-philosopher-problem)
1. [*The assignment.*](#the-assignment)
1. [*Sure you have questions.*](#sure-you-have-questions)
1. [*The **Thread's** functions to use.*](#the-threads-functions-to-use)
1. [*The algo.*](#the-algo)
    1. [The data sturcturs i used](#the-data-structurs-i-used)

## **The dining philosopher problem.**

The Dining Philosophers problem is a classic OS problem that's usuallu stated in very non-OS terms: There are N philosphers sitting around a circular table eating spaghetti and discussing philosphy. The problem is that each philosopher needs 2 forks to eat, and there are only N forks, one between each 2 philosophers.

[ ![philo](./philo_dinning.png)](https://www.javatpoint.com/os-dining-philosophers-problem)

---

## **The assignment.**

You have to write a program that take the following arguments:

- **number of philosophers**: The number of philosophers and also the number of forks.
- **time to die** (in milliseconds) : If a philosopher didn’t start eating time_to_die
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

Keep in mind displaing state messages should not be mixed up with another messages. Also the message announcing a philosopher died should be displayed no more than 10 ms
after the actual death of the philosopher.

**The specific rules for the project are:**

- Each philosopher should be a thread.
- There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
- To prevent philosophers from duplicating forks, you should protect the forks state
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
| pthread_detach | The pthread_detach() function is used to indicate to the implementation that storage for the thread thread can be reclaimed when the thread terminates. If thread has not terminated, pthread_detach() will not cause it to terminate. |
| pthread_join | The pthread_join() function suspends execution of the calling thread until the target thread terminates unless the target thread has already terminated. |
| pthread_mutex_init | The pthread_mutex_init() function creates a new mutex, with attributes specified with attr.  If attr is NULL the default attributes are used. |
| pthread_mutex_destroy | The pthread_mutex_destroy() function frees the resources allocated for mutex.|
| pthread_mutex_lock | The pthread_mutex_lock() function locks mutex.  If the mutex is already locked, the calling thread will block until the mutex becomes available. |
| pthread_mutex_unlock | If the current thread holds the lock on mutex, then the pthread_mutex_unlock() function unlocks mutex.|

> You can find more about each function on it's MAN page.
***

## The algo.

### The data structurs i used:

> I use 3 structurs in my code:

- **t_nd** a structur that hold the needed data to statrt the simulation and making sending all the necessary information to the rotine :
``` c
typedef struct f_nd
{
	int				*wait; // The intiger pointer that used to send to pthread_join() function to store the rotine return value
	struct f_inf	inf; // The data intred by the user
	struct f_philo	*phls; // The linked list of the philosophers
}	t_nd;
```
- **t_inf** structur to store the data given by the user and other helpfull variables :
``` c
typedef struct f_inf
{
	int				nb_ph; // Number of philosophers setting around the table
	int				t_d; // Time to die if they didn't eat
	int				t_e; // Time each philosopher should spent eating
	int				t_s; // Time each philosopher should spent sleeping
	int				*h_m_e; // The optional argiment of how many time should each philosopher eat
	int				lp; // This variable its indicate how many time the simulation had looped
	pthread_mutex_t	prnt; // This mutex is used to protect the the thread writing the state of the philosopher
	pthread_t		wrtr; // This is the thread used to write the state of the philosopher
	pthread_mutex_t	wt; // This mutex is used to wait for the philosopher who is writing what he is doing
}	t_inf;
```
- **t_philo** is a linked list that holds the necessary information about each philosopher in the sumilation :
``` c
typedef struct f_philo
{
	pthread_t			thrd_id; // The thread ID
	int					philo_id; // The philosopher ID or his place around the table
	unsigned long long	ct; // The philosopher current time
	int					t_l; // The time left for the philosopher to live
	int					st; // The state of the philosopher or what is he doing on the current time
	pthread_mutex_t		f; // The mutex that represent the fork
	struct f_philo		*nxt; // The pointer to the next philosopher
}	t_philo;
```


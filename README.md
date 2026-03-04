*This project has been created as part of the 42 curriculum by anbelose.*  

## Description

Philosophers is a multithreads project that simulates the classic [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem), originally formulated by Edsger Dijkstra in 1965. The goal is to learn the basics of threading and synchronization by managing multiple philosophers sitting around a table, each alternating between eating, sleeping, and thinking, while avoiding deadlocks and data races.  

Each philosopher is a thread, and the forks between them are protected by mutexes. A philosopher must pick up two forks to eat, then release them to sleep and think. If a philosopher doesn't eat within a given time window, they die and the simulation ends. 

## Instructions

```
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```

```
valgrind --tool=helgrind ./philo 4 800 200 200
```

```
cc -Wall -Wextra -Werror -fsanitize=thread -g *.c -o philo
./philo 4 800 200 200
```

## Implementation

1/ Each philosopher runs in its own **pthread**. 

2/ Mutexes protect shared resources: forks, death flag, print output, meal counters.  

3/ A custom **ft_usleep** with periodic death-checks ensures timely simulation termination.  

4/ An odd/even fork-picking strategy prevents deadlock by ensuring philosophers don't all reach for the same fork first.  

### Algorithm

1/ Even nb of philosophers : 2 groups (even IDs wait 30ms)  

2/ Odd nb of philosophers : 3 groups via id % 3 (0/30/60ms delays) + extra eat/2 thinking pause in the loop to spread fork access.

### Structures

```typedef struct s_philo
{
	int				id;			// philosopher number (1 to philo_nb)
	int				had_meals;	// number of meals eaten so far
	pthread_t		th;			// thread associated with this philosopher
	u_int64_t		start_meal;	// timestamp of the last meal start
	struct s_data	*data;		// pointer to shared simulation data
	struct s_philo	*next;		// next philosopher in linked list
}	t_philo;
```
```
typedef struct s_data
{
	int				philo_nb;		// total number of philosophers
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				meal_nb;		// 0 if unused
	int				nb_full;		// count of philosophers that reached meal_nb
	u_int64_t		start_simul;	// simulation start timestamp (ms)
	t_philo			*philos;		// linked list of all philosophers
	bool			flag_death;		// true if a philosopher has died
	pthread_mutex_t	*fork;			// array of mutexes, one per fork
	pthread_mutex_t	print;			// mutex protecting stdout output
	pthread_mutex_t	full;			// mutex protecting nb_full counter
	pthread_mutex_t	dead;			// mutex protecting flag_death
	char			**logs;			// array of log message strings
}	t_data;
```

## Several tests

### A philosopher dies

`1 800 200 200`  
`2 60 60 60`  
`4 310 200 100`  
`4 800 350 450`  
`5 300 100 60`  
`105 200 60 60`  

### No one dies

`2 410 200 200`  
`4 800 200 200`  
`5 310 100 70`  
`5 610 200 200`  
`200 800 200 200`  // починить  
`199 190 60 60`  // починить  

## Resources

### Visualizer

The website https://rom98759.github.io/Philosophers-visualizer/ was the most useful resource while working on the project, especially when developing the delay algorithm.

### CodeVault

Youtube channel [CodeVault](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) (especially the Unix theads in C playlist) helped me understand the theory of threads and mutexes thanks to the exercices structured from simple to complex.  

### AI use
The use of AI was limited to helping identify certain bugs in the code, as well as assisting with understanding the theory while reviewing CodeVault videos.  
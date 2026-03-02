*This project has been created as part of the 42 curriculum by anbelose.*  

## Description

Philosophers is a multithreads project that simulates the classic [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem), originally formulated by Edsger Dijkstra in 1965. The goal is to learn the basics of threading and synchronization by managing multiple philosophers sitting around a table, each alternating between eating, sleeping, and thinking, while avoiding deadlocks and data races.  

Each philosopher is a thread, and the forks between them are protected by mutexes. A philosopher must pick up two forks to eat, then release them to sleep and think. If a philosopher doesn't eat within a given time window, they die and the simulation ends. 

## Instructions

```
make
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```

## Implementation

1/ Each philosopher runs in its own **pthread**. 

2/ Mutexes protect shared resources: forks, death flag, print output, and meal counters.  

3/ An odd/even fork-picking strategy prevents deadlock by ensuring philosophers don't all reach for the same fork first.  

4/ A staggered start **create_gap** spreads out initial fork contention, especially for odd numbers of philosophers.  

5/ A custom **ft_usleep** with periodic death-checks ensures timely simulation termination.  

## How to determine if a philosopher will die or not?


## Several tests

### A philosopher dies

`1 800 200 200`
`2 60 60 60`
`4 310 200 100` 
`4 800 350 450`
`5 300 100 60`
`105 200 60 60`

### 2. No one dies

`2 410 200 200`
`4 800 200 200`
`5 310 100 70`
`5 610 200 200`
`200 800 200 200`
`199 190 60 60`

## Resources

### Visualizer

The website https://rom98759.github.io/Philosophers-visualizer/ was the most useful resource while working on the project, especially when developing the delay algorithm.

### CodeVault

Youtube channel [CodeVault](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) (especially the Unix theads in C playlist) helped me understand the theory of threads and mutexes thanks to the exercices structured from simple to complex.  

### AI use
The use of AI was limited to helping identify certain bugs in the code, as well as assisting with understanding the theory while reviewing CodeVault videos.  
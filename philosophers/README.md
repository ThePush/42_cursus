<div align="center">
  <center><h1>philosophers 🍽</h1></center>
  <img src="https://user-images.githubusercontent.com/91064070/166064033-47275d8b-8eca-42b1-a9bd-66caa898f911.png">

## Goal of the project

A classic computer science problem: [Dijkstra's dining philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem).
</div>

## Skills involved
* Concurrency
* Threads
* Mutexes
* Semaphores
* Data races and deadlocks


## How it works

The program should take the following arguments:
number_of_philosophers time_to_die time_to_eat time_to_sleep
[number_of_times_each_philosopher_must_eat]

* number_of_philosophers: The number of philosophers and also the number
of forks.

* time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.

* time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.

* time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.

* number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

![alt tag](https://user-images.githubusercontent.com/91064070/165654038-219bb003-01aa-4bd5-a969-22c21db4f5fc.png)

Two methods: mutexes ( /philo/ ) or semaphores ( /philo_bonus/ ).

* One thread for each philosopher.

* One mutex/semaphore for each fork (means one per philosopher);

* One mutex/semaphore to protect the philosopher last meal time (accessed when updating said time or when checking if the philosopher is dead, given the amount of time it takes for them to die after a meal);

* One mutex/semaphore in the function that writes the informations on stdout.

## Usage

```shell
$> cd philosophers/philo/ && make
```
```shell
$> ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

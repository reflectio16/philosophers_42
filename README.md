# Philosophers

A multithreaded solution to the classic Dining Philosophers problem, implemented in C as part of the 42 school core curriculum.

## The Problem

Five philosophers sit at a round table with a bowl of spaghetti. Between each pair of philosophers is a single fork. A philosopher needs two forks to eat. The challenge is to design a protocol that allows philosophers to eat without deadlocking or starving.

## Overview

This project explores concurrent programming concepts including threads, mutexes, and race condition prevention. Each philosopher is represented as a thread, and each fork as a mutex-protected resource.

## Features

- **Thread Management**: Each philosopher runs as a separate thread
- **Mutex Protection**: Forks are protected by mutexes to prevent data races
- **Deadlock Prevention**: Fork ordering strategy prevents circular wait
- **Death Detection**: Monitor thread checks for philosopher starvation
- **Precise Timing**: Microsecond-level timing for accurate simulation
- **Clean Termination**: Proper resource cleanup on simulation end

## Installation

### Prerequisites

- GCC compiler
- Make
- pthread library (standard on Unix systems)

### Build

```bash
git clone https://github.com/yourusername/philosophers.git
cd philosophers
make
```

## Usage

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

| Argument | Description |
|----------|-------------|
| `number_of_philosophers` | Number of philosophers and forks |
| `time_to_die` | Time (ms) a philosopher can go without eating before dying |
| `time_to_eat` | Time (ms) it takes to eat |
| `time_to_sleep` | Time (ms) a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` | Optional: simulation stops when all philosophers have eaten this many times |

### Examples

```bash
# 5 philosophers, 800ms to die, 200ms to eat, 200ms to sleep
./philo 5 800 200 200

# Same as above, but stop after each philosopher eats 7 times
./philo 5 800 200 200 7

# Edge case: single philosopher (will die - needs 2 forks)
./philo 1 800 200 200

# Stress test: many philosophers
./philo 200 800 200 200
```

### Output Format

```
timestamp_in_ms philosopher_id action
```

Actions:
- `has taken a fork`
- `is eating`
- `is sleeping`
- `is thinking`
- `died`

Example output:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 3 has taken a fork
...
```

## Project Structure

```
philosophers/
└── philo/
    ├── src/
    │   ├── main.c           # Entry point
    │   ├── parsing.c        # Argument parsing
    │   ├── init_data.c      # Initialize table and philosophers
    │   ├── threads.c        # Thread creation and management
    │   ├── simulation.c     # Main simulation logic
    │   ├── actions.c        # Philosopher actions (eat, sleep, think)
    │   ├── monitor.c        # Death detection thread
    │   ├── mutex.c          # Mutex operations
    │   ├── mutex_set_get.c  # Thread-safe getters/setters
    │   ├── time_utils.c     # Timing functions
    │   ├── write.c          # Status output
    │   ├── cleanup.c        # Resource cleanup
    │   └── utils.c          # Helper functions
    ├── include/
    │   └── philo.h
    └── Makefile
```

## Technical Implementation

### Deadlock Prevention

Philosophers are assigned fork pickup order based on their ID:
- Even-numbered philosophers pick up right fork first
- Odd-numbered philosophers pick up left fork first

This breaks the circular wait condition and prevents deadlock.

### Race Condition Prevention

All shared data is protected by mutexes:
- Each fork has its own mutex
- Table state (simulation end flag) protected by table mutex
- Philosopher state (last meal time, meals eaten) protected by individual mutexes

### Precise Timing

Custom `usleep` implementation with busy-waiting for the final milliseconds ensures accurate timing, critical for edge-case tests.

## Testing

Tested with various configurations:
- ✅ No deaths: `./philo 5 800 200 200` (philosophers should survive indefinitely)
- ✅ Death expected: `./philo 4 310 200 100` (should die)
- ✅ Single philosopher: `./philo 1 800 200 200` (should die - only one fork)
- ✅ Meal count: `./philo 5 800 200 200 7` (should stop after all eat 7 times)
- ✅ Valgrind: No memory leaks
- ✅ Helgrind: No data races

## Resources

- [suspectedoceano's Philosophers Walkthrough](https://www.youtube.com/watch?v=zOpzGHwJ3MU) - Video tutorial that helped structure this project ([YouTube Channel](https://www.youtube.com/@onaecO) | [GitHub](https://github.com/suspectedoceano))
- [Dining Philosophers - Gitbook42](https://42-cursus.gitbook.io/guide/3-rank-03/philosophers)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)

## Author

meelma 42 Student

## License

This project is part of the 42 school curriculum.

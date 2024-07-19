# Philosophers

## Overview

This project is an implementation of the classic dining philosophers problem using threads and mutexes in C. The goal is to simulate philosophers sitting at a table, eating, thinking, and sleeping, without causing a deadlock or starving any philosopher.

## Table of Contents

- [Overview](#overview)
- [Global Rules](#global-rules)
- [How to Run](#how-to-run)
- [Contribution](#Contribution)

## Global Rules

- **Global variables are forbidden!**
- The program takes the following arguments:
  1. `number_of_philosophers`: Number of philosophers (and forks)
  2. `time_to_die`: Time in milliseconds a philosopher can go without eating before dying
  3. `time_to_eat`: Time in milliseconds a philosopher spends eating
  4. `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
  5. `number_of_times_each_philosopher_must_eat` (optional): If specified, the simulation stops when all philosophers have eaten at least this many times. If not, the simulation stops when a philosopher dies.
- Each philosopher has a unique number ranging from 1 to `number_of_philosophers`.
- Philosophers don't speak to each other and don't know if another philosophe

## How to Run

1. Clone the repository:
   ```sh
   git clone https://github.com/hussienK/Philosophers.git
   cd Philosophers/philo
2. Compile the program:
   ```sh
   make
3. Run the program with the required arguments:
   ```sh
   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

## Contribution

Contributions are welcome! If you have suggestions or improvements, feel free to open an issue or submit a pull request.

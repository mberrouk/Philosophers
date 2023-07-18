# Philosophers Project

This project is a part of the 42 & 1337 cursus and aims to simulate the dining philosophers problem using threads and mutexes. The dining philosophers problem is a classic synchronization problem in computer science, which illustrates the challenges of resource allocation and deadlock avoidance in a concurrent system.

## Table of Contents

- [Introduction](#introduction)
- [Problem Statement](#problem-statement)
- [Implementation](#implementation)
- [Usage](#usage)
- [Contributing](#contributing)

## Introduction

The dining philosophers problem is a thought experiment that involves a group of philosophers sitting around a circular table with a bowl of rice and a chopstick between each pair of adjacent philosophers. Each philosopher alternates between thinking and eating. However, to eat, a philosopher must have both chopsticks adjacent to them. The challenge is to design a solution that prevents deadlock and starvation, ensuring that each philosopher can eat without being blocked by their neighbors.

## Problem Statement

The goal of this project is to implement a solution to the dining philosophers problem using threads and mutexes. The program should create a specified number of philosophers, each represented by a separate thread. The philosophers should alternate between thinking and eating, and they should use mutexes to ensure that they can acquire both chopsticks before eating.

The program should also handle the case where a philosopher dies of starvation. If a philosopher spends too much time thinking without being able to eat, they should be considered dead, and the program should terminate.

## Implementation

The project should be implemented in the C programming language, following the guidelines and coding standards of the 42 & 1337 cursus. The program should use threads and mutexes from the pthread library to simulate the philosophers and their chopsticks. The implementation should ensure that the philosophers can acquire both chopsticks without causing deadlock or starvation.

## Usage

To compile the program, navigate to the project directory and run the following command:

```
make
```

This will generate an executable named `philo`.

To run the program, use the following command:

```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: The number of philosophers sitting at the table.
- `time_to_die`: The time in milliseconds after which a philosopher is considered dead if they haven't started eating.
- `time_to_eat`: The time in milliseconds it takes for a philosopher to eat.
- `time_to_sleep`: The time in milliseconds a philosopher spends sleeping after eating.
- `number_of_times_each_philosopher_must_eat`: The number of times each philosopher must eat before the program can terminate. If set to -1, the program should not terminate until a philosopher dies.

## Contributing

Contributions to the Philosophers Project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.


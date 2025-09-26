# Project 1 - Creating Your Own Shell

- In this project, we implemented a simplified command-line shell names myshell. The shell demonstrates core concepts of process creation, destruction, synchronization, and input/output redirection in UNIX-like systems.

The shell is designed in two parts:
- Parsing: reads user commands, tokenizes input, and stores the results in a Param object.
- Execution: creates child processes using fork() and executes commands with exec(), supporting I/O redirection and background execution.

## Files
- myshell.cpp: main program, handles shell loop and execution.
- parse.cpp: implements command parsing logic.
- parse.hpp: exposes parsing functionality.
- param.cpp: defines and implements the Param class methods.
- param.hpp: defines the Param class structure.
- Makefile: builds the project with -Wall -g, includes a clean rule.


## To run and test:
-  1st: make clean
-  2nd: make
-  3rd: ./myshell
-  4th: ./slow &  (process will allow you to test if we handled the execution of background processes )
-  5th: you may need to type exit to stop the slow program
-  6th: ./testme <totalNumInstance> <index> <values>   (test program that prints out the instance, the total number of instances, and the range of values each instance processes.)
-  7th: ./prime <totalNumInstances> <index> <upperValue>   (generates all prime numbers that occur within a range of numbers)

## Authors:
Chase Dittbenner and Deesha Rajiv

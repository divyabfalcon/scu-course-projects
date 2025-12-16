# Lab 2 – Programming in C and System Calls

This lab focuses on developing C programs in a Linux environment to explore
process creation, process control, and basic multithreading using system calls
and POSIX threads.

## Concepts Covered
- Process creation using `fork()`
- Parent and child process behavior
- Command-line arguments
- Creating multiple processes with different execution delays
- Using `wait()` to manage process termination
- Replacing process images with `exec()`
- Implementing threads as lightweight processes using `pthread`

## File Overview
- divyabengali_step1_fork_basic.c  
  Demonstrates basic parent and child process creation using `fork()`.

- divyabengali_step3_user_delay.c  
  Extends Step 1 by allowing the execution delay to be specified via a
  command-line argument.

- divyabengali_step5_four_processes.c  
  Creates four processes, each running with a different delay.

- divyabengali_step6_five_processes.c  
  Extends the program to create five processes with distinct delays.

- divyabengali_step7_exec_ls.c  
  Uses `exec()` so the child process runs the `ls` command while the parent
  waits for completion.

- divyabengali_step8_threads.c  
  Reimplements process-based logic using POSIX threads instead of processes.

## Notes
This lab was completed using instructor-provided instructions and example
code discussed in lecture. The uploaded source files reflect my own
implementations and modifications. Assignment documents and provided
automation scripts are proprietary and therefore not included.


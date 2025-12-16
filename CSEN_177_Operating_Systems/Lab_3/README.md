# Lab 3 – Inter-Process Communication and Pthreads

This lab explores inter-process communication (IPC) mechanisms and multithreading
using C and POSIX APIs on Linux.

## Concepts Covered
- Pipes for process-to-process communication
- fork(), exec(), and dup2() for process control
- Producer–consumer synchronization using pipes
- Shared memory IPC using System V shared memory
- pthread creation, synchronization, and debugging

## File Overview
- divyabengali_step3_ls_pipe.c: Redirects the output of `ls` through a pipe to a reader process
- divyabengali_step4_passwd_grep.c: Implements `cat /etc/passwd | grep root`
- divyabengali_step5_producer_consumer_pipe.c: Producer–consumer communication using pipes
- divyabengali_step6_shared_memory_ipc.c: Producer–consumer communication using shared memory
- divyabengali_step8_pthread_fix.c: Demonstrates and fixes a race condition in pthread argument passing

## Notes
This lab was completed using instructor-provided instructions and example code.
The uploaded source files reflect my own implementation, extensions, and fixes.
Assignment documents and proprietary materials are not included.


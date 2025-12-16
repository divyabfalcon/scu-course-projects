## Lab 5 – Thread Synchronization

This lab explores synchronization techniques for multithreaded programs
using POSIX threads. The focus is on preventing race conditions and
coordinating access to shared resources.

## Concepts Covered
- Race conditions and critical sections
- Mutex locks for mutual exclusion
- Semaphores for thread synchronization
- Producer–consumer problem
- Condition variables to avoid busy waiting
- Signal handling and resource cleanup

## File Overview
- threadSync_base_modified.c:
  Modified version of an instructor-provided thread synchronization example, demonstrating mutual exclusion using synchronization primitives.

- step2_mutex_lock.c:
  Implements synchronization using mutex locks to protect a critical section.

- step3_semaphore_producer_consumer.c:
  Producer–consumer implementation using semaphores for coordination.

- step4_condition_variables.c:
  Producer–consumer implementation using condition variables to avoid busy waiting and improve efficiency.

## Notes
This lab was completed using instructor-provided instructions and starter code. The uploaded source files reflect my own implementations, modifications, and extensions. Assignment documents and other proprietary materials are not included.

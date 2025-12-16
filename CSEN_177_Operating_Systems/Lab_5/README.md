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
- step2_threadSync_modified.c:
  Modified version of an instructor-provided thread synchronization example,
  extended to correctly protect critical sections using synchronization
  primitives.

- step3_semaphore_producer_consumer.c:
  Implements the producer–consumer problem using semaphores for coordination
  between threads.

- step4_condition_variables.c:
  Implements the producer–consumer problem using condition variables to improve
  efficiency and avoid busy waiting.

## Notes
This lab was completed using instructor-provided instructions and starter code. The uploaded source files reflect my own implementations, modifications, and extensions. Assignment documents and other proprietary materials are not included.

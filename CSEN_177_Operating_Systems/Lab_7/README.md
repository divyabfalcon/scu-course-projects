# Lab 7 – Page Replacement Algorithms (Memory Management)

This lab simulates virtual memory management behavior by implementing and
evaluating page replacement algorithms. Given a sequence of page access
requests, each algorithm determines which pages produce faults under different
replacement strategies.

## Concepts Covered
- Page faults and page replacement
- Simulating a fixed-size page frame cache
- FIFO (First-In, First-Out) replacement
- LRU (Least Recently Used) replacement
- Second Chance (Clock) replacement
- Input/output redirection for automated testing
- Basic test generation and output validation

## File Overview
- divyabengali_step3_fifo.c  
  Implements FIFO page replacement and outputs the pages that result in faults.

- divyabengali_step3_lru.c  
  Implements LRU page replacement and outputs the pages that result in faults.

- divyabengali_step3_secondChance.c  
  Implements Second Chance (Clock) page replacement and outputs the pages that
  result in faults.

- divyabengali_testInputgenerator.c  
  Generates test input files containing sequences of page access requests.

- divyabengali_readOutput.c  
  Reads and summarizes simulator output for validation and debugging.

- divyabengali_step4_testCases.sh  
  Custom shell script written to automate testing of the implementations.

## Notes
This lab was completed using instructor-provided instructions and starter
materials. Proprietary assignment documents, starter code, and provided input
files are not included. The uploaded source files reflect my own
implementations, extensions, and testing utilities.

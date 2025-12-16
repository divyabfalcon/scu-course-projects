# Lab 4 – Multithreaded Matrix Multiplication

This lab focuses on developing multithreaded applications using POSIX threads
and applying concurrency to a computationally intensive problem: matrix
multiplication.

## Concepts Covered
- POSIX thread creation and synchronization
- Parallel decomposition strategies
- Thread-per-row vs. thread-per-cell designs
- Dynamic memory allocation for matrices
- Performance considerations in multithreaded programs

## File Overview
- divyabengali_step4_matrix_mult_rows.c:
  Implements matrix multiplication using N threads, where each thread computes
  one row of the result matrix.

- divyabengali_step5_matrix_mult_cells.c:
  Extends the implementation to create N×L threads, where each thread computes
  a single cell of the result matrix.

## Notes
This lab was completed using instructor-provided instructions and example code.
The uploaded source files reflect my own implementation, extensions, and design
decisions. Assignment documents and proprietary materials are not included.


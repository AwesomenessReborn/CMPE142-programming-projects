# Project #4 - Chapter 10: Page Replacement Algorithms

## Description

This program simulates three page replacement algorithms (FIFO, LRU, and Optimal) to evaluate memory management performance. It generates a random reference string and calculates page faults for a user-defined number of frames.

## Files Included

* `page_replacement.cpp` - Main C++ source code.
* `README.md` - This documentation file.

## Compilation Instructions

To compile the program:

```bash
clang++ -o page_replacement page_replacement.cpp
```

or

```bash
g++ -o page_replacement page_replacement.cpp
```

or use whichever compiler you have on your machine.

## How to run

```bash
./page_replacement
```

## Usage

Upon running, the program will prompt for two inputs:

1. Number of Page Frames: (e.g., 3, 5, or 7)
2. Length of Reference String: (e.g., 20 or 30)

## Test Cases

**Test 1:** Constraints Stress Test (Small Memory)

```bash
❯ ./page_replacement
--- Page Replacement Algorithm Simulation ---
Enter number of page frames: 3
Enter length of random page-reference string: 15

Generated Reference String: 1 2 9 0 4 7 8 4 6 6 9 5 4 8 7
--------------------------------------------------
Algorithm       | Page Faults
------------------------------
FIFO            | 13
LRU             | 13
OPT             | 11
------------------------------
```

This test case involves extremely limited resources, causing frequent swapping / fault count.

**Test 2:** Standard Workload (Medium Memory)

```bash
❯ ./page_replacement
--- Page Replacement Algorithm Simulation ---
Enter number of page frames: 5
Enter length of random page-reference string: 25

Generated Reference String: 5 1 2 8 5 7 5 5 7 8 9 6 7 8 0 0 0 7 6 4 5 5 6 2 6
--------------------------------------------------
Algorithm       | Page Faults
------------------------------
FIFO            | 11
LRU             | 11
OPT             | 9
------------------------------
```

This test case is balanced, strategically chosen size to test if LRU method starts outperforming FIFO noticably.

**Test 3:** Saturation Test (Large Memory)

```bash
❯ ./page_replacement
--- Page Replacement Algorithm Simulation ---
Enter number of page frames: 7
Enter length of random page-reference string: 30

Generated Reference String: 2 3 2 1 3 5 9 4 4 0 4 6 6 0 7 8 1 6 8 9 3 8 3 9 3 3 0 7 8 1
--------------------------------------------------
Algorithm       | Page Faults
------------------------------
FIFO            | 13
LRU             | 12
OPT             | 10
------------------------------
```

This test case is a situation with high memory availabilty. Hits become common regardless of strategy.

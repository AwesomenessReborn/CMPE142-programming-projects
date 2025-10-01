# Project 2: Multithreaded Sorting Application

## Description of the Project

This project is a C program that demonstrates multithreading by sorting a list of integers. The application implements a "divide and conquer" sorting strategy using three separate threads.

-   **Thread Creation & Division**: The main thread initializes a global array of integers.  The list is then conceptually divided into two equal halves.  Two "sorting threads" are created to handle these halves.
-   **Sorting**: Each sorting thread is responsible for sorting its assigned sublist.  It receives parameters (start and end index) to identify its portion of the array. For this implementation, the standard library's `qsort()` function is used for efficiency, but any sorting algorithm would suffice. The threads operate on the same global array, sorting their respective halves in place.
-   **Merging & Synchronization**: After the two sorting threads have completed their tasks, a third "merging thread" is created. This thread merges the two now-sorted halves from the original array into a second global array, resulting in a single, completely sorted list. 
-   **Synchronization**: The main (parent) thread uses `pthread_join()` to wait for each thread to complete its execution in the correct order: it waits for both sorters to finish before starting the merger, and then waits for the merger to finish before printing the final result. This ensures the data is processed correctly.

## Instructions for Compilation and Execution

### Compilation

1.  Place the file `multisort.c` in desired location.
2.  Compile the program using `gcc`. You must link the pthread library using the `-lpthread` flag.
    ```bash
    gcc -o multisort multisort.c -lpthread
    ```

### Execution

Execute the binary: 
```bash
./multisort
```

### Example execution

Reference `sample_p2_run.txt` for a example run of the program. 

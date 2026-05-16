# CMPE 142 – Operating Systems Programming Projects

**Author:** Hari Kotamsetti (016222167)  
**Course:** CMPE 142 – Operating Systems, San José State University

A collection of systems programming projects covering core OS concepts: kernel modules, process management, threading, memory allocation, and virtual memory.

---

## Project 1 — File Copy & Linux Kernel Modules (`project_1/`)

### Part I: POSIX File Copy (`project_1/I/FileCopy.c`)

A C program that copies a file using low-level POSIX system calls (`open`, `read`, `write`, `close`) with a 4 KB buffer. The user is prompted interactively for source and destination filenames. Error handling uses `perror()` to surface OS-level error messages. The README includes a full `strace` capture showing the exact sequence of system calls made at runtime.

**Key concepts:** file descriptors, POSIX I/O, system call tracing

### Part II: Linux Kernel Modules (`project_1/II/`)

Three loadable kernel modules written in C, all built with the shared `Makefile`:

| Module | `/proc` entry | What it does |
|---|---|---|
| `simple.c` | — | On `insmod`, prints `GOLDEN_RATIO_PRIME`, initial `jiffies`, and `HZ`; on `rmmod`, prints GCD(3300, 24) and final `jiffies` |
| `jiffies_module.c` | `/proc/jiffies` | Exposes the current value of the kernel `jiffies` counter via a proc file |
| `seconds_module.c` | `/proc/seconds` | Records `jiffies` at load time; `/proc/seconds` reads report elapsed seconds since load (`Δjiffies / HZ`) |

**Key concepts:** kernel module lifecycle (`init`/`exit`), proc filesystem, `jiffies`, `HZ`, `gcd()`

---

## Project 2 — Shell & Multithreaded Sort (`project_2/`)

### Part 1: Simple UNIX Shell (`project_2/p1/shell.c`)

A command-line shell (`osh`) implemented in C that replicates the core behavior of a POSIX shell. The shell forks a child process for every command using `fork()` + `execvp()`.

Features:
- **Background execution** — append `&` to run a command without blocking the parent
- **Command history** — `!!` re-executes the most recent command
- **I/O redirection** — `>` and `<` redirect stdout/stdin via `dup2()`
- **Pipes** — `|` connects two commands with a kernel pipe using `pipe()` + `dup2()`

**Key concepts:** `fork`, `execvp`, `wait`, `dup2`, `pipe`, inter-process communication

### Part 2: Multithreaded Sorting Application (`project_2/p2/multisort.c`)

A C program that sorts an integer array using a three-thread divide-and-conquer strategy:

1. **Sorting thread 1** — sorts the left half of the array in-place using `qsort()`
2. **Sorting thread 2** — sorts the right half of the array in-place using `qsort()`
3. **Merge thread** — created only after both sorters finish; merges the two sorted halves into a second global array

The main thread uses `pthread_join()` to enforce the correct ordering: both sorters must complete before the merger starts.

**Key concepts:** `pthread_create`, `pthread_join`, shared memory between threads, synchronization ordering

---

## Project 4 — Memory Management (`project_4/`)

### Chapter 9: Contiguous Memory Allocator (`project_4/ch9/allocator.c`)

An interactive C program that simulates a contiguous memory manager. The user specifies total memory at launch and then issues commands at a prompt:

| Command | Action |
|---|---|
| `RQ <name> <size> F\|B\|W` | Allocate memory using First Fit, Best Fit, or Worst Fit |
| `RL <name>` | Release a process's memory; adjacent free blocks are merged automatically |
| `C` | Compact memory — shifts all live processes to the front, leaving one large free hole at the end |
| `STAT` | Print the current address map of all allocated and free regions |
| `X` | Exit |

Internally implemented as a fixed-size `MemoryBlock` array (up to 1000 entries). Compaction works by copying all live blocks to a scratch buffer and rewriting them contiguously.

**Key concepts:** first/best/worst fit, external fragmentation, compaction, memory splitting

### Chapter 10: Page Replacement Simulator (`project_4/ch10/page_replacement.cpp`)

A C++ program that simulates three classic page replacement algorithms on a randomly generated page reference string. The user specifies the number of frames and the reference string length.

| Algorithm | Strategy |
|---|---|
| **FIFO** | Evicts the page that has been in memory the longest |
| **LRU** | Evicts the page that was least recently used |
| **OPT** | Evicts the page that will not be used for the longest time in the future (theoretical optimum) |

The output is a side-by-side comparison of page fault counts across all three algorithms for the same reference string, making it easy to see the performance gap between practical and optimal policies.

**Key concepts:** page faults, frame management, FIFO, LRU, Optimal (Bélády's) algorithm

---

## Repository Structure

```
CMPE142-programming-projects/
├── project_1/
│   ├── I/              # POSIX file copy (FileCopy.c)
│   └── II/             # Kernel modules (simple.c, jiffies_module.c, seconds_module.c)
├── project_2/
│   ├── p1/             # UNIX shell (shell.c)
│   └── p2/             # Multithreaded sort (multisort.c)
└── project_4/
    ├── ch9/            # Contiguous memory allocator (allocator.c)
    └── ch10/           # Page replacement simulator (page_replacement.cpp)
```

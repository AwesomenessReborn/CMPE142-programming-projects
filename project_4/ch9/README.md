# Project #4 - Chapter 9: Contiguous Memory Allocation

## **Overview**

This program simulates a contiguous memory management system. It allows users to:

1. **Request (RQ)** memory for processes using First Fit (F), Best Fit (B), or Worst Fit (W) strategies.  
2. **Release (RL)** memory, which automatically merges adjacent free blocks.  
3. **Compact (C)** memory to eliminate external fragmentation.  
4. **Report (STAT)** the current status of memory addresses.

## **Design**

The solution is implemented using a **fixed-size array** (MemoryBlock memory\[1000\]).

* **Array vs Linked List:** An array was chosen for simplicity. It allows for O(1) access during compaction and simpler logic when shifting blocks during allocation splits.  
* **Compaction:** Implemented by copying all active processes to a temporary buffer and rewriting them contiguously to the main memory, leaving a single large hole at the end.

## **How to Compile**

Run the following command in the terminal:

```bash
clang \-o allocator allocator.c
```

## **How to Run**

Start the program by specifying the total memory size (in bytes):

```bash
./allocator 1048576
```

## **Test Cases**

**Test 1**: Verify memory is requested and released, and holes are merged.

```bash
❯ ./allocator 1048576
Memory initialized with 1048576 bytes (0 to 1048575)

allocator> RQ P1 100000 F
Successfully allocated 100000 bytes to process P1
allocator> RQ P2 200000 F
Successfully allocated 200000 bytes to process P2
allocator> RQ P3 300000 F
Successfully allocated 300000 bytes to process P3
allocator> STAT

=== Memory Status ===
Addresses [0:99999] Process P1
Addresses [100000:299999] Process P2
Addresses [300000:599999] Process P3
Addresses [600000:1048575] Unused
====================

allocator> RL P2
Released memory for process P2
allocator> STAT

=== Memory Status ===
Addresses [0:99999] Process P1
Addresses [100000:299999] Unused
Addresses [300000:599999] Process P3
Addresses [600000:1048575] Unused
====================

allocator> X
Exiting...
```

**Test 2**: Verify that 'W' picks the largest hole and 'B' picks the tightest fit.

```bash
❯ ./allocator 1048576
Memory initialized with 1048576 bytes (0 to 1048575)

allocator> RQ P1 100000 F
Successfully allocated 100000 bytes to process P1
allocator> RQ P2 150000 F
Successfully allocated 150000 bytes to process P2
allocator> RQ P3 100000 F
Successfully allocated 100000 bytes to process P3
allocator> RQ P4 300000 F
Successfully allocated 300000 bytes to process P4
allocator> RQ P5 100000 F
Successfully allocated 100000 bytes to process P5
allocator> RL P2
Released memory for process P2
allocator> RL P4
Released memory for process P4
allocator> STAT

=== Memory Status ===
Addresses [0:99999] Process P1
Addresses [100000:249999] Unused
Addresses [250000:349999] Process P3
Addresses [350000:649999] Unused
Addresses [650000:749999] Process P5
Addresses [750000:1048575] Unused
====================

allocator> RQ P6 100000 W
Successfully allocated 100000 bytes to process P6
allocator> STAT

=== Memory Status ===
Addresses [0:99999] Process P1
Addresses [100000:249999] Unused
Addresses [250000:349999] Process P3
Addresses [350000:449999] Process P6
Addresses [450000:649999] Unused
Addresses [650000:749999] Process P5
Addresses [750000:1048575] Unused
====================

allocator> RQ P7 100000 B
Successfully allocated 100000 bytes to process P7
allocator> STAT

=== Memory Status ===
Addresses [0:99999] Process P1
Addresses [100000:199999] Process P7
Addresses [200000:249999] Unused
Addresses [250000:349999] Process P3
Addresses [350000:449999] Process P6
Addresses [450000:649999] Unused
Addresses [650000:749999] Process P5
Addresses [750000:1048575] Unused
====================

allocator> X
Exiting...
```

Here we see efficient and correct behavior since P7 occupies the hole left by formerly P2, thus reducing fragmentation.

**Test 3**: Verify that C moves all processes to the top and creates one big hole.

```bash
❯ ./allocator 1048576
Memory initialized with 1048576 bytes (0 to 1048575)

allocator> RQ P1 100000 F
Successfully allocated 100000 bytes to process P1
allocator> RQ P2 100000 F
Successfully allocated 100000 bytes to process P2
allocator> RQ P3 100000 F
Successfully allocated 100000 bytes to process P3
allocator> RL P2
Released memory for process P2
allocator> STAT

=== Memory Status ===
Addresses [0:99999] Process P1
Addresses [100000:199999] Unused
Addresses [200000:299999] Process P3
Addresses [300000:1048575] Unused
====================

allocator> C
Memory compacted successfully
allocator> STAT

=== Memory Status ===
Addresses [0:99999] Process P1
Addresses [100000:199999] Process P3
Addresses [200000:1048575] Unused
====================

allocator> X
Exiting...
```

**Test 4**: Ensure the program handles requests exceeding available memory

```bash
❯ ./allocator 1048576
Memory initialized with 1048576 bytes (0 to 1048575)

allocator> RQ HUGE 99999999 F
Error: Not enough memory to allocate 99999999 bytes for process HUGE
allocator> X
Exiting...
```

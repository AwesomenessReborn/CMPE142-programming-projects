# Programming Project 1: File Copy and Linux Kernel Modules

## Author: Hari Kotamsetti 016222167

## Part 1: File Copy Program (FileCopy.c)

The file copy program is implemented in C using the POSIX API for file operations. It prompts the user for a source and destination filename.

Key functions used:

- `open()`: To open files.
- `read()/write()`: To transfer data in a loop using a 4KB buffer.
- `close()`: To release file descriptors.
- `perror()`: For descriptive error handling.

### Test Cases

1. **Successful Copy:**
    - Command: `./FileCopy`
    - Source: `source.txt`
    - Destination: `destination.txt`
    - Result: Program reported success. `cat destination.txt` confirmed content was copied correctly.

    ```plaintext
    ❯ ./file_copy 
    Enter the name of the source file: source.txt
    Enter the name of the destination file: destination.txt
    File copied successfully.
    ```

2. **Error Case (Source Not Found):**
    - Command: `./FileCopy`
    - Source: `nonexistent.txt`
    - Result: Program exited with an error: "Error opening source file: No such file or directory".

    ```plaintext
    ❯ ./file_copy
    Enter the name of the source file: bab.txt
    Enter the name of the destination file: boo.txt
    Error opening source file: No such file or directory
    ```

### System Call Tracing

The `strace` utility was used to trace the system calls.

- Command: `strace ./FileCopy`
- The key system calls observed were `openat`, `read`, `write`, and `close`, which directly correspond to the POSIX functions used in the code.

```bash
execve("./file_copy", ["./file_copy"], 0x7ffe7389e650 /* 58 vars */) = 0
brk(NULL)                               = 0x556ff930e000
arch_prctl(0x3001 /* ARCH_??? */, 0x7ffead083a40) = -1 EINVAL (Invalid argument)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f4c786c9000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=37424, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 37424, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f4c786bf000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\237\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
pread64(3, "\4\0\0\0 \0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0"..., 48, 848) = 48
pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\325\31p\226\367\t\200\30)\261\30\257\33|\366c"..., 68, 896) = 68
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=2220400, ...}, AT_EMPTY_PATH) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2264656, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f4c78496000
mprotect(0x7f4c784be000, 2023424, PROT_NONE) = 0
mmap(0x7f4c784be000, 1658880, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x7f4c784be000
mmap(0x7f4c78653000, 360448, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1bd000) = 0x7f4c78653000
mmap(0x7f4c786ac000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x215000) = 0x7f4c786ac000
mmap(0x7f4c786b2000, 52816, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f4c786b2000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f4c78493000
arch_prctl(ARCH_SET_FS, 0x7f4c78493740) = 0
set_tid_address(0x7f4c78493a10)         = 7265
set_robust_list(0x7f4c78493a20, 24)     = 0
rseq(0x7f4c784940e0, 0x20, 0, 0x53053053) = 0
mprotect(0x7f4c786ac000, 16384, PROT_READ) = 0
mprotect(0x556fdc7ec000, 4096, PROT_READ) = 0
mprotect(0x7f4c78703000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7f4c786bf000, 37424)           = 0
newfstatat(1, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x5), ...}, AT_EMPTY_PATH) = 0
getrandom("\x77\xd6\xaa\xfb\x23\x09\xb6\xfe", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x556ff930e000
brk(0x556ff932f000)                     = 0x556ff932f000
newfstatat(0, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0x5), ...}, AT_EMPTY_PATH) = 0
write(1, "Enter the name of the source fil"..., 35Enter the name of the source file: ) = 35
read(0, source.txt
"source.txt\n", 1024)           = 11
write(1, "Enter the name of the destinatio"..., 40Enter the name of the destination file: ) = 40
read(0, destination.txt
"destination.txt\n", 1024)      = 16
openat(AT_FDCWD, "source.txt", O_RDONLY) = 3
openat(AT_FDCWD, "destination.txt", O_WRONLY|O_CREAT|O_TRUNC, 0644) = 4
read(3, "Lorem Ipsum is simply dummy text"..., 4096) = 1639
write(4, "Lorem Ipsum is simply dummy text"..., 1639) = 1639
read(3, "", 4096)                       = 0
close(3)                                = 0
close(4)                                = 0
write(1, "File copied successfully.\n", 26File copied successfully.
) = 26
lseek(0, -1, SEEK_CUR)                  = -1 ESPIPE (Illegal seek)
exit_group(0)                           = ?
+++ exited with 0 +++
```

## Part 2: Kernel Modules

### simple.c

This module was modified to print kernel-specific values upon loading and unloading.

- On `insmod` (in `simple_init`), it prints:
  - The value of `GOLDEN_RATIO_PRIME`.
  - The initial value of `jiffies`.
  - The system's `HZ` value.
- On `rmmod` (in `simple_exit`), it prints:
  - The greatest common divisor (GCD) of 3300 and 24.
  - The final value of `jiffies`.

[Paste your `dmesg` output showing the loading and unloading of simple.ko]

### jiffies_module.c

This module creates a file in the proc filesystem at `/proc/jiffies`.

- **Functionality**: When a user reads this file (`cat /proc/jiffies`), the module's `proc_read` function is called, which returns the current value of the `jiffies` kernel variable.
- The `/proc/jiffies` entry is created on `insmod` and removed on `rmmod`.

[Paste `dmesg` output and the output of `cat /proc/jiffies`]

### seconds_module.c

This module creates a file in the proc filesystem at `/proc/seconds`.

- **Functionality**: This module records the `jiffies` value when it is loaded. When `/proc/seconds` is read, it calculates the difference between the current `jiffies` and the starting value, then divides by `HZ` to report the total number of seconds that have elapsed since the module was loaded.
- The `/proc/seconds` entry is created on `insmod` and removed on `rmmod`.

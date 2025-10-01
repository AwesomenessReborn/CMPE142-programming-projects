# Project 1: Simple UNIX Shell

## Description of the Project

This project is a C program that implements a simple command-line shell, named `osh`. It is designed to accept user commands and execute them in separate processes. The shell supports several key features of modern shells:

-   **Command Execution**: The shell forks a child process to execute each command using the `fork()` and `execvp()` system calls. 
-   **Background Processing**: Commands can be run in the background by appending an ampersand (`&`). When a command is run in the background, the parent shell does not wait for it to complete and immediately prompts for the next command. 
-   **History**: The shell keeps a history of the most recent command. Entering `!!` re-executes that command. An error message is displayed if `!!` is used with no prior commands. 
-   **I/O Redirection**: The shell supports input redirection (`<`) and output redirection (`>`), allowing commands to read from or write to files. This is implemented using the `dup2()` system call to duplicate file descriptors. 
-   **Pipes**: The shell supports piping the output of one command to the input of another using the pipe (`|`) operator. This IPC mechanism is implemented using the `pipe()` and `dup2()` system calls. 

## Instructions for Compilation and Execution

### Prerequisites

You need a C compiler (like `gcc`) and a UNIX-like environment (Linux, macOS, or WSL on Windows).

### Compilation

Compile the program using the following command:
```bash
gcc -o shell shell.c
```

### Execution

Run the program:
```bash
./shell
```

To exit the program, simply type `exit`. 

### Example execution

Reference `sample_p2_run.txt` for a example run of the program. 


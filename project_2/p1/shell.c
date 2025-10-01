#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 80 

void parse_command(char *input, char *args[], int specialChars[], char **io_file, char *pipe_args[]) {
    // Reset flags and pointers
    for (int i = 0; i < 4; i++) specialChars[i] = 0;
    *io_file = NULL;

    int arg_count = 0;
    char *token = strtok(input, " \n\t");

    while (token != NULL) {
        if (strcmp(token, "<") == 0) {
            specialChars[0] = 1; 
            token = strtok(NULL, " \n\t");
            if (token != NULL) *io_file = token;
        } else if (strcmp(token, ">") == 0) {
            specialChars[1] = 1; 
            token = strtok(NULL, " \n\t");
            if (token != NULL) *io_file = token;
        } else if (strcmp(token, "|") == 0) {
            specialChars[2] = 1; 
            int pipe_arg_count = 0;
            while ((token = strtok(NULL, " \n\t")) != NULL) {
                pipe_args[pipe_arg_count++] = token;
            }
            pipe_args[pipe_arg_count] = NULL;
            break; 
        } else if (strcmp(token, "&") == 0) {
            specialChars[3] = 1; 
        } else {
            args[arg_count++] = token;
        }
        token = strtok(NULL, " \n\t");
    }
    args[arg_count] = NULL; 
}

int main(void) {
    char *args[MAX_LINE / 2 + 1];      
    char *pipe_args[MAX_LINE / 2 + 1]; 
    int should_run = 1;                
    char history[MAX_LINE] = "";       
    int has_history = 0;               

    while (should_run) {
        printf("osh> ");
        fflush(stdout);

        char input[MAX_LINE];
        fgets(input, MAX_LINE, stdin);

        if (strncmp(input, "!!", 2) == 0) {
            if (!has_history) {
                printf("No commands in history.\n"); 
                continue;
            }
            printf("%s", history); 
            strcpy(input, history);
        } else {
            strcpy(history, input);
            has_history = 1;
        }

        if (strncmp(input, "exit", 4) == 0) {
            should_run = 0; 
            continue;
        }

        int specialChars[4]; 
        char *io_file = NULL;
        parse_command(strtok(input, "\n"), args, specialChars, &io_file, pipe_args);

        if (args[0] == NULL) {
            continue;
        }
        
        pid_t pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Fork failed.\n");
            return 1;
        } 
        else if (pid == 0) { 
            if (specialChars[0]) { 
                int fd_in = open(io_file, O_RDONLY);
                if (fd_in < 0) {
                    fprintf(stderr, "Failed to open input file.\n");
                    exit(1);
                }
                dup2(fd_in, STDIN_FILENO); 
                close(fd_in);
            }
            if (specialChars[1]) { 
                int fd_out = open(io_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd_out < 0) {
                    fprintf(stderr, "Failed to open output file.\n");
                    exit(1);
                }
                dup2(fd_out, STDOUT_FILENO); 
                close(fd_out);
            }
            
            if (specialChars[2]) { 
                int fd[2];
                pipe(fd); 

                pid_t pid2 = fork(); 
                
                if (pid2 < 0) {
                    fprintf(stderr, "Second fork failed.\n");
                    exit(1);
                } else if (pid2 == 0) { 
                    close(fd[1]); 
                    dup2(fd[0], STDIN_FILENO); 
                    close(fd[0]);
                    if (execvp(pipe_args[0], pipe_args) == -1) {
                        fprintf(stderr, "Error executing second command.\n");
                        exit(1);
                    }
                } else { 
                    close(fd[0]); 
                    dup2(fd[1], STDOUT_FILENO); 
                    close(fd[1]);
                    if (execvp(args[0], args) == -1) {
                        fprintf(stderr, "Error executing first command.\n");
                        exit(1);
                    }
                }
            } else {
                if (execvp(args[0], args) == -1) {
                    fprintf(stderr, "Error executing command.\n");
                    exit(1);
                }
            }
        } 
        else { 
            if (!specialChars[3]) { 
                wait(NULL);
            }
        }
    }
    return 0;
}

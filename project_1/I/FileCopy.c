// FileCopy.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 4096 

int main() {
    char source_file[256];
    char dest_file[256];
    int source_fd, dest_fd;
    ssize_t bytes_read;
    char buffer[BUFFER_SIZE];

    printf("Enter the name of the source file: ");
    scanf("%255s", source_file);

    printf("Enter the name of the destination file: ");
    scanf("%255s", dest_file);

    source_fd = open(source_file, O_RDONLY);
    if (source_fd == -1) {
        // This is the required error checking 
        perror("Error opening source file");
        return 1;
    }

    dest_fd = open(dest_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd); 
        return 1;
    }

    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("Error reading from source file");
    }

    close(source_fd);
    close(dest_fd);

    printf("File copied successfully.\n");

    return 0;
}

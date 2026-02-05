#include <fcntl.h>     // For open()
#include <unistd.h>    // For read(), write(), close()
#include <stdlib.h>    // For exit()
#include <stdio.h>     // For perror()

#define BUFFER_SIZE 1024

int main() {
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Open source file
    source_fd = open("result.txt", O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening result.txt");
        exit(1);
    }

    // Open destination file
    dest_fd = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error creating copyresult.txt");
        close(source_fd);
        exit(1);
    }

    // Copy data
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to copyresult.txt");
            close(source_fd);
            close(dest_fd);
            exit(1);
        }
    }

    if (bytes_read < 0)
        perror("Error reading result.txt");

    close(source_fd);
    close(dest_fd);

    write(1, "File copied successfully using system calls.\n", 46);
    return 0;
}

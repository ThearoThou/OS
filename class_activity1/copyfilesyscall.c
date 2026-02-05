#include <stdio.h>
#include <fcntl.h>      // For open() and O_* constants
#include <unistd.h>     // For read(), write(), close()
#include <stdlib.h>     // For exit()

int main() {
    int source_fd, dest_fd;       // File descriptors
    ssize_t bytes_read, bytes_written;
    char buffer[1024];            // Buffer for data transfer

    // Open source file (result.txt) for reading
    source_fd = open("result.txt", O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening source file");
        exit(1);
    }

    // Open (or create) destination file (copyresult.txt) for writing
    dest_fd = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error opening/creating destination file");
        close(source_fd);
        exit(1);
    }

    // Copy contents from source to destination
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            exit(1);
        }
    }

    if (bytes_read < 0)
        perror("Error reading source file");

    // Close both files
    close(source_fd);
    close(dest_fd);

    printf("File copied successfully!\n");
    return 0;
}

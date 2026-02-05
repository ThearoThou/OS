#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } 
    else if (pid == 0) {  
        // Child process
        printf("Child process running ls...\n");
        execl("/bin/ls", "ls", NULL);

        // If execl fails:
        perror("execl failed");
        exit(1);
    }
    else {  
        // Parent process
        printf("Parent process: child PID = %d\n", pid);
    }

    return 0;
}

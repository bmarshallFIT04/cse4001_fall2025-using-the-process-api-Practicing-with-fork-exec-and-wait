#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    // Create new process
    int rc = fork();
    if (rc < 0) { 
      perror("fork"); 
      exit(1); 
    }
    else if (rc == 0) {
        // Child process
        _exit(0);
    } 
    else {
        // Parent process
        int status = 0;
        pid_t pid = wait(&status);
        printf("wait() returned pid=%d\n", (int)pid);
        
        // Check exit status of child
        if (WIFEXITED(status))
            printf("child exit status=%d\n", WEXITSTATUS(status));
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main(void) {
    int fd = open("q2.output", O_CREAT|O_WRONLY|O_TRUNC, 0700);
    if (fd < 0) { 
      perror("open"); 
      exit(1); 
    }

    // Create new process
    int rc = fork();
    if (rc < 0) { 
      perror("fork"); 
      exit(1); 
    }
    else if (rc == 0) {
        // Child process
        const char *msg = "child writing\n";
        if (write(fd, msg, strlen(msg)) < 0) perror("write(child)");
        _exit(0);
    } else {
        // Parent process
        const char *msg = "parent writing\n";
        if (write(fd, msg, strlen(msg)) < 0) 
          perror("write(parent)");
        wait(NULL);  // Parent waits for child to finish writing
    }
    return 0;
}

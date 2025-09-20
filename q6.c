#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    // 1st child
    pid_t c1 = fork();
    if (c1 < 0) { 
        perror("fork1"); 
        exit(1); 
    }
    if (c1 == 0)
        _exit(0);

    // 2nd child 
    pid_t c2 = fork();
    if (c2 < 0) { 
        perror("fork2"); 
        exit(1); 
    }
    if (c2 == 0)
        _exit(1);

    // Parent process
    int st1=0, st2=0;
    pid_t r1 = waitpid(c2, &st2, 0);  // Wait for c2
    pid_t r2 = waitpid(c1, &st1, 0);  // Wait for c1

    // Print results 
    if (WIFEXITED(st1)) {
        printf("Child 1 (pid=%d) exited with status=%d\n", (int)r2, WEXITSTATUS(st1));
    }
    if (WIFEXITED(st2)) {
        printf("Child 2 (pid=%d) exited with status=%d\n", (int)r1, WEXITSTATUS(st2));
    }
        
  return 0;
}

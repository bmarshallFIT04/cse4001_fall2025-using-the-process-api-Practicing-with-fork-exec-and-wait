#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int x = 100;
    printf("Initial x=%d (pid:%d)\n", x, (int)getpid());
    int rc = fork();
  
    if (rc < 0) { 
      // Fork failed: Return an error and exit
      perror("fork"); 
      exit(1); 
    } else if (rc == 0) {
        // Child
        printf("Child has x=%d (pid:%d)\n", x, (int)getpid());
        x = 200;
        printf("Child set x to %d\n", x);
    } else {
        // Parent
        printf("Parent has x=%d (pid:%d)\n", x, (int)getpid());
        x = 300;
        printf("Parent set x to %d\n", x);
    }
    return 0;
}

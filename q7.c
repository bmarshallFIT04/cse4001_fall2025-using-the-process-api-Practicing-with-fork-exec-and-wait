#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main(void) {
    int rc = fork();
    if (rc < 0) { 
        perror("fork"); 
        exit(1); 
    }
    else if (rc == 0) {
        // Child process
        if (close(STDOUT_FILENO) < 0) 
            perror("close");  // Close standard output file
        
        printf("Child stdout closed\n");  // Test - Should NOT appear on terminal
    } 
    else {
        // Parent process
        printf("Parent stdout still open\n");  // stdout still open for parent
        wait(NULL);
    }
    return 0;
}

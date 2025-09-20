#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    // Create pipe
    int p[2];
    if (pipe(p) < 0) { 
        perror("pipe"); 
        exit(1); 
    }
  
    // Fork for child process
    int rc = fork();
    if (rc < 0) { 
        perror("fork"); 
        exit(1); 
    }
    
    else if (rc == 0) {
        // Child process
        close(p[0]);  // Child doesn't need read end
        printf("hello\n");
      
        // Child signals parent and exits
        if (write(p[1], "x", 1) < 0) 
            perror("write");
        close(p[1]);
        _exit(0);
    } 
    
    else {
        // Parent process
        close(p[1]);  // Parent doesn't need write end
        
        // Parent blocks until child has printed
        char buf;      
        if (read(p[0], &buf, 1) < 0)
            perror("read");
        close(p[0]);
        printf("goodbye\n");  // Parent prints after child is done
    }
    return 0;
}

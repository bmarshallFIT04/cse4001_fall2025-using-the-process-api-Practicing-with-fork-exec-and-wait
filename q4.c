#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;

int main(int argc, char *argv[]) {
      if (argc != 2) {
      fprintf(stderr, "Variant needed: execl, execle, execlp, execv, execvp, execvpe\n");
      exit(1);
    }

    int rc = fork();
    if (rc < 0) { 
        perror("fork"); 
        exit(1); 
    }
    else if (rc == 0) {
        // Child process
        // Run bin/ls exec() varaint based on command-line arg
        if (strcmp(argv[1], "execl") == 0) {
            execl("/bin/ls", "ls", NULL);
        } else if (strcmp(argv[1], "execle") == 0) {
            execle("/bin/ls", "ls", NULL, environ);
        } else if (strcmp(argv[1], "execlp") == 0) {
            execlp("ls", "ls", NULL);
        } else if (strcmp(argv[1], "execv") == 0) {
            char *av[] = { "ls", NULL };
            execv("/bin/ls", av);
        } else if (strcmp(argv[1], "execvp") == 0) {
            char *av[] = { "ls", NULL };
            execvp("ls", av);
        } else if (strcmp(argv[1], "execvpe") == 0) {
            char *av[] = { "ls", NULL };
            execvpe("ls", av, environ);
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[1]);
            exit(1);
        }
        
        // If exec() fails:
        perror("exec* failed");
        _exit(127);
    } else {
        // Parent process
        int status;
        waitpid(rc, &status, 0);  // Wait for child to finish
    }
    return 0;
}

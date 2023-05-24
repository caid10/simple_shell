#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#define BUFFER_SIZE 1024

int main(void)
{
    char *prompt = "simple_shell> ";
    char buffer[BUFFER_SIZE];
    int status;
    pid_t pid;

    while (1) {
        printf("%s", prompt);

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;
        }

        buffer[strcspn(buffer, "\n")] = '\0'; /* Remove trailing newline character */

        pid = fork(); /* Assign value here */

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            /* Child process */
            if (execlp(buffer, buffer, (char *)NULL) == -1) {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
        } else {
            /* Parent process */
            wait(&status);
        }
    }

    return 0;
}

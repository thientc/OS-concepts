#include <stdio.h> 
#include <stdlib.h> // extern char **environ;

/**
 * @brief Prints all environment variables and their values.
 *
 * This subroutine iterates through the 'environ' global variable, which is
 * an array of pointers to strings, where each string is an environment
 * variable in the format "NAME=VALUE". The array is terminated by a NULL pointer.
 * 'environ' is a global variable declared in <stdlib.h> (or <unistd.h> in some systems)
 * It's an array of pointers to strings, where each string is an environment variable.
 * The array is terminated by a NULL pointer.
 */
int main() {
    extern char **environ;

    printf("Environment Variables:\n");

    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }

    printf("\n");
    return 0;
}
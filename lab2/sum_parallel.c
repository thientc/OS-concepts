#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "operations.h"

int main(int argc, char *argv[])
{
	printf("The shell process ID: %d\n", getppid());
	printf("Current process ID: %d\n", getpid());
	if (argc != 2)
	{
		printf("Error, only 1 argument is accepted!");
		return 1;
	}
	char *output;
	long num = strtol(argv[1], &output, 10);
	printf("%ld\n", sum_parallel(num));

	pid_t pid = fork();
	long sum_odd = 0;
	if (pid == 0)
	{
		// write the code of child-process
		long sum_odd = sum_odd_sleep(num);
		printf("Child process %d: sum_odd = %ld\n", getpid(), sum_odd);
		exit(0);
	}
	else if (pid > 0)
	{
		printf("parent process");
	}
	else
	{
		// in case of an error
	}
	pid_t pid = fork();
	long sum_even = 0;
	if (pid == 0)
	{
		// write the code of child-process
		long sum_even = sum_even_sleep(num);
		printf("Child process %d: sum_even = %ld\n", getpid(), sum_even);
		exit(0);
	}
	else if (pid > 0)
	{
		printf("parent process");
	}
	else
	{
		// in case of an error
	}
	return 0;
}

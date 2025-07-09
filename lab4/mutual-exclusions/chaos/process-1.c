/*process-1.c*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
int main(int argc, char * argv[]) {
	char * c = "Process 1 - This is operating system course.\n";
	setbuf(stderr, NULL);
	while (* c != '\0') {
		fputc(* c, stderr);
		c++;
		sleep(1);
	 }
    return 0;
}
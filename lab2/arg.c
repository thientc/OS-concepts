#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
	if(argc != 2){
		printf("Error, only 1 argument is accepted!");
		return 1;
	}
	char *output;
	long num = strtol(argv[1], &output, 10);
	printf("%ld\n", num);
	return 0;
}


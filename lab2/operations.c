#include <sys/wait.h>
#include <unistd.h>

long sum_odd(long n){
	long sum = 0;
	for(int i = 1; i <= n ; i+=2){
		sum += i;
	}
	return sum;
}
long sum_even(long n){
	long sum = 0;
	for(int i = 2; i <= n ; i+=2){
		sum += i;
	}
	return sum;
}
long sum(long n){
	return sum_odd(n) + sum_even(n);
}

long sum_even_sleep(long n){
	long sum = 0;
	for(int i = 2; i <= n ; i+=2){
		sum += i;
		sleep(100);
	}
	return sum;
}
long sum_odd_sleep(long n){
	long sum = 0;
	for(int i = 1; i <= n ; i+=2){
		sum += i;
		sleep(100);

	}
	return sum;
}

long sum_parallel(long n){
	return sum_even_sleep(n) + sum_odd_sleep(n);
}
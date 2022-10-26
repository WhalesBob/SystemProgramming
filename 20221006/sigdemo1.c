#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void f(int signum){ 
	printf("Nam Dongwoo\n");
}

int main(void){
	void f(int);
	
	signal(SIGINT, f);
	for(int i = 0; i < 10; i++){
		printf("hello \n");
		sleep(2);
	}
}
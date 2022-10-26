#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

pid_t opposite_pid;
void my_sig_handler(int signum);

int main(void){
	
	signal(SIGUSR2,my_sig_handler);
	
	// 자신의 pid 출력. (getpid 함수)
	pid_t pid = getpid();
	printf("pid = %d \n", pid);
	
	// 각각 상대의 pid 입력(by scanf)
	
	printf("Opposite PID's number ? : ");
	scanf("%d", &opposite_pid);
	
	while(1){
		printf("Wait for signal...\n");
		sleep(20);
	}
}
void my_sig_handler(int signum){
	// usr2 는 SIGUSR2 받으면 usr1 에게 SIGUSR1 전송
	// usr2 는 SIGUSR1 전송 이후 바로 exit 때리면 될것(by signal-handler)
	
	printf("GET SIGUSR2 Signal and SEND SIGUSE1 to opposite process"); // signal 2 를 입력받음.
	kill(opposite_pid,SIGUSR1);
	exit(EXIT_SUCCESS);
}
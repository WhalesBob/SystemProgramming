#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>

pid_t opposite_pid;

void my_sig_handler(int signum);

int main(void){
	
	signal(SIGUSR1,my_sig_handler);
	
	// 자신의 pid 출력. (getpid 함수)
	pid_t self_pid = getpid();
	printf("pid = %d \n", self_pid);
	
	// 각각 상대의 pid 입력(by scanf)
	printf("Opposite PID's number ? : ");
	scanf("%d", &opposite_pid);
	
	
	// usr1 => usr2 에게 "SIGUSR2" 전송
	printf("send 'SIGUSR2' to opposite signal \n");
	int sendSignalResult = kill(opposite_pid,SIGUSR2);
	
	while(1){
		printf("Wait for signal...");
		sleep(20);
	}	
	// usr1 은 먼저 SIGUSR1 받으면 종료할 것.
}
void my_sig_handler(int signum){
	// usr2 는 SIGUSR2 받으면 usr1 에게 SIGUSR1 전송
	// usr2 는 SIGUSR1 전송 이후 바로 exit 때리면 될것(by signal-handler)
	
	printf("GET SIGUSR1 Signal"); // signal 2 를 입력받음.
	exit(EXIT_SUCCESS);
}
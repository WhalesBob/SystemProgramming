#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

int count;

void my_alarm_handler(int signum);
void timePrinter(void);

int main(void){
	
	count = 0;
	
	signal(SIGALRM, my_alarm_handler); // 시그널 핸들링을 처리하는 부분. 들어오면 여기에서 시그널핸들링된다.
	alarm(5); // Process 내에 "5초 뒤에 알람을 울려!" 라고 등록하는 alarm 함수였음.
	
	while(1){
		printf("Nam Dongwoo\n");
		timePrinter();
		sleep(5);
	}
	
	return 0;
}
void my_alarm_handler(int signum){
	
	count++;
	
	if(count == 3){
		exit(EXIT_SUCCESS);
	}	
	
	alarm(5);// signal 을 처리하고 난 뒤에, 새로 process 내에 알람을 5초 내에 울리라고 등록해 둠.
}
void timePrinter(void){
	time_t ct = time(NULL);
	struct tm tm = *localtime(&ct);
	printf("%d-%d-%d H: %d, M : %d, S: %d \n"
		   ,tm.tm_year + 1900,tm.tm_mon + 1,tm.tm_mday,tm.tm_hour+9,tm.tm_min,tm.tm_sec);
}
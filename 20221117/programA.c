#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <string.h>

int main(){
	int msgqidAtoB, msgqidBtoA;
	key_t keyAtoB = 1234;
	key_t keyBtoA = 1235;
	
	msgqidAtoB = msgget(keyAtoB, IPC_CREAT | 0666);
	msgqidBtoA = msgget(keyBtoA, IPC_CREAT | 0666);
	
	char msg[100];
	
	while(1){
		printf("Enter a string to send: ");
		gets(msg);
		
		// 여기서 programB가 msg 를 보내는 부분이 나온다.
		msgsnd(msgqidAtoB,msg,strlen(msg+1),0);
		
		// 그리고 msg 가 end 이면 whlie 문을 break 한다
		if(!strcmp(msg,"end")){
			break;
		}
		
		// 다시 받아오는 부분이다. programB 로부터 메세지를 받아온다
		msgrcv(msgqidBtoA,msg,100,0,0);
		
		
		// 받은 메세지를 출력한다.
		printf("msg from programB is \" %s \" \n",msg);
	}
	
	return 0;
}
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
		// 먼저 A로부터 메세지를 받아온다
		msgrcv(msgqidAtoB,msg,100,0,0);
		
		// A로부터 받아온 메세지가 end라면, break 한다
		if(!strcmp(msg,"end")){
			break;
		}
		
		// 메세지가 A로부터 어떻게 왔는지 출력하고, 뒤에 자기 이름을 붙인다.
		printf("msg from programA is \" %s \" \n", msg);
		strcat(msg, "   DONGWOO");
		
		
		// 다시 이름 붙인 메세지를 A로 보낸다. 
		msgsnd(msgqidBtoA,msg,strlen(msg)+1,0);
	}
}
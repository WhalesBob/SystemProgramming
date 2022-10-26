#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	// src_file을 dest_file에 복사하는 프로그램
	// open,read,write,close 시스템 콜 사용
	
	// printf("%s %s\n", argv[1], argv[2]); -> 잘 들어감을 확인. 
	
	int inputFd;
	int readStatus;
	
	if((inputFd = open(argv[1],O_RDONLY)) == 0){
		fprintf(stderr, "Cannot open source file.\n");
		exit(EXIT_FAILURE);
	}
	
	int outputFd = open(argv[2],O_WRONLY | O_CREAT);
	
	int takeInput = 0;
	
	while((readStatus = read(inputFd,&takeInput, sizeof(int)))){
		write(outputFd,&takeInput, sizeof(int));
	}
	
	close(inputFd);
	close(outputFd);
	
	return 0;
}
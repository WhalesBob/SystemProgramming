#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct{
	int i;
	char c;
	float f;
}Node;

void makeNodeandWrite(int a, float b, char c,int outputFD);
void takeData(int inputFD);

int main(int argc, char* argv[]){
	
	int inputFD, outputFD;
	
	outputFD = open("hw2Binary.bin", O_RDWR | O_CREAT);
	
	makeNodeandWrite(10,3.14,'a',outputFD);
	makeNodeandWrite(20,1.11,'b',outputFD);
	makeNodeandWrite(30,2.22,'c',outputFD);
	makeNodeandWrite(40,3.33,'d',outputFD);
	makeNodeandWrite(50,4.44,'e',outputFD);
	
	
	if((inputFD = open("hw2Binary.bin", O_RDONLY)) == 0){
		fprintf(stderr,"Cannot open input file\n");
		exit(EXIT_FAILURE);
	}
	
	for(int i = 0; i < 5; i++){
		takeData(inputFD);
	}
	
	close(inputFD);
	close(outputFD);
	
	return 0;
	
}
void makeNodeandWrite(int a, float b, char c,int outputFD){
	Node node;
	node.i = a;
	node.f = b;
	node.c = c;
	
	write(outputFD,&node,sizeof(Node));
	
}
void takeData(int inputFD){
	int readStatus;
	Node takeInput;
	while((readStatus = read(inputFD,&takeInput, sizeof(Node)))){
		printf("takeInput.i = %d, takeInput.f = %lf, takeInput.c = %c\n",takeInput.i,takeInput.f, takeInput.c);
	}
}
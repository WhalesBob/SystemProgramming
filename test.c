#define MALLOC(p,s){\
    if(!((p) = malloc(s))){\
        fprintf(stderr,"Insufficient Memory\n");\
        exit(EXIT_FAILURE);\
    }\
}\

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int data;
    char name[20];
}Node;

Node* makeStruct(int data);
Node* testMake(void);

int main(void){

    Node* testPointer = makeStruct(10);
    printf("Hello World\n");
    
    return 0;
}

Node * makeStruct(int data){
    Node* p = testMake();

    p->data = data;
    strcpy(p->name, "test");

    return p;
}
Node* testMake(void){
    Node* p;
    MALLOC(p, sizeof(*p));
    return p;
}
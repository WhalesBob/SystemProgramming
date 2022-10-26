#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int fd;
	int a = 20;
	int b = 0;
	int result;
	
	printf("a : %d\n", a);
	fd = open("data.bin", O_RDWR | O_CREAT);
	
	write(fd, &a, sizeof(int));
	close(fd);
}
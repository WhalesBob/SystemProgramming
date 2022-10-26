#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void){
	int fd;
	int a = 0;
	
	int result;
	
	fd = open("data1.bin", O_RDONLY);
	
	result = read(fd, &a, sizeof(int));// 읽은 바이트를 가져오는 것임.
	printf("result = %d\n",result);
	printf("a = %d\n",a);
	close(fd);
}
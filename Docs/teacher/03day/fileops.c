#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int  main(void)
{
	int fd;
	int ret;
	char buf[128];

	fd = open("/home/lsf/test.txt",O_RDWR );
	if(fd <0){
		printf("open err\n");
		return -12;
	}

	lseek(fd,0,SEEK_END);

	ret = write(fd,"hello world\n",strlen("hello world\n")); 
	if(ret <0){
		printf("write err\n");
		close(fd); return -13;
	}

	lseek(fd, 0,SEEK_SET);


	memset(buf,0,sizeof(buf));
	ret = read(fd,buf,12);
	if(ret <0){
		printf("read err\n");
		close(fd);return -23;
	}
	printf("get read rst:%s\n",buf);

	close(fd);
}





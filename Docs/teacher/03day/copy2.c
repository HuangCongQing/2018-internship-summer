#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char **argv)
{
	int ret;
	int fd_src;
	int fd_dst;
	char buf[1024];

	if(argc != 3){
		printf("sorry ,args is %d\n",argc);
		return -12;
	}

	/*creat destiniton file argv[2]*/
	ret = creat(argv[2],S_IRWXU);
	if(ret <0){
		printf("create err\n");
		return -12;
	}

	fd_src = open(argv[1],O_RDWR);
	if(fd_src <0){
		printf("open src err\n"); 
		return -13;
	}

	fd_dst = open(argv[2],O_RDWR);
	if(fd_dst <0){
		printf("open dst err\n");
		return -13;
	}

	memset(buf,0,sizeof(buf));
	ret = read(fd_src,buf,sizeof(buf));
	if(ret <0){
		printf("read err src \n");
		return -16;
	}

	ret = write(fd_dst,buf,ret);
	if(ret <0){
		printf("write err dst\n");
		return -17;
	}

	close(fd_src);
	close(fd_dst);
}

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

int gprs_serial_init(char *filename)
{
	int fd;
	struct termios options;
	/* open file and set file to mode non-block*/	
	fd = open(filename,O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd<0){
		perror("gprs_serial_init fail to open serial port");
		return -1;
	}
	
	tcgetattr(fd,&options);
	options.c_cflag |=(CLOCAL | CREAD);
	options.c_cflag &= ~CSIZE;
	options.c_cflag &= ~CRTSCTS;
	options.c_cflag |= CS8;
	options.c_cflag &= ~CSTOPB;
	options.c_iflag |= IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	
	if((cfsetispeed(&options,B115200)) == -1){
		printf("gprs_serial_init cfsetospeed is err\n");
		return -2;
	}

	//cfsetospeed(&options,B9600);
	tcsetattr(fd,TCSANOW,&options);

	return fd;
}

int gprs_serial_send(int fd,char *msg,int len)
{
	int ret;

	ret = write(fd,msg,len);
	if(ret <0){
		printf("%s %d write %s err\n",__func__,__LINE__,msg);
		return -12;
	}
	return 0;
}

int gprs_serial_recv(int fd,char *buf,int len)
{
	int ret;

	ret = read(fd,buf,len);
	if(ret <0){
		printf("%s %d read err\n",__func__,__LINE__);
		return -11;
	}

	return 0;
}

int gprs_serial_send_than_recv_timeout
	(int fd,char *atcmd,int atlen,
	 		char *recvbuf,int buflen,int ms)
{
	int ret;
	
	ret = gprs_serial_send(fd,atcmd,atlen);
	if(ret < 0){
		printf("%s %d send %s err\n",__func__,__LINE__,atcmd);
		return -14;
	}
	usleep(ms * 1000);
	ret = gprs_serial_recv(fd,recvbuf,buflen);
	if(ret < 0){
		printf("%s %d send %s than recv  err\n",__func__,__LINE__,atcmd);
		return -15;
	}
	return 0;
}


int gprs_serial_send_than_recv_match_timeout
	(int fd,char *atcmd,int atlen,
	 	char *recvbuf,int buflen,char *match,
			int ms)
{
	int ret;
	
	ret = gprs_serial_send(fd,atcmd,atlen);
	if(ret < 0){
		printf("%s %d send %s err\n",__func__,__LINE__,atcmd);
		return -14;
	}
loop:
	usleep(ms * 1000);
	ret = gprs_serial_recv(fd,recvbuf,buflen);
	if(ret < 0){
		printf("%s %d send %s than recv  err\n",__func__,__LINE__,atcmd);
		return -15;
	}

	if(!strstr(recvbuf,match)){  // no match
		goto loop;	
	}

	return 0;
}
int gprs_serial_send_than_recv_match_step_cnt
	(int fd,char *atcmd,int atlen,
	 	char *recvbuf,int buflen,char *match,
			int stepms,int cnt)
{
	int ret;
	
	ret = gprs_serial_send(fd,atcmd,atlen);
	if(ret < 0){
		printf("%s %d send %s err\n",__func__,__LINE__,atcmd);
		return -14;
	}

	if(recvbuf == NULL){  //only send 
		return 0;
	}
loop:
	cnt--;
	usleep(stepms* 1000);
	ret = gprs_serial_recv(fd,recvbuf,buflen);
	if(ret < 0){
		printf("%s %d send %s than recv  err\n",__func__,__LINE__,atcmd);
		if(cnt >0){
			goto  loop;
		}else {
			printf("%s %d atcmd%s recv err\n",__func__,__LINE__,atcmd);
			return -16;	
		}
	}

	if(!strstr(recvbuf,match)){  // no match
	
		if(cnt >0){
			goto loop;
		}else {
			printf("%s %d atcmd%s recv err\n",__func__,__LINE__,atcmd);
			return -17;
		}
	}

	return 0;
}


int gprs_serial_deinit(int fd)
{
	close(fd);
	return 0;
}

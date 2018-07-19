#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "gprs.h"

int serial_fd;

int phone_call(int fd, char *phonenum)
{
	char cmd[64];
	char recvbuf[64];
	int ret;

	memset(cmd,0,sizeof(cmd));
	memset(recvbuf,0,sizeof(recvbuf));
	sprintf(cmd,"ATD%s;\r",phonenum);
	ret = gprs_serial_send_than_recv_match_step_cnt
		(fd,cmd,strlen(cmd),recvbuf,sizeof(recvbuf),
		   "OK",100,10);
	if(ret <0){
		printf("%s %d err\n",__func__,__LINE__);
		return -18;
	}

	return 0;
}


int phone_handup(int serial_fd)
{
	int ret;
	char recvbuf[32];

	ret = gprs_serial_send_than_recv_match_step_cnt
	  (serial_fd,"ATH\r",strlen("ATH\r"),
	     recvbuf,sizeof(recvbuf),"OK",10,100);
	if(ret <0){
		printf("%s %d err\n",__func__,__LINE__);
		return -14;
	}

	return 0;
}

int emsg_send(int serial_fd,char *phonenum,char *msg,int len)
{
	int ret;
	char atcmd[64];
	char recvbuf[64];

	memset(atcmd,0,sizeof(atcmd));
	sprintf(atcmd,"AT+CMGF=1\r");
	ret = gprs_serial_send_than_recv_match_step_cnt
		    (serial_fd,atcmd,strlen(atcmd),
			   recvbuf,sizeof(recvbuf),"OK",10,50);
	if(ret <0){
		printf("%s %d send %s err\n",__func__,__LINE__,atcmd);
		return -12;
	}


	memset(atcmd,0,sizeof(atcmd));
	sprintf(atcmd,"AT+CMGS=\"%s\"\r",phonenum);
	ret = gprs_serial_send_than_recv_match_step_cnt
		    (serial_fd,atcmd,strlen(atcmd),
			   recvbuf,sizeof(recvbuf),">",10,50);
	if(ret <0){
		printf("%s %d send %s err\n",__func__,__LINE__,atcmd);
		return -12;
	}


	memset(atcmd,0,sizeof(atcmd));
	sprintf(atcmd,"%s\x1a\r",msg);
	ret = gprs_serial_send_than_recv_match_step_cnt
		    (serial_fd,atcmd,strlen(atcmd),
			   NULL,0,NULL,10,50);
	if(ret <0){
		printf("%s %d send %s err\n",__func__,__LINE__,atcmd);
		return -12;
	}


	return 0;
}

int main(int argc,char **argv)
{
	int ret;

	serial_fd = gprs_serial_init("/dev/ttyUSB2");
	if(serial_fd <0){
		printf("%s %d init err\n",__func__,__LINE__);
		return -12;
	}
#if  0
	ret= phone_call(serial_fd,"18875141504");
	if(ret <0){
		printf("main phone call err\n");
		return -13;
	}
	printf("call success\n");

	usleep(40*1000*1000);

	ret = phone_handup(serial_fd);
	if(ret <0){
		printf("main phone handup err\n");
		return -15;
	}
	printf("handup ok\n");
#endif

	ret= emsg_send(serial_fd,"18875141504","hello come from Mr W.",20);
	if(ret <0){
		printf("msg send err\n");
		return -23;
	}
	printf("msg send ok\n");

	sleep(100);

	return 0;
}

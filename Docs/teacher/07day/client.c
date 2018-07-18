#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "common.h"



int main(int argc,char **argv)
{
	int socket_fd;
	int i = 0;
	struct msg  msgcli;
	struct sockaddr_in serv_addr;
    char buf[32];	
	socklen_t addrlen;

	int ret;

	/*creat socket fd*/
	socket_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(socket_fd <0){
		printf("creat socket err\n");
		return -12;
	}

	while(1) {
		memset(buf,0,sizeof(buf));
		printf("pls input word:");
		scanf("%s",buf);

		memset(&msgcli,0,sizeof(msgcli));
		msgcli.type = 0;
		strcpy(msgcli.word,buf);
		msgcli.wordlen = strlen(buf);

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(COMM_PORT);
		serv_addr.sin_addr.s_addr = inet_addr("8.12.22.209");
		ret = sendto(socket_fd,&msgcli,sizeof(msgcli),0,(struct sockaddr * )&serv_addr,sizeof(serv_addr));
		if(ret <0){
			printf("sendto err\n");
			return -15;
		}
#if    1    //client get server response
		memset(&msgcli,0,sizeof(msgcli));
		addrlen = sizeof(serv_addr);
		ret = recvfrom(socket_fd,&msgcli,sizeof(msgcli),0,(struct sockaddr *)&serv_addr,&addrlen);
		if(ret <0){
			printf("cli recvfrom err\n");
			return -34;
		}

		if(msgcli.result == -1 ){
			printf("cli get rsp: serv find failed\n");
			continue;
		}

		if(msgcli.type != 1){
			printf("cli get  resp no come from serv\n");
			continue;
		}

		printf("cli get serv rsp:%s\n",msgcli.resp);
#endif
	}


	close(socket_fd);
}






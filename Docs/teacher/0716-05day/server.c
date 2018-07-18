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
	struct msg msgser;
	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;
	socklen_t addrlen;

	char buf[128];

	int ret;

	/*creat socket fd*/
	socket_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(socket_fd <0){
		printf("creat socket err\n");
		return -12;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(COMM_PORT);
	//serv_addr.sin_addr.s_addr = inet_addr("192.168.43.234");
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(socket_fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if(ret <0){
		printf("serv bind err\n");
		return -23;
	}
	while(1) {
		addrlen = sizeof(client_addr);
		memset(&msgser,0,sizeof(msgser));
		ret = recvfrom(socket_fd,&msgser,sizeof(msgser),0, 
				(struct sockaddr *)&client_addr,&addrlen);
		if(ret <0){
			printf("serv recv from err\n");
			return -24;
		}

		printf("serv recvfrom stat:tmp%d hidm%d stat:%s des:%s\n",
				msgser.temp,msgser.hidm,msgser.stat,msgser.des);

#if   1
		memset(buf,0,sizeof(buf));
		sprintf(buf,"Ur msg got,tmp%d hidm%d stat:%s",
				msgser.temp,msgser.hidm,msgser.stat);
		ret = sendto(socket_fd,buf,sizeof(buf),0,
				(struct sockaddr *)&client_addr,sizeof(client_addr));
		if(ret <0){
			printf("serv sendto cli err\n");
			return -14;
		}
		printf("serv sendto msg:%s\n",buf);
#endif
	}
	close(socket_fd);
}






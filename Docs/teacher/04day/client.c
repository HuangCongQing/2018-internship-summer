#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc,char **argv)
{
	int socket_fd;
	char buf[128];
	struct sockaddr_in serv_addr;
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
		strcpy(buf,"hello serv: i am client");

		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(5885);
		serv_addr.sin_addr.s_addr = inet_addr("8.12.22.209");
		ret = sendto(socket_fd,buf,sizeof(buf),0,(struct sockaddr * )&serv_addr,sizeof(serv_addr));
		if(ret <0){
			printf("sendto err\n");
			return -15;
		}

		sleep(1);
	}


	close(socket_fd);
}






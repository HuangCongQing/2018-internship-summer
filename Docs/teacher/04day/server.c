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
	struct sockaddr_in client_addr;
	socklen_t addrlen;

	int ret;

	/*creat socket fd*/
	socket_fd = socket(AF_INET,SOCK_DGRAM,0);
	if(socket_fd <0){
		printf("creat socket err\n");
		return -12;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(5885);
	//serv_addr.sin_addr.s_addr = inet_addr("192.168.43.234");
	serv_addr.sin_addr.s_addr = inet_addr("8.12.22.209");
	ret = bind(socket_fd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if(ret <0){
		printf("serv bind err\n");
		return -23;
	}
	while(1) {
		addrlen = sizeof(client_addr);
		memset(buf,0,sizeof(buf));
		ret = recvfrom(socket_fd,buf,sizeof(buf),0, (struct sockaddr *)&client_addr,&addrlen);
		if(ret <0){
			printf("serv recv from err\n");
			return -24;
		}

		printf("serv recvfrom data:%s\n",buf);
	}
	close(socket_fd);
}






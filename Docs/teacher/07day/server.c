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
	FILE *fp;

	int socket_fd;
	struct msg msgser;
	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;
	socklen_t addrlen;

	char buf[1024];

	int ret;
	char *pt_word;

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

		/*open file*/
		fp = fopen("./dic.txt","r");
		if(fp==NULL){
			printf("serv open err\n");
			return -12;
		}
		
loop:
		memset(buf,0,sizeof(buf));
		pt_word = fgets(buf,sizeof(buf),fp);
		if(pt_word == NULL){   //file end
			msgser.type = 1;
			msgser.result = -1;
			strcpy(msgser.resp,"sorry,no word find");
			ret = sendto(socket_fd,&msgser,sizeof(msgser),0,
				(struct sockaddr *)&client_addr,sizeof(client_addr));
			if(ret <0){
				printf("serv sendto cli err\n");
				return -14;
			}
			
			fclose(fp);
			continue;   //next time
		}

		ret = strncmp(msgser.word,buf,msgser.wordlen);
		if(ret != 0){   //read next line
			goto loop;	
		}
		
		fclose(fp);

		// find it
		msgser.type = 1;
		msgser.result = 0;
		strcpy(msgser.resp,buf);
		ret = sendto(socket_fd,&msgser,sizeof(msgser),0,
				(struct sockaddr *)&client_addr,sizeof(client_addr));
		if(ret <0){
			printf("serv sendto cli err\n");
			return -14;
		}
	}
	close(socket_fd);
}






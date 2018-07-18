#ifndef			COMMON_H
#define			COMMON_H

#define	   COMM_PORT   5999

struct msg {
	char type;   //0-cli2serv  1-serv2cli
	// cli2serv
	char word[32];
	char wordlen;
	//serv2cli
	char resp[128];
	char result;   //-1 err  0-success
};


#endif

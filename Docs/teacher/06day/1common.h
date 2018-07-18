#ifndef			COMMON_H
#define			COMMON_H

#define	   COMM_PORT   65533

#define   CLI2SERV_CAPTURE  0
#define	  CLI2SERV_DISPLAY  1
#define	  SERV2CLI_RESP		2

struct msg {
	char type;  //0-capture 1-display 2-serv resp

	char temp; 
	char hidm;
	char aqi;
	char stat[32];
	char des[128];
};


#endif

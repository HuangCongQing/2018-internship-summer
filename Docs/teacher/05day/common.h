#ifndef			COMMON_H
#define			COMMON_H

#define	   COMM_PORT   5999

struct msg {
	char temp; 
	char hidm;
	char stat[32];
	char des[128];
};


#endif

#ifndef		GPRS_H
#define		GPRS_H

int gprs_serial_init(char *filename);

int gprs_serial_send_than_recv_match_step_cnt(
	int fd,char *atcmd,int atlen,char *recvbuf,int buflen,
		char *match,int stepsms,int cnt);
		
int gprs_serial_deinit(int fd);

#endif

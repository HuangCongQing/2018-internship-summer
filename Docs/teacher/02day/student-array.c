#include <stdio.h>
#include <string.h>

struct student{
	int id;
	char name[32];
	int year; int month;int day;
	char home[128];
	double height;double weight;
	char sex;
	//...........
};


void main(void)
{
	int i;
	struct student  stu[10];

	for(i=0;i<10;i++){
		stu[i].id = 201500+i;
		stu[i].sex =  (stu[i].id%2==0) ? 'M' :'W';
		stu[i].day = i +1;
	}


	for(i=0;i<10;i++){
		printf("%dst id:%d sex:%c day%d\n",
			i,	stu[i].id,stu[i].sex,stu[i].day);
	}
}

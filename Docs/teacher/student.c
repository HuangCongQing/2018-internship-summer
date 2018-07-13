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

	struct student  liu;
	liu.id = 201521123;
	strcpy(liu.name,"liuqiaozhi");
	liu.year = 1997;liu.month=2;liu.day=30;
	strcpy(liu.home,"chongqingjiulongpomaoxiangou");
	liu.weight = 49.9; liu.height = 170.2;
	liu.sex = 'M';

	printf("liu stu info:id=%d name:%s\n",
			liu.id,liu.name);
	printf("liu stu year:%d month:%d day:%d\n",
			liu.year,liu.month,liu.day);
	printf("home:%s\n",liu.home);

}

#include <stdio.h>
#include <string.h>

struct datetime {
	int year;
	int month;
	int day;
};

struct student{
	int id;
	char name[32];
	struct datetime date;	
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
	liu.date.year = 1997;liu.date.month=2;
	liu.date.day = 30; 
	strcpy(liu.home,"chongqingjiulongpomaoxiangou");
	liu.weight = 49.9; liu.height = 170.2;
	liu.sex = 'M';

	printf("liu stu info:id=%d name:%s\n",
			liu.id,liu.name);
	printf("liu stu year:%d month:%d day:%d\n",
			liu.date.year,liu.date.month,liu.date.day);
	printf("home:%s\n",liu.home);

}

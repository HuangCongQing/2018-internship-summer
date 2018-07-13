#include <stdio.h>
#include <string.h>

struct cat {
	char name[32];
	char sex;
	int age;
	double weight;
	double length;
	char pinzhong[32];
	//......
};

void main(void)
{
	int           i = 5;
	struct cat    aijicat; 

	strcpy(aijicat.name , "xiaohua");
	aijicat.sex = 'W';
	aijicat.age = 1;
	aijicat.weight = 1.1;
	aijicat.length = 15.8;
	strcpy(aijicat.pinzhong,"aiji");

	printf("i=%d\n",i);
	printf(
	"xiaohua info name:%s sex:%c age:%d  weight:%lf length:%lf pinzhong:%s\n",
	  aijicat.name,aijicat.sex,aijicat.age,aijicat.weight,
	  aijicat.length,aijicat.pinzhong);


}

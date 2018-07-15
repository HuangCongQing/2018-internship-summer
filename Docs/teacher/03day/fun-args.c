#include <stdio.h>
#include <string.h>

int main(int argc,char **argv)
{
	//argc means  cnt of argument
	//argv means  array of string 

	int i;
	printf("cur code name:%s\n",argv[0]);
	printf("args cnt is %d\n",argc);

	for(i=0;i<argc;i++){
		printf("%dst -- %s\n",i,argv[i]);
	}

	if(   strstr ( argv[1] ,  "11" ) ){
		printf("U have 1 apple\n");
	}else if( strstr(argv[1],"22")){
		printf("U have 2 aplle\n");
	}else if(strstr(argv[1],"33")){
		printf("U have 3 apple\n");
	}



	return 0;
}


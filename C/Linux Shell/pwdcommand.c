#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc,char* argv[]){
	char path[256];
	getcwd(path,sizeof(char)*255);
	if(argc==1)
		printf("%s\n",path);	
	else{
		write(STDOUT_FILENO,path,sizeof(char)*strlen(path));
	}
	return 0;
}
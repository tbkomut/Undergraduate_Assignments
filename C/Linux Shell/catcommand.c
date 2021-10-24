#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void readPipe(char* filename);
void readFile(char* filename);
void readPipe2();
void outStream(char *filename);

int
main(int argc, char* argv[]){
	char filename[255];
	char type[255];
	int n;
	if(argc==2){
		n=sscanf(argv[1],"%s%s",filename,type);
		if(strcmp(filename,"<")==0)
			readPipe(type);
		else{
			if(strcmp(type,"|")==0)
				readPipe(filename);
			else if(strcmp(type,">")==0)
				readPipe(filename);
			else
			readFile(filename);
		}
	}	
	else
		readPipe2();
	return 0;
}

void 
readPipe(char* filename){
	int fd;
	char buff;
	if((fd=open(filename,O_RDONLY))==-1){
		perror("File open error. ");
		exit(1);
	}
	while(read(fd,&buff,sizeof(char))>0)
		write(STDOUT_FILENO,&buff,sizeof(char));
//	close(fd);
}

void 
readFile(char* filename){
	int fd;
	char buff;
	if((fd=open(filename,O_RDONLY))==-1){
		perror("File open error. ");
		exit(1);
	}
	while(read(fd,&buff,sizeof(char))>0)
		printf("%c",buff);
}

void 
readPipe2(){
	char buff;
	while(read(STDIN_FILENO,&buff,sizeof(char))>0)
		printf("%c",buff);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void readPipe();
void readFile(char* filename);
void readPipe2(char* filename);

int
main(int argc, char* argv[]){
	char filename[255];
	char type[255];
	int n;	
	if(argc==2){
		n=sscanf(argv[1],"%s%s",filename,type);
		if(strcmp(filename,"<")==0)
			readPipe2(type);
		else{
			if(strcmp(type,"|")==0)
				readPipe2(filename);
			else
				readFile(filename);
		}
	}
	else{
		readPipe();		
	}
	return 0;
}

void 
readPipe(){
	char buff;
	int line=0;
	if(read(STDIN_FILENO,&buff,sizeof(char))>0)
		line++;
	while(read(STDIN_FILENO,&buff,sizeof(char))>0){
		if(buff=='\n')
			line++;
	}
	printf("%d",line);
}

void 
readFile(char* filename){
	int fd;
	char buff;
	int line=0;
	if((fd=open(filename,O_RDONLY))==-1){
		fprintf(stderr,"No such a file\n");
		exit(1);
	}
	if(read(fd,&buff,sizeof(char))>0)
		line++;
	while(read(fd,&buff,sizeof(char))>0)
		if(buff=='\n')
			line++;
	printf("%d",line);
	close(fd);
}

void 
readPipe2(char* filename){
	int fd;
	char buff;
	int line=0;
	char str[10];
	int i;
	if((fd=open(filename,O_RDONLY))==-1){
		fprintf(stderr,"No such a file\n");
		exit(1);
	}
	if(read(fd,&buff,sizeof(char))>0)
		line++;	
	while(read(fd,&buff,sizeof(char))>0){
		if(buff=='\n')
			line++;
	}
	sprintf(str,"%d",line);
	for(i=0;str[i]!='\0';++i)
		write(STDOUT_FILENO,&str[i],sizeof(char));	
}
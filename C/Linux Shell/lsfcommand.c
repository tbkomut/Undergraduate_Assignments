#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

void withPipe();
void notPipe(char* path);
int isDirectory(char *path);

int
main(int argc,char* argv[]){
	char path[255];
	char isPipe[10];
	int n;

	n=sscanf(argv[1],"%s %s",isPipe,path);

	if(n==1)
		notPipe(isPipe);
	else
		withPipe(path);

	return 0;
}

void 
withPipe(char *path){
	DIR* direct;
	struct dirent* dir;
	struct stat item;
	char str[10];
	int i;

	if((direct=opendir(path))==NULL){
		printf("Directory is not exit\n");
		exit(1);
	}
	while((dir=readdir(direct))!=NULL){
		if(strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){	
			if(isDirectory(dir->d_name)==0){
				if(lstat(dir->d_name,&item)==-1){
					perror("Lstat error:");
					exit(1);
				}
				if(S_ISREG(item.st_mode))
					write(STDOUT_FILENO,"R ",sizeof(char)*2);
				else
					write(STDOUT_FILENO,"S ",sizeof(char)*2);
				sprintf(str,"%d",(int)item.st_size);
				for(i=0;str[i]!='\0';++i)
					write(STDOUT_FILENO,&str[i],sizeof(char));	
				write(STDOUT_FILENO,"\t",sizeof(char));							
				write(STDOUT_FILENO,&dir->d_name,sizeof(char)*strlen(dir->d_name));
				write(STDOUT_FILENO,"\n",sizeof(char));
			}
		}
	}

}

void 
notPipe(char* path){
	DIR* direct;
	struct dirent* dir;
	struct stat item;

	if((direct=opendir(path))==NULL){
		printf("Directory is not exit\n");
		exit(1);
	}
	while((dir=readdir(direct))!=NULL){
		if(strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){	
			if(isDirectory(dir->d_name)==0){
				if(lstat(dir->d_name,&item)==-1){
					perror("Lstat error:");
					exit(1);
				}
				if(S_ISREG(item.st_mode))
					printf("R ");
				else
					printf("S ");
					printf("%d\t",(int)item.st_size);
					printf("%s\n",dir->d_name);
			}
		}
	}

}

int 
isDirectory(char *path){
	struct stat statbuf;
	if (stat(path, &statbuf) == -1)
		return 0;
	else
		return S_ISDIR(statbuf.st_mode);
}
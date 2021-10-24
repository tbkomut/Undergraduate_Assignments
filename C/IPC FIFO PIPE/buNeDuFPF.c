/*
	System Programming HW04
	Name: Taip Bayram
	Surname: Komut
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/file.h>

void basePostOrder(char* path);
int postOrderApply (char* path,int pathfun(char *path1));
int sizepathfun (char* path);
int isDirectory(char *path);
void parentProcess(char *path);

char parameter[]="-z";
/* Global fifo file descriptor	*/
int fd;
/* It's a counter for child processes in current directory.	*/
static volatile int childCount=0;
/* It's total child Process Count*/
int totalChild=0;

int 
main(int argc,char* argv[]){
	if (argc!=2 && argc!=3){
		printf("Argument counter is invalid. It should be 2 or 3.\n");
		printf("Command line arguments have two options\n");
		printf("These are (prog -z pathname) or (prog pathname)\n");
		exit(1);
	}		
	if(argc==2){
		if(strcmp(argv[1],parameter)==0){
			printf("You can't -z argument that special words as a path.\n");
			exit(1);
		}
		strcpy(parameter,"");
		parentProcess(argv[1]);
	}
	else{
		if(strcmp(argv[1],"-z")==0)
			parentProcess(argv[2]);	
		else{
			printf("Du utility argument is invalid. It should be -z or no argument.\n");
			exit(1);
		}
	}
	return 0;
}

int 
postOrderApply (char* path,int pathfun(char *path1)){
	DIR* direct;
	struct dirent* dir;
	char* workingPath;
	int i;	
	int strSize=strlen(path);
	int result=0;
	pid_t pid;
	int pfd[2];
	int subResult=0;

	if((workingPath=calloc(sizeof(char),strSize+200))==NULL){
		perror("Allocation error, ");
		exit(1);
	}	
	strcat(workingPath,path);
	if((direct=opendir(workingPath))==NULL){
		printf("Directory is not exit\n");		
		free(workingPath);
		exit(1);
	}
	while((dir=readdir(direct))!=NULL){
		if(strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
			strcat(workingPath,"/");
			strcat(workingPath,dir->d_name);			
			if(isDirectory(workingPath)==0){
				/*	I used pipe for two modes But the pipe stores extra size of subdirectories in -z mode. */
				if(pipe(pfd)==-1){
					perror("Pipe error, ");
					exit(1);
				}
				if((pid=fork())==-1){
					perror("Fork error, ");
					exit(1);
				}
				else if(pid==0){
					close(pfd[0]);
					strcpy(path,workingPath);
					free(workingPath);
					closedir(direct);
					if(strcmp(parameter,"-z")==0)			
						subResult=postOrderApply(path,pathfun);
					else{
						postOrderApply(path,pathfun);
						subResult=0;
					}
					if(strcmp(parameter,"-z")==0)
						write(pfd[1],&subResult,sizeof(int));
					totalChild++;
					write(pfd[1],&totalChild,sizeof(int));
					close(pfd[1]);
					exit(0);
				}
				else{
					close(pfd[1]);	
					strcpy(workingPath,path);
					if(strcmp(parameter,"-z")==0)
						read(pfd[0],&subResult,sizeof(int));
					read(pfd[0],&totalChild,sizeof(int));
					result+=subResult;			
					close(pfd[0]);
					childCount++;					
				}
			}
			else{
				int handle=(pathfun)(workingPath);
				if(handle==-1){
					char *id=malloc(20*sizeof(char));
					char special[]="Special_file_";

					sprintf(id,"%d",(int)getpid());
					write(fd,id,sizeof(char)*strlen(id));	
					write(fd,"\t",sizeof(char));
					write(fd,"-1",sizeof(char)*2);	
					write(fd,"\t",sizeof(char));		
					write(fd,special,sizeof(char)*strlen(special));	
					write(fd,dir->d_name,sizeof(char)*strlen(dir->d_name));
					write(fd,"\n",sizeof(char));
					handle=0;
					free(id);
				}
				else
					result+=handle;
				strcpy(workingPath,path);				
			}			
		}
	}	
	if(strcmp(parameter,"-z")==0){
		char *size=malloc(20*sizeof(char));
		char *id=malloc(20*sizeof(char));
		sprintf(id,"%d",(int)getpid());
		sprintf(size,"%d",result/1024);

		write(fd,id,sizeof(char)*strlen(id));	
		write(fd,"\t",sizeof(char));
		write(fd,size,sizeof(char)*strlen(size));	
		write(fd,"\t",sizeof(char));		
		write(fd,path,sizeof(char)*strSize);	
		write(fd,"\n",sizeof(char));
		free(size);
		free(id);
	}
	else{
		char *size=malloc(20*sizeof(char));
		char *id=malloc(20*sizeof(char));
		result=result/1024;

		sprintf(id,"%d",(int)getpid());
		sprintf(size,"%d",result);

		write(fd,id,sizeof(char)*strlen(id));	
		write(fd,"\t",sizeof(char));
		write(fd,size,sizeof(char)*strlen(size));	
		write(fd,"\t",sizeof(char));		
		write(fd,path,sizeof(char)*strSize);	
		write(fd,"\n",sizeof(char));
		free(size);
		free(id);
	}
	if(closedir(direct)==-1){
		perror("Close directory error, ");
		free(workingPath);	
		exit(1);
	}
	free(workingPath);

	/* Zombie children are dead in here for given parallelism.	*/
	for(int i=0;i<childCount;++i)
		waitpid(-1,NULL,WNOHANG);
/*	I checked with using "top -d 1" command in terminal and sleep function for zombies */
/*	sleep(5); */

	return result;
}

void 
parentProcess(char *path){
	if(isDirectory(path)==0){
		pid_t pid;

		/*	
			Working directory should be /home/gtuvirt otherwise mkfifo error.
		*/
		char fifoname[]="131044010sizes";
		int upfd[2];

		unlink(fifoname);

		/*	Pipe is useful to transfer number of child process in this function(main process).	*/
		if(pipe(upfd)==-1){
			perror("Pipe error, ");
			exit(1);
		}
		if((pid=fork())==-1){
			perror("Fork error, ");
			exit(1);
		}
		else if(pid==0){
			close(upfd[0]);
			fd=open(fifoname,O_WRONLY);
			postOrderApply(path,sizepathfun);
			totalChild++;
			write(upfd[1],&totalChild,sizeof(int));
			close(upfd[1]);		
			close(fd);
			exit(0);
		}
		else{
			char buffer;
			int pfd;
			close(upfd[1]);
			/* We have only single global fifo 	*/
			if(mkfifo(fifoname,0666)==-1){
				perror("Fifo error, ");	
				exit(1);
			}
			pfd=open(fifoname,O_RDONLY);
			printf("PID\tSIZE\tPATH\n");
			while(read(pfd,&buffer,sizeof(char))>0)
				printf("%c",buffer);
			read(upfd[0],&totalChild,sizeof(int));
			close(upfd[0]);
			printf("%d child processes created. Main process is %d.\n",totalChild,(int)getpid());			
			if(close(pfd)==-1){
				perror("Close error, ");
				exit(1);
			}
			if(unlink(fifoname)==-1){
				perror("Unlink error, ");
				exit(1);
			}
			waitpid(-1,NULL,WUNTRACED);
		}
	}
	else{
		printf("Given path isn't a directory!\n");
		exit(1);
	}
/*	I checked with using "top -d 1" command in terminal and sleep function for zombies */
/*	sleep(5); */
}

int 
isDirectory(char *path){
	struct stat statbuf;
	if (lstat(path, &statbuf) == -1){
		perror("System path error:");
		exit(1);
	}
	if(S_ISDIR(statbuf.st_mode)){
		return 0;
	}
	else
		return 1;
}

int 
sizepathfun (char * path){
	struct stat buff;
	if(lstat(path,&buff)==-1){
		perror("System path error, ");
		exit(1);
	}
	if(S_ISREG(buff.st_mode)){
		return buff.st_size;
	}
	else
		return -1;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#define MODE S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

void shellProcess();
/*	Evalution of operations 	*/
void pipewithFork(char* command,char* currentDirectory,char* permanentDirectory,int rv);
void onlyFork(char* command,char* currentDirectory,char* permanentDirectory);

/*Input parsing for our operations.*/
void leftOneSpaces();

/*	Input conditions	*/
int commandCondition(char* command);
int streamCondition(char* command);
int pipeCondition(char* command);
int pipeCommand(char* command); 

/* Nonexecutables	*/
int exitShell(char* command);
void helpUtility();
void cdUtility(char* currentDirectory,char* argument);
void childProcess(char* com,char* currentDirectory,char* permanentDirectory);

/*	Signal Handler	*/

static void 
sigHandler(int sig){

	if(sig==SIGTERM){
		printf("\nProgram exit from a signal.\n");
		exit(1);
	}

}

int
main(){
	shellProcess();
	return 0;
}

void 
shellProcess(){
	char* command;
	char* currentDirectory;
	char* permanentDirectory;
	int rv;
	struct sigaction sa;

	if((command=calloc(sizeof(char),256))==NULL){
		perror("System heap error =>");
		exit(1);
	}
	if((currentDirectory=calloc(sizeof(char),256))==NULL){
		perror("System heap error =>");
		exit(1);
	}
	if((permanentDirectory=calloc(sizeof(char),256))==NULL){
		perror("System heap error =>");
		exit(1);
	}
	if(getcwd(permanentDirectory,sizeof(char)*255)==NULL){
		perror("Utility links aren't protected =>");
		exit(1);
	}

	sigemptyset(&sa.sa_mask);
	sa.sa_flags=0;
	sa.sa_handler=sigHandler;

	do{
		do{
			getcwd(currentDirectory,sizeof(char)*255);
			printf("@user_name %s :",currentDirectory);
			printf("$ ");
			sigaction(SIGTERM,&sa,NULL);	
			fgets(command,255,stdin);
			command[strlen(command)-1]='\0';
			leftOneSpaces(command);
		}while((rv=commandCondition(command))==0);	
		if(rv==1)
			onlyFork(command,currentDirectory,permanentDirectory);
		else if(rv==2 || rv==3 || rv==4)
			pipewithFork(command,currentDirectory,permanentDirectory,rv);
	}while(exitShell(command));
	free(command);
	free(currentDirectory);
	free(permanentDirectory);
}


void 
pipewithFork(char* command,char* currentDirectory,char* permanentDirectory,int rv){
	char com[25];
	char p[25];	
	char argument[255];
	int next;
	pid_t pid;
	int i;
	int pfd[2];

	sscanf(command,"%s",com);
	next=strlen(com)+1;

	if(rv==4)
		strcpy(argument,&command[next]);
	else{
		sscanf(&command[next],"%s",argument);
		next+=strlen(argument)+1;
		sscanf(&command[next],"%s",p);
		next+=strlen(p)+1;
		if(strcmp(com,"pwd")!=0 && strcmp(com,"lsf")!=0){
			strcat(argument," ");
			strcat(argument,p);
		}
	}

	if(strcmp(com,"lsf")==0){
		strcat(argument," ");		
		strcat(argument,currentDirectory);
	}

	if(pipe(pfd)==-1){
		perror("Pipe error:");
		exit(1);
	}

	if((pid=fork())==-1){
		perror("Fork creating error =>");
		exit(1);
	}
	if(pid==0){
		if(close(pfd[0])==-1){
			perror("Close error");
			exit(1);
		}
		if(pfd[1]!=STDOUT_FILENO){
			if(dup2(pfd[1],STDOUT_FILENO)==-1){
				perror("");
				exit(1);
			}
			if(close(pfd[1])==-1){
				perror("Close error");
				exit(1);
			}
		}
		childProcess(com,argument,permanentDirectory);			
		free(permanentDirectory);
		free(currentDirectory);
		free(command);
		exit(0);		
	}

	if(strcmp(com,"pwd")==0 || strcmp(com,"lsf")==0){
		strcpy(com,p);
	}
	else{
		strcpy(com,"");
		strcpy(argument,"");		
		sscanf(&command[next],"%s",com);
		next+=strlen(com)+1;
		if(sscanf(&command[next],"%s",argument)==1)
		next+=strlen(argument)+1;
	}

	if((pid=fork())==-1){
		perror("Fork creating error =>");
		exit(1);
	}
	if(pid==0){
		if(close(pfd[1])==-1){
			perror("Close error");
			exit(1);
		}
		if(pfd[0]!=STDIN_FILENO){
			if(dup2(pfd[0],STDIN_FILENO)==-1){
				perror("");
				exit(1);
			}
			if(close(pfd[0])==-1){
				perror("Close error");
				exit(1);
			}
		}
		if(rv==2)
			childProcess(com,NULL,permanentDirectory);
		else if(rv==3){
			char buff;
			int fd;
			if((fd=open(com,O_WRONLY|O_CREAT|O_TRUNC,MODE))==-1){
				perror("File open error: ");
				exit(1);
			}
			while(read(STDIN_FILENO,&buff,sizeof(char))>0)
				write(fd,&buff,sizeof(char));			
		}
		else if(rv==4){
			char buff;
			while(read(STDIN_FILENO,&buff,sizeof(char))>0)
				printf("%c",buff);			
		}		
		free(permanentDirectory);
		free(currentDirectory);
		free(command);
		exit(0);
	}
	close(pfd[0]);
	close(pfd[1]);
	/*	for paralellism	*/
	for(i=0;i<2;++i)
		wait(NULL);
}

void 
onlyFork(char* command,char* currentDirectory,char* permanentDirectory){

	char com[25];
	char type[50];
	char argument[255];
	int next;
	pid_t pid;
	int i;
	int pfd[2];

	sscanf(command,"%s",com);
	next=strlen(com)+1;
	if(sscanf(&command[next],"%s",argument)==1)
		next+=strlen(argument)+1;

	if(strcmp(com,"bunedu")==0){
		if(sscanf(&command[next],"%s",type)==1){
			next+=strlen(argument)+1;
			strcat(argument," ");
			strcat(argument,type);
		}
	}

	if((pid=fork())==-1){
		perror("Fork creating error =>");
		exit(1);
	}
	if(pid==0){
		if(strcmp(com,"pwd")==0)
			childProcess(com,NULL,permanentDirectory);
		else if(strcmp(com,"lsf")==0)
			childProcess(com,currentDirectory,permanentDirectory);
		else
			childProcess(com,argument,permanentDirectory);
		free(permanentDirectory);
		free(currentDirectory);
		free(command);
		exit(0);
	}
	else{
		if(strcmp(com,"cd")==0)
			cdUtility(currentDirectory,argument);
		else if(strcmp(com,"help")==0)
			helpUtility();
	}
	wait(NULL);
}

void 
childProcess(char* com,char* argument,char* permanentDirectory){
	char* argList[10];
	argList[0]=permanentDirectory;
	argList[1]=argument;
	argList[2]=NULL;	
	if(strcmp(com,"lsf")==0){
		strcat(permanentDirectory,"/lsfcommand");
		if(execv(permanentDirectory,argList)==-1){
			perror("Execv system error => ");
			exit(1);
		}
	}
	else if(strcmp(com,"pwd")==0){
		strcat(permanentDirectory,"/pwdcommand");
		if(execv(permanentDirectory,argList)==-1){
			perror("Execv system error => ");
			exit(1);
		}
	}
	else if(strcmp(com,"cat")==0){
		strcat(permanentDirectory,"/catcommand");
		if(execv(permanentDirectory,argList)==-1){
			perror("Execv system error => ");
			exit(1);
		}
	}
	else if(strcmp(com,"wc")==0){
		strcat(permanentDirectory,"/wccommand");
		if(execv(permanentDirectory,argList)==-1){
			perror("Execv system error => ");
			exit(1);
		}
	}
	else if(strcmp(com,"bunedu")==0){
		strcat(permanentDirectory,"/bunedu");
		if(execv(permanentDirectory,argList)==-1){
			perror("Execv system error => ");
			exit(1);
		}
	}
}


void 
helpUtility(){
	printf("HELP UTILITY FOR USERS\n");
	printf("A LIST OF SUPPORTED UTILITIES IN GTU SHELL\n");
	printf("1) lsf [|,>]						\n");
	printf("2) pwd  [|,>]						\n");
	printf("3) cd [directory]					\n");
	printf("4) help  for supported commands		\n");
	printf("5) cat [filename] [ |,<,>]			\n");
	printf("6) wc [filename] [|,<,>]			\n");
	printf("7) bunedu [-z] [directory]			\n");
	printf("8) !n 								\n");
	printf("9) exit 							\n");							
}

void 
cdUtility(char* currentDirectory,char* argument){
	int i;
	for(i=0;argument[i]==' ' || argument[i]=='\t';++i)	;
	sscanf(&argument[i],"%s",argument);

	if(chdir(argument)==-1)
		perror("");	
}

int 
exitShell(char* command){
	char check[256];
	sscanf(command,"%s",check);
	if(strcmp(check,"exit")==0)
		return 0;
	return 1;
}

void 
leftOneSpaces(char* command){
	int i,j,status=0;
	char* com;	
	if((com=calloc(sizeof(char),256))==NULL){
		perror("System heap error =>");
		exit(1);
	}
	for(i=0,j=0;command[i]!='\0';++i){
		if(command[i]==' ' || command[i]=='\t')
			status++;
		else
			status=0;
		if(status==0 || status==1)
			com[j++]=command[i];
	}
	com[j]='\0';
	strcpy(command,com);
	free(com);
}

int 
commandCondition(char* command){
	char check[256];
	int start;
	int result;

	sscanf(command,"%s",check);
	start=strlen(check)+1;

	if(strcmp(check,"lsf")==0){	
		if(sscanf(&command[start],"%s",check)==1){
			if(strcmp(check,">")==0){
				start+=strlen(check)+1;		
				result=streamCondition(&command[start]);
			}
			else if(strcmp(check,"<")==0){
				start+=strlen(check)+1;		
				result=1+streamCondition(&command[start]);						
			}				
			else if(strcmp(check,"|")==0){
				start+=strlen(check)+1;		
				result=pipeCondition(&command[start]);			
			}			
			else{
				fprintf(stderr,"Syntax error!\n");				
				result=0;
			}
		}
		else
			result=1;
	}
	else if(strcmp(check,"pwd")==0){
		if(sscanf(&command[start],"%s",check)==1){
			if(strcmp(check,">")==0){
				start+=strlen(check)+1;		
				result=streamCondition(&command[start]);
			}
			else if(strcmp(check,"<")==0){
				start+=strlen(check)+1;		
				result=1+streamCondition(&command[start]);					
			}		
			else if(strcmp(check,"|")==0){
				start+=strlen(check)+1;		
				result=pipeCondition(&command[start]);			
			}			
			else{
				fprintf(stderr,"Syntax error!\n");				
				result=0;
			}
		}
		else
			result=1;
	}
	else if(strcmp(check,"help")==0){
		if(sscanf(&command[start],"%s",check)==1){
			if(strcmp(check,">")==0){
				start+=strlen(check)+1;		
				result=streamCondition(&command[start]);
			}
			else{
				fprintf(stderr,"Syntax error!\n");		
				result=0;
			}
		}
		else
			result=1;
	}
	else if(strcmp(check,"cd")==0){
		if(sscanf(&command[start],"%s",check)==1){
			start+=strlen(check)+1;			
			if(strcmp(check,"<")==0 || strcmp(check,">")==0 || strcmp(check,"|")==0){
				fprintf(stderr,"It isn't valid redirection or pipe for cd Command\n");
				result=0;
			}
			else{
				if(sscanf(&command[start],"%s",check)==1){
					if(strcmp(check,"<")==0 || strcmp(check,">")==0 || strcmp(check,"|")==0){
						fprintf(stderr,"It isn't valid redirection or pipe for cd Command\n");
						result=0;
					}
					else 
						result=1;
				}
				else
					result=1;
			}
		}
		else
			result=1;
	}
	else if(strcmp(check,"exit")==0)
		result=1;
	else if(strcmp(check,"cat")==0){
		if(sscanf(&command[start],"%s",check)==1){
			if(strcmp(check,">")==0 || strcmp(check,"|")==0){
				fprintf(stderr,"Syntax error!\n");				
				result=0;
			}
			else if(strcmp(check,"<")==0){
				start+=strlen(check)+1;		
				result=1+streamCondition(&command[start]);				
			}
			else{
				start+=strlen(check)+1;		
				if(sscanf(&command[start],"%s",check)==1){
					if(strcmp(check,">")==0){
						start+=strlen(check)+1;		
						result=streamCondition(&command[start]);
					}
					else if(strcmp(check,"<")==0){
						start+=strlen(check)+1;		
						result=1+streamCondition(&command[start]);						
					}					
					else if(strcmp(check,"|")==0){
						start+=strlen(check)+1;		
						result=pipeCondition(&command[start]);			
					}
					else{
						fprintf(stderr,"Syntax error!\n");				
						result=0;
					}
				}
				else
					result=1;
			}
		}
		else{
			fprintf(stderr,"At least one argument for cat command\n");
			result=0;
		}
	}
	else if(strcmp(check,"wc")==0){
		if(sscanf(&command[start],"%s",check)==1){
			if(strcmp(check,">")==0 || strcmp(check,"|")==0){
				fprintf(stderr,"Syntax error!\n");				
				result=0;
			}
			else if(strcmp(check,"<")==0){
				start+=strlen(check)+1;		
				result=1+streamCondition(&command[start]);				
			}
			else{
				start+=strlen(check)+1;		
				if(sscanf(&command[start],"%s",check)==1){
					if(strcmp(check,">")==0){
						start+=strlen(check)+1;		
						result=streamCondition(&command[start]);
					}
					else if(strcmp(check,"<")==0){
						start+=strlen(check)+1;		
						result=1+streamCondition(&command[start]);						
					}
					else if(strcmp(check,"|")==0){
						start+=strlen(check)+1;		
						result=pipeCondition(&command[start]);		
					}
					else{
						fprintf(stderr,"Syntax error!\n");				
						result=0;
					}
				}
				else
					result=1;
			}
		}
		else{
			fprintf(stderr,"At least one argument for wc command\n");
			result=0;
		}
	}
	else if(strcmp(check,"bunedu")==0){
		if(sscanf(&command[start],"%s",check)==1){
			if(strcmp(check,">")==0 || strcmp(check,"|")==0){
				fprintf(stderr,"Syntax error!\n");				
				result=0;
			}
			else if(strcmp(check,"<")==0){
				start+=strlen(check)+1;		
				result=1+streamCondition(&command[start]);				
			}
			else{
				start+=strlen(check)+1;		
				if(sscanf(&command[start],"%s",check)==1){
					if(strcmp(check,">")==0 || strcmp(check,"<")==0){
						start+=strlen(check)+1;		
						result=streamCondition(&command[start]);
					}
					else if(strcmp(check,"|")==0){
						start+=strlen(check)+1;		
						result=pipeCondition(&command[start]);		
					}
					else{		
						result=1;
					}
				}
				else
					result=1;
			}
		}
		else{
			fprintf(stderr,"At least one argument for bunedu command\n");
			result=0;
		}
	}
	else{
		printf("%s: komut bulunamadı.\n",check);
		result=0;
	}

	return result;
}

int 
pipeCondition(char* command){
	char check[256];
	int start=0;
	int result;

	if(sscanf(&command[start],"%s",check)==1){
		start+=strlen(check)+1;		
		if(strcmp(check,">")==0 || strcmp(check,"<")==0 || strcmp(check,"|")==0){
			fprintf(stderr,"Syntax error!\n");
			result=0;
		}
		else{
			if(pipeCommand(check)==1)
				result=2;
			else{
				fprintf(stderr,"This command is invalid for input pipe.Pipe can't be created\n");
				result=0;
			}
			if(sscanf(&command[start],"%s",check)==1){
				if(strcmp(check,"<")==0 || strcmp(check,">")==0)
					printf("A pipe or a redirection is valid for this shell.\n");					
				else if(strcmp(check,"|")==0)
					printf("Only one pipe is valid for this shell.\n");
				fprintf(stderr,"Syntax error!\n");								
				result=0;
			}
		}
	}
	else{
		fprintf(stderr,"Syntax error!\n");	
		result=0;
	}

	return result;
}

int 
streamCondition(char* command){
	char check[256];
	int start=0;
	int result;

	if(sscanf(command,"%s",check)==1){
		start+=strlen(check)+1;
		if(strcmp(check,"<")==0 || strcmp(check,">")==0 || strcmp(check,"|")==0){
			fprintf(stderr,"Syntax error!\n");
			result=0;
		}
		else{
			if(sscanf(&command[start],"%s",check)==1){
				if(strcmp(check,"<")==0 || strcmp(check,">")==0)
					printf("Only one < or > redirection is valid for this shell.\n");
				else if(strcmp(check,"|")==0)
					printf("A pipe or a redirection is valid for this shell.\n");
				fprintf(stderr,"Syntax error!\n");
				result=0;
			}
			else
				result=3;
		}
	}
	else{
		fprintf(stderr,"Syntax error!\n");
		result=0;
	}
	return result;
}

int 
pipeCommand(char* command){
	if(strcmp(command,"wc")==0)
		return 1;
	else if(strcmp(command,"bunedu")==0)
		return 1;
	else if(strcmp(command,"cat")==0)
		return 1;
	else return 0;
}
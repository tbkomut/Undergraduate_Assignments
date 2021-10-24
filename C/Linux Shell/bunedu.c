#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int postOrderApply (char* path,int pathfun(char *path1));
int sizepathfun (char* path);
int isDirectory(char *path);

char parameter[]="-z";

int 
main(int argc,char* argv[]){
	char arg1[255];
	char arg2[255];
	int n;
	printf("%s\n",argv[1]);	
	n=sscanf(argv[1],"%s%s",arg1,arg2);
	if(n==1){
		strcpy(parameter,"");
		postOrderApply(arg1,sizepathfun);
	}
	else{
		postOrderApply(arg2,sizepathfun);		
	}
	return 0;
}

int 
sizepathfun (char * path){
	struct stat buff;
	if(lstat(path,&buff)==-1){
		perror("System error 6 = ");
		exit(1);
	}
	if(S_ISREG(buff.st_mode)){
		return buff.st_size;
	}
	else
		return -1;
}

int 
postOrderApply (char* path,int pathfun(char *path1)){
	DIR* direct;
	struct dirent* dir;
	char* workingPath;
	char* shortPath;
	char* holdPath;	
	int strSize=strlen(path);
	int result=0;
	/*
	 	I suppose that a directory name must be max. 200 chars.Otherwise 
		Program will be get error. 
	*/
	if((workingPath=calloc(sizeof(char),strSize+200))==NULL){
		perror("System error 1= ");
		exit(1);
	}
	/* 
		Arguman directory is set up with these lines.
	 	Maybe memory leak because of '\0'. It is tested, no problem...			
	*/
	if(getcwd(workingPath,strSize+200)==NULL){
		perror("System error 2= ");
		free(workingPath);
		exit(1);
	}
	if((shortPath=calloc(sizeof(char),strSize+200))==NULL){
		perror("System error 3= ");
		exit(1);
	}

	/*	strcpy(shortPath,"/");	*/
	strcat(shortPath,path);
	/*	Then workingPath=workingPath+shortPath	*/	
	strcat(workingPath,"/");
	strcat(workingPath,shortPath);

	/* 	Current directory processes in here. */
	/*	printf("%s\n",workingPath);	*/

	/*	This value is stored by a temp variable...	*/	
	if((holdPath=calloc(sizeof(char),strSize+200))==NULL){
		perror("System error 4= ");
		exit(1);
	}
	strcpy(holdPath,workingPath);

	if((direct=opendir(workingPath))==NULL){
		printf("Directory is not exit\n");
		free(workingPath);
		free(shortPath);
		free(holdPath);
		exit(1);
	}
	while((dir=readdir(direct))!=NULL){
		if(strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
			strcat(workingPath,"/");
			strcat(workingPath,dir->d_name);		
			if(isDirectory(workingPath)!=0){
				strcpy(shortPath,path);
				strcat(shortPath,"/");
				strcat(shortPath,dir->d_name);
				if(strcmp(parameter,"-z")==0)			
					result+=postOrderApply(shortPath,pathfun);
				else
					postOrderApply(shortPath,pathfun);
				strcpy(workingPath,holdPath);	
			}
			else{
				int handle=(pathfun)(workingPath);
				if(handle==-1){
					printf("Special file %s\n",dir->d_name);
					handle=0;
				}
				else{
					if(strcmp(parameter,"-z")==0)
						result+=handle;
					else
						result+=handle;
				}
				strcpy(workingPath,holdPath);
			}			
		}
	}
	if(strcmp(parameter,"-z")==0)
		printf("%d\t%s\n",result/1024,path);
	else{
		result=result/1024;
		printf("%d\t%s\n",result,path);
	}
	if(closedir(direct)==-1){
		perror("System error 5= ");
		free(workingPath);
		free(shortPath);
		free(holdPath);		
		exit(1);
	}
	free(workingPath);
	free(shortPath);
	free(holdPath);

	return result;
}

int 
isDirectory(char *path){
	struct stat statbuf;
	if (stat(path, &statbuf) == -1)
		return 0;
	else
		return S_ISDIR(statbuf.st_mode);
}
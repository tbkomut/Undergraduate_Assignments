/*_______________________________Part 2_________________________________*/
/*______________________________________________________________________*/
/*__________________HW06_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 25/04/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*_____________This program gets the line string from user______________*/ 
/*____It examines the words in the string separately and lists them_____*/ 
/*________The user gets a string until the "end" word is passed_________*/
/*______________________________________________________________________*/

/*_______________________________Includes_______________________________*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h> 

/*_____________________________Definitions______________________________*/
#define MAX_NUM_WORDS	500
#define WORD_LENGTH	50

/*	Functions	*/
int getAndFilterWord(char * w);
void addWord(char * w, char words[][WORD_LENGTH],int occur[], int *word_count);
void sortWords(char words[][WORD_LENGTH], int occur[],int word_count);
void myTest();

/*	Helper Functions	*/
int getLine(char str[][50],int* size);

int 
main(){

	myTest();

	return 0;
}

void 
myTest(){

	char w[WORD_LENGTH];
	char words[MAX_NUM_WORDS][WORD_LENGTH];
	int occur[MAX_NUM_WORDS];
	int word_count;
	int first,second;	/*	These variables keeps the number of words before 
						the line and the number of words after the line.	*/
	int i,size;
	int result=0;

	word_count=0;
	size=0;

	do{
		first=size;
		getLine(&words[0],&size);
		second=size;
		for(i=0;i<(second-first) && result==0;i++){
			strcpy(w,words[first+i]);
			if(getAndFilterWord(w)==1){
				if(strcmp(w,"end")==0){
					result=1;
				}
				else{
					printf("w=%s	",w);
					addWord(w,words,occur,&word_count);
				}
			}
			else{
				printf("w=%s\n",w);
			}	
		}	
	}while(result==0);
	sortWords(words,occur,word_count);	
	
}

/*	This function takes a line string. 	*/
int
getLine(char str[][50],int *size){

	int i;
	char ch;
	char temp[50];

	for(i=0;ch!='\n';i++){
		ch=getchar();
		if(ch==' ' || ch=='\t'){
			temp[i]='\0';
			i=-1;
			if(strlen(temp)!=0){
				strcpy(str[*size],temp);
				*size+=1;
			}
			strcpy(temp," ");				
		}
		else if(ch=='\n'){
			temp[i]='\0';			
			if(strlen(temp)!=0){
				strcpy(str[*size],temp);
				*size+=1;
			}
			else{
				strcpy(str[*size],temp);
				*size+=1;
			}			
		}
		else{
			temp[i]=ch;				
		}

	}

	return 0;
}

/*	This function removes characters that are not letters in the word.	*/
int 
getAndFilterWord(char * w){

	int i,j;
	int result;
	char temp[WORD_LENGTH];

	result=1;

	for(i=0,j=0;w[i]!='\0';i++){
		if((w[i]>='a' && w[i]<='z'))
			temp[j++]=w[i];
		else if((w[i]>='A' && w[i]<='Z'))
			temp[j++]=w[i]+('a'-'A');
	}

	temp[j]='\0';	
	strcpy(w,temp);
	w[strlen(temp)]='\0';

	if(strlen(w)==0){
		result=0;
	}

	return result;
}

/*	The filtered words are assigned to the total word string.	*/
void 
addWord(char *w,char words[][WORD_LENGTH],int occur[],int *word_count){

	int i;
	int same;

	same=0;

	for(i=0;i<*word_count && same==0;i++){
		if(strcmp(words[i],w)==0){
			same=1;
		}
	}

	if(same==1){
		occur[i-1]+=1;
		printf("occur[%d]=%d	",i-1,occur[i-1]);
		printf("word_count=%d\n",*word_count);
	}
	else{
		strcpy(words[*word_count],w);
		occur[*word_count]=1;
		printf("word[%d]=%s		",*word_count,words[*word_count]);
		printf("occur[%d]=%d	",*word_count,occur[*word_count]);
		printf("word_count=%d\n",*word_count);
		*word_count=*word_count+1;
	}

}

/* If there is more than which word,It placed to the first elements of arrays */
void 
sortWords(char words[][WORD_LENGTH], int occur[],int word_count){

	int i,j;
	int temp,max;
	char str[WORD_LENGTH];

	/*	Selection Sort Algorithm	*/
	for(i=0;i<word_count;i++){
		max=i;
		for(j=i;j<word_count;j++){
			if(occur[max]<occur[j]){
				max=j;
			}
		}
		temp=occur[i];
		occur[i]=occur[max];
		occur[max]=temp;
		strcpy(str,words[i]);
		strcpy(words[i],words[max]);
		strcpy(words[max],str);
	}

	for(i=0;i<word_count;i++){
		printf("words[%d]=%s	",i,words[i]);
		printf("occur[%d]=%d\n",i,occur[i]);
	}

}

/*----------------------------------------------------------------------*/
/*				End of HW06_TaipBayram_Komut_131044010_part2.c			*/
/*----------------------------------------------------------------------*/

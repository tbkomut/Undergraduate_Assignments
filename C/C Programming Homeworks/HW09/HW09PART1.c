/*_______________________________Part 1_________________________________*/
/*______________________________________________________________________*/
/*__________________HW09_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 21/05/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*____It reads person and record information from the input.txt file____*/
/*_________We used linked list algorithm for records information________*/
/*______________These information is kept in struct pointer_____________*/
/*________In fact,Records information are in the person structure_______*/
/*_We written in a binary file,finally read information from these file_*/
/*______________________________________________________________________*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAMELEN 50
#define MAXRECORD 500

typedef struct record_s {
    int id;
    char number[NAMELEN];
    struct record_s *next;
} Record;

typedef struct person_s {
    int id;
    char name[NAMELEN];
    double expenditure;
    Record *numbers;
} Person;

typedef struct people_s {
    Person data[MAXRECORD];
    int size;
} People;

/*  Linked list is created in this  function  */
void 
createList(People *people,int line,char *str){

	people->data[line].numbers=NULL;

	people->data[line].numbers=malloc(sizeof(Record));	
	people->data[line].numbers->id=people->data[line].id;
	strcpy(people->data[line].numbers->number,str);
	people->data[line].numbers->next=NULL;

}
/*  Add the new element to linked list */
void 
addList(Record* list,People *people,int line,char* str){
	
	Record *current=list;

	while(current->next!=NULL){
		current=current->next;
	}

	current->next=malloc(sizeof(Record));
	current->next->id=people->data[line].id;
	strcpy(current->next->number,str);
	current->next->next=NULL;

}
/*  Write People.data array to the filename */
void 
writePeople(People people, char* filename){

	FILE *fptr;
	int count=0;
	
	if((fptr=fopen(filename,"wb"))!=NULL){
		while(count<people.size){
			fwrite(&people.data[count],sizeof(Person),1,fptr);
			count++;
		}
		fclose(fptr);
	}

}
/*  Reads Person structs from file and places them to People.data array    */
/*  Note that the number of Person structs in the file is unkown   */
void 
readPeople(People *people, char* filename){

	FILE *fptr;

	people->size=0;
	if((fptr=fopen(filename,"rb"))!=NULL){
		while(fread(&people->data[people->size],sizeof(Person),1,fptr)>0){
			people->size++;
		}
		fclose(fptr);
	}

}
/*  Calculates the expected expenditure for the person with unknown expenditure */
/*  Persons' expenditure is -1 if their expenditure is unknown  */
/*  You should calculate average bill amount for a phone number and */
/*  multiply it by the phone number count for the person   */
void 
imputation(People *people){

    int i;
	double total=0;
	double average;
	int count=0;
	Record* current;

	for(i=0;i<people->size;i++){
		if(people->data[i].expenditure!=-1){
			total+=people->data[i].expenditure;
			current=people->data[i].numbers;
			while(current!=NULL){
				current=current->next;
				count++;
			}
		}
	}

	average=(total/count);

	count=0;
	for(i=0;i<people->size;i++){
		if(people->data[i].expenditure==-1){
			current=people->data[i].numbers;
			while(current!=NULL){
				current=current->next;
				count++;
			}
			people->data[i].expenditure=count*average;		
		}		
	}

}
/*  Reads the input file and constructs People struct  */
/*  Note that the number of phone numbers in file is unknown unlike your    */
/*  previous homework. You should keep phone numbers in the linked list */
/*  (numbers field) */
void 
read(char* filename, People *people){

	FILE *fptr;
	int status=1;
	char ch;
	int count=0;
	int create=0;	
	char temp[NAMELEN];
	Record *head;
	int length;

	if((fptr=fopen(filename,"r"))!=NULL){
		while(status!=0){
			if(count==0){
				fscanf(fptr,"%d",&people->data[people->size].id);
				fscanf(fptr,"%s",people->data[people->size].name);	
				length=strlen(people->data[people->size].name);
				people->data[people->size].name[length]=' ';
				fscanf(fptr,"%s",&people->data[people->size].name[length+1]);
				fscanf(fptr,"%lf",&people->data[people->size].expenditure);
			}
			else{
				fscanf(fptr,"%s",temp);
				if(create==0){	
					createList(people,people->size,temp);	
					head=people->data[people->size].numbers;
				}
				else{
					addList(head,people,people->size,temp);
				}	
				create++;
			}
			ch=fgetc(fptr);
			count++;
			if(ch=='\n'){
				create=0;
				people->size++;
				count=0;
			}
			else if(ch==-1){
				status=0;			
			}	
		}
		fclose(fptr);
	}
}

void print(People people) {
    int i,found = 0;
    Record *rec;
    /* header */
    printf("%-5s %-30s %-20s %-20s\n", "ID","NAME","EXPENDITURE","NUMBER(s)");
    /* line */
    for (i = 0; i < 78; ++i)
        printf("-");
    printf("\n");

    for (i = 0; i < people.size; ++i) {
        found = 0;
        printf("%-5d %-30s %-20.4f", people.data[i].id, people.data[i].name, people.data[i].expenditure);
        rec = people.data[i].numbers;
        while(rec) {
            if(found)
                printf("%57s", "");
            else
                found = 1;
            printf("%-20s\n", rec->number);
            rec = rec->next;
        }
        printf("\n");
    }
}

int isPeopleEq(People ppl1, People ppl2) {
    Record *rec1,*rec2;
    int i,found = 0;
    int p1size = 0, p2size = 0;
    if(ppl1.size != ppl2.size)
        return 0;
    for (i = 0; i < ppl1.size; ++i)
        if(strcmp(ppl1.data[i].name,ppl2.data[i].name))
            return 0;
        if(ppl1.data[i].id != ppl2.data[i].id)
            return 0;

        p1size = p2size = 0;
        rec1 = ppl1.data[i].numbers;
        while(rec1) {
            ++p1size;
            rec1 = rec1->next;
        }

        rec2 = ppl2.data[i].numbers;
        while(rec2) {
            ++p2size;
            rec2 = rec2->next;
        }

        if(p1size != p2size) {
            return 0;
        }

        rec1 = ppl1.data[i].numbers;
        while(rec1) {
            rec2 = ppl2.data[i].numbers;
            found = 0;
            while(!found && rec2) {
                if(strcmp(rec1->number,rec2->number) == 0) {
                    found = 1;
                    break;
                }
                rec2 = rec2->next;
            }
            if(!found) {
                return 0;
            }
            rec1 = rec1->next;
        }
    return 1;
}

int main(int argc, char** argv) {
    People people1,people2;
    people1.size = 0;
    read(argv[1],&people1);
    print(people1);
    writePeople(people1,"people.bin");
    readPeople(&people2,"people.bin");
    print(people2);
    printf("%s\n", isPeopleEq(people1,people2) ? "PEOPLE ARE SAME" : "PEOPLE ARE DIFFERENT!");
    printf("Making imputation\n");
    imputation(&people1);
    print(people1);
    return 0;
}
/*----------------------------------------------------------------------*/
/*				End of HW09_TaipBayram_Komut_131044010_part1.c			*/
/*----------------------------------------------------------------------*/

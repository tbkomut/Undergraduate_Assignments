/*_______________________________Part 1_________________________________*/
/*______________________________________________________________________*/
/*__________________HW08_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 14/05/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*____It reads person and record information from the input.txt file____*/
/*___Then It places this information into the corresponding structure___*/
/*___Then It assign the information in these two separate structures____*/
/*___________________to two separate binary files_______________________*/
/*_______Finally, we read the information in these binary files_________*/
/*______________________________________________________________________*/

/*________________________________Includes______________________________*/

#include <stdio.h>
#include <string.h>

/*______________________________Definitions_____________________________*/

#define NAMELEN 50
#define MAXRECORD 500

/*___________________________Typedef Structures_________________________*/

typedef struct person_s {
	int id;
	char name[NAMELEN];
} Person;

typedef struct record_s {
	int id;
	char number[NAMELEN];	
} Record;

typedef struct Records_s {
	Record data[MAXRECORD];
	int size;	
} Records;

typedef struct people_s {
	Person data[MAXRECORD];
	int size;				
} People;

/*___Write Records.data array to the filename___*/
/*___Note that file should be binary___*/
void 
writeRecords(Records records, char* filename) {

	FILE *fptr;
	int count;
	
	if((fptr=fopen(filename,"wb"))!=NULL){
		count=0;
		while(count<records.size){
			fwrite(&records.data[count],sizeof(Record),1,fptr);
			count++;
		}
		fclose(fptr);
	}

}

/*___Reads Record structs from the binary file___*/ 
/*___and places them to Records.data array___*/
/*___Note that the number of Record structs in the file is unkown___*/
void 
readRecords(Records *records, char* filename){

	FILE *fptr;

	if((fptr=fopen(filename,"rb"))!=NULL){
		records->size=0;	
		while(fread(&records->data[records->size++],sizeof(Record),1,fptr)>0) ;
		fclose(fptr);
	}
	records->size--;
	
}

/*___Write People.data array to the filename___*/
/*___Note that file should be binary___*/
void 
writePeople(People people, char* filename){
	
	FILE *fptr;
	int count;

	if((fptr=fopen(filename,"wb"))!=NULL){
		count=0;
		while(count<people.size){
			fwrite(&people.data[count],sizeof(Person),1,fptr);
			count++;
		}
		fclose(fptr);
	}

}

/*___Reads Person structs from the binary file___*/ 
/*___and places them to People.data array___*/
/*___Note that the number of Person structs in the file is unkown___*/
void 
readPeople(People *people, char* filename){
	
	FILE *fptr;

	if((fptr=fopen(filename,"rb"))!=NULL){
		while(fread(&people->data[people->size++],sizeof(Person),1,fptr)) ;
		fclose(fptr);
	}
	people->size--;

}

/*___Reads the input file and constructs People and Records structs___*/
/*___Note that each Record in Records is unique___*/

void 
read(char* filename, People *people, Records *records){

	FILE *fptr;	
	int count;
	int total,status;
	int useage;
	int control;
	int surname;
	char num[NAMELEN];

	if((fptr=fopen(filename,"r"))!=NULL){
		status=EOF+1;
		while(status!=EOF){
			status=fscanf(fptr,"%d%s"	,&people->data[people->size].id
										,people->data[people->size].name);
			surname=strlen(people->data[people->size].name);
			people->data[people->size].name[surname]=' ';
			fscanf(fptr,"%s%d"	,&people->data[people->size].name[surname+1]
								,&total);
			if(status!=EOF){
				count=0;
				while(count<total){
					control=0;
					useage=1;
					fscanf(fptr,"%s",num);
					while(control<records->size){
						if(strcmp(num,records->data[control++].number)==0)
						useage=0;
					}
					if(useage==1){
						/*_Same records will be canceled if they pass again_*/
						records->data[records->size].id=people->data[people->size].id;
						strcpy(records->data[records->size].number,num);
						records->size++;
					}
					count++;
					strcpy(num," ");
				}
				people->size++;
			}
		}
		fclose(fptr);
	}

}


void print(People people, Records records) {
	int i,j,found = 0;
	/* header */
	printf("%-5s %-30s %-20s\n", "ID","NAME","NUMBER(s)");
	/* line */
	for (i = 0; i < 57; ++i)
		printf("-");
	printf("\n");
	for (i = 0; i < people.size; ++i) {
		found = 0;
		printf("%-5d %-30s", people.data[i].id, people.data[i].name);
		for (j = 0; j < records.size; ++j) {
			if(records.data[j].id == people.data[i].id) {
				if(found)
					printf("%36s", "");
				printf("%-20s\n", records.data[j].number);
				found = 1;
			}
		}
		printf("\n");
	}
}

int 
isPeopleEq(People ppl1, People ppl2) {
	int i;
	if(ppl1.size != ppl2.size)
		return 0;
	for (i = 0; i < ppl1.size; ++i)
		if(strcmp(ppl1.data[i].name,ppl2.data[i].name) ||
			ppl1.data[i].id != ppl2.data[i].id)
			return 0;
	return 1;
}

int 
isRecordsEq(Records rec1, Records rec2) {
	int i;
	if(rec1.size != rec2.size)
		return 0;
	for (i = 0; i < rec1.size; ++i)
		if(strcmp(rec1.data[i].number,rec2.data[i].number) ||
			rec1.data[i].id != rec2.data[i].id)
			return 0;
	return 1;
}

int 
main(int argc, char** argv) {
	People people1,people2;
	Records records1,records2;
	people1.size = 0;
	records1.size = 0;
	read(argv[1],&people1, &records1);
	print(people1, records1);
	writePeople(people1,"people.bin");
	writeRecords(records1,"records.bin");
	readRecords(&records2,"records.bin");
	readPeople(&people2,"people.bin");
	print(people2, records2);
	printf("%s\n", isRecordsEq(records1,records2) ? "RECORDS ARE SAME" : "RECORDS ARE DIFFERENT!");
	printf("%s\n", isPeopleEq(people1,people2) ? "PEOPLE ARE SAME" : "PEOPLE ARE DIFFERENT!");
	return 0;
}	

/*----------------------------------------------------------------------*/
/*				End of HW08_TaipBayram_Komut_131044010_part1.c			*/
/*----------------------------------------------------------------------*/

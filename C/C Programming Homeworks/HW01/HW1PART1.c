/*_______________________________Part 1_________________________________*/
/*______________________________________________________________________*/
/*__________________HW01_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 03/03/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*________The program that takes a user's date of birth information_____*/ 
/*_____________and calculates the number of days left birthday__________*/ 
/*______________and his or her age according to today's date____________*/
/*______________________________________________________________________*/

/*_______________________________Includes_______________________________*/

#include<stdio.h>

/*______________________________Definitions_____________________________*/

#define TAKE_YEAR  365
#define TAKE_MONTH  30

/*_________________________Function Prototypes__________________________*/


int theAge(int day,int month,int year,int today,int this_month,int this_year);
int daysLeft(int day,int month, int today,int this_month);

int main(){

	int day,month,year;
	int today,this_month,this_year;

	printf("Please enter the your birthday as day,month and year:\n");
	scanf("%d%d%d",&day,&month,&year);
	printf("Please enter the today as day,month and year:\n");
	scanf("%d%d%d",&today,&this_month,&this_year);

	theAge(day,month,year,today,this_month,this_year);
	daysLeft(day,month,today,this_month);

	return 0;
}

int 
theAge(int day,int month,int year,int today,int this_month,int this_year){

	int result;

	result=((this_year-year)*TAKE_YEAR)+((this_month-month)*TAKE_MONTH)+
	(today-day);
	
	result=(result/TAKE_YEAR);

	printf("Your age is %d.\n",result);

	return result;

}

int daysLeft(int day,int month, int today,int this_month){

	int result;

	result=((month-this_month)*TAKE_MONTH)+(day-today);

	result=(result+TAKE_YEAR)%TAKE_YEAR;

	printf("%d\n",result);
	
	return result;
}

/*----------------------------------------------------------------------*/
/*			 End of HW01_TaipBayram_Komut_131044010_part1.c			  	*/
/*----------------------------------------------------------------------*/

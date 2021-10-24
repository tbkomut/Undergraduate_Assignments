/*_______________________________Part 3_________________________________*/
/*______________________________________________________________________*/
/*__________________HW03_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 19/03/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*_____Program that calculates remaining balance and monthly usage______*/ 
/*______________in a travel card (IstanbulCard) automation______________*/
/*______________________________________________________________________*/

/*_______________________________Includes_______________________________*/

#include<stdio.h>
#define NORMAL_C	2.30
#define	STUDENT_C	1.15
#define TEACHER_C	1.65

/*_________________________Function Prototypes__________________________*/

int charge(int cardType, int* monthlyUse, double* balance);

int 
main(){

	int cardType;
	int monthlyUse;
	double balance;
	int state;	

	scanf("%d",&cardType);
	scanf("%d",&monthlyUse);
	scanf("%lf",&balance);

	state=charge(cardType,&monthlyUse,&balance);

	if(state==0){
		printf("Succes!\n");
		printf("balance:%.2f monthly use:%d\n",balance,monthlyUse);
	}
	else if(state==-1){
		printf("Insufficient balance or	monthly	use!\n");
		printf("balance:%.2f monthly use:%d\n",balance,monthlyUse);
	}
	else if(state==-2){
		printf("Invalid card type!\n");
	}

	return 0;

}

int 
charge(int cardType, int* monthlyUse, double* balance){

	double condition;
	double result;

	result=0;

	switch(cardType){
		case 1:	
			condition=NORMAL_C;
			break;
		case 2:	
			condition=STUDENT_C;
			break;
		case 3:	
			condition=TEACHER_C;
			break;
		default:
			result=-2;
	}
	
	if(result!=-2){

		if(*monthlyUse>0){
			*monthlyUse=*monthlyUse-1;
		}
		else{
			if(*balance>=condition){
				*balance=*balance-condition;	
			}
			else
				result=-1;
		}

	}	

	return result;

}

/*----------------------------------------------------------------------*/
/*			 End of HW03_TaipBayram_Komut_131044010_part3.c			  	*/
/*----------------------------------------------------------------------*/

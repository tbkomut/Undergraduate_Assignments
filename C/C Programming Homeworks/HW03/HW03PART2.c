/*_______________________________Part 2_________________________________*/
/*______________________________________________________________________*/
/*__________________HW03_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 19/03/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*____Program that calculates the amount of Turkish Liras in coins______*/
/*______________________________________________________________________*/

/*_______________________________Includes_______________________________*/

#include<stdio.h>
#define DOUBLE_CAST 1000

/*_________________________Function Prototypes__________________________*/

int dispenseChange(double paid,double due,int *tl1,int *krs50,int *krs25,int *krs10,int *krs5,int *krs1);

int 
main(){

	double paid,due;
	int tl1,krs50,krs25,krs10,krs5,krs1;


	scanf("%lf",&paid);
	scanf("%lf",&due);

	printf("Return Function-->%d\n",dispenseChange(paid,due,&tl1,&krs50,&krs25,&krs10,&krs5,&krs1));

	printf("1TL=%d\n50KRS=%d\n25KRS=%d\n10KRS=%d\n5KRS=%d\n1KRS=%d\n",tl1,krs50,krs25,krs10,krs5,krs1);

	return 0;
}

int 
dispenseChange(double paid,double due,int *tl1,int *krs50,int *krs25,int *krs10,int *krs5,int *krs1){

	int result;
	double kalan;
	int temp;

	result=-1;

	if((paid*DOUBLE_CAST)<(due*DOUBLE_CAST))
		result=0;
	else if(paid*DOUBLE_CAST<0 || due*DOUBLE_CAST<0)
		result=0;
	else{

		kalan=paid-due;
		temp=kalan*DOUBLE_CAST;

	/*//////////*/
			*tl1=temp/DOUBLE_CAST;
			temp=temp%1000;
	/*//////////*/
			*krs50=temp/500;
			temp=temp%500;

	/*//////////*/
			*krs25=(temp/250);
			temp=temp%250;

	/*//////////*/
			*krs10=(temp/100);
			temp=temp%100;

	/*//////////*/
			*krs5=(temp/50);
			temp=temp%50;

	/*//////////*/
			*krs1=(temp/9);
			temp=temp%10;	

	}

	return result;
}

/*----------------------------------------------------------------------*/
/*			 End of HW03_TaipBayram_Komut_131044010_part2.c			  	*/
/*----------------------------------------------------------------------*/

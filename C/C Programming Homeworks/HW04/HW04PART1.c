/*_______________________________Part 1_________________________________*/
/*______________________________________________________________________*/
/*__________________HW04_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 26/03/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*_____________This program adds elements to the given array____________*/ 
/*____according to the padding type and padding width of a the array____*/
/*____________The elements are added to the end of the array____________*/ 
/*___________________and to the beginning of the array__________________*/
/*___________The output array must have a maximum size of 255___________*/
/*______________________________________________________________________*/

/*_______________________________Includes_______________________________*/

#include<stdio.h>

/*_________________________Function Prototypes__________________________*/

void addPadding(double inputArr[], int inputArraySize, double outputArr[], int
*outputArraySize, int paddingWidth, void paddingMethod(double[], int, int));
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);

int main(){

	double inputArr[]= {5, 6, 7, 8, 9};
	double outputArr[255];
	int outputArrSize = 0;
	int i;

	addPadding(inputArr, 5 , outputArr, &outputArrSize, 4, samePadding);

	printf("[");
	for(i=0;i<outputArrSize;i++)
		printf(" %.1f ",outputArr[i]);
	printf("]\n");

	return 0;
}


void 
addPadding(double inputArr[],int inputArraySize,double outputArr[],int
*outputArraySize,int paddingWidth,void paddingMethod(double[],int,int)){

	int i;

	if((inputArraySize+(2*paddingWidth))>255){
		printf("Warning! The maximum number of outputs is 255.\n");
	}	
	else{
		*outputArraySize=inputArraySize+(2*paddingWidth);
		for(i=0;i<(*outputArraySize);i++){
			if(i>=paddingWidth && i<inputArraySize+paddingWidth)
			outputArr[i]=inputArr[i-paddingWidth];
		}

		paddingMethod(outputArr,*outputArraySize,paddingWidth);
	}
}

void 
zeroPadding(double outputArr[], int outputArraySize, int paddingWidth){

	int i;

	for(i=0;i<outputArraySize;i++){
		if(i<paddingWidth || i>=outputArraySize+paddingWidth)
		outputArr[i]=0;
	}

}

void 
samePadding(double outputArr[], int outputArraySize, int paddingWidth){

	int i;
	double first;
	double last;
	
	first=outputArr[0+paddingWidth];
	last=outputArr[outputArraySize-paddingWidth-1];
	
	for(i=0;i<outputArraySize;i++){
		if(i<paddingWidth)
		outputArr[i]=first;	
		else if(i>=outputArraySize-paddingWidth)
		outputArr[i]=last;	
	}

}

void 
halfPadding(double outputArr[], int outputArraySize, int paddingWidth){


	int i;
	double first;
	double last;
	
	first=(outputArr[0+paddingWidth]/2.00);
	last=(outputArr[outputArraySize-paddingWidth-1]/2.00);
	
	for(i=0;i<outputArraySize;i++){
		if(i<paddingWidth)
		outputArr[i]=first;	
		else if(i>=outputArraySize-paddingWidth)
		outputArr[i]=last;	
	}

}

/*----------------------------------------------------------------------*/
/*			 End of HW04_TaipBayram_Komut_131044010_part1.c			  	*/
/*----------------------------------------------------------------------*/

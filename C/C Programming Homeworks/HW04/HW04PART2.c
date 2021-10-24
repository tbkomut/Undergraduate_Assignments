/*_______________________________Part 2_________________________________*/
/*______________________________________________________________________*/
/*__________________HW04_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 26/03/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*______The program make a convolution operation over a given array_____*/ 
/*______This operation has two components: input array,kernel array_____*/
/*___________There is a relationship between these two arrays___________*/
/*___________________First, InputArray is made padding__________________*/
/*____After kernel array will be moved stride size on the input array___*/
/*_________________Operations are performed at each step________________*/
/*_________________Then Output Array is assigned values_________________*/
/*______________________________________________________________________*/

/*_______________________________Includes_______________________________*/

#include<stdio.h>

/*_______________________Typedef Enum Structure_________________________*/

typedef enum _paddingType{ZERO, HALF, SAME}PaddingType;

/*_________________________Function Prototypes__________________________*/

int convolution(double inputArr[],int inputArraySize,
				double kernelArr[],int kernelArraySize,
				double outputArr[],int *outputArraySize,
				int stride, PaddingType padding);
void addPadding(double inputArr[], int inputArraySize, double outputArr[], int
*outputArraySize, int paddingWidth, void paddingMethod(double[], int, int));
void zeroPadding(double outputArr[], int outputArraySize, int paddingWidth);
void samePadding(double outputArr[], int outputArraySize, int paddingWidth);
void halfPadding(double outputArr[], int outputArraySize, int paddingWidth);

int main(){

	double inputArr []={1, 3, 5, 7, 9, 11, 13};
	double kernelArr []={2, 4, 6};
	double outputArr[255];
	int outputArrSize = 0;
	int i;

	convolution(inputArr, 7, kernelArr, 3, outputArr, &outputArrSize, 2, ZERO);

	printf("[");
	for(i=0;i<outputArrSize;i++){
		printf(" %.1f ",outputArr[i]);	
	}
	printf("]\n");

	return 0;
}

int 
convolution(double inputArr[],int inputArraySize,
				double kernelArr[],int kernelArraySize,
				double outputArr[],int *outputArraySize,
				int stride,PaddingType paddingMethod){

	double tempArr[256];
	int tempArraySize;
	int i,j,k;
	int result;
	int paddingWidth;
	double total;

	result=0;

	if(kernelArraySize>inputArraySize){
		 result=-1;
	}
	else if(kernelArraySize<=0 || stride<=0){
		 result=-1;
	}

	else{

		paddingWidth=(kernelArraySize-1)/2;
		tempArraySize=inputArraySize;

		if(paddingMethod==ZERO){
			addPadding(inputArr,inputArraySize,tempArr,&tempArraySize,
						paddingWidth,zeroPadding);
		}
		else if(paddingMethod==SAME){
			addPadding(inputArr,inputArraySize,tempArr,&tempArraySize,
						paddingWidth,samePadding);
		}
		else if(paddingMethod==HALF){
			addPadding(inputArr,inputArraySize,tempArr,&tempArraySize,
						paddingWidth,halfPadding);
		}
		else{
			printf("Invalid Padding.\n");
		}

		k=0;

		for(i=0;i<inputArraySize;i++){
			if(i%stride==0){
				total=0;
				for(j=i;j<i+kernelArraySize;j++){
					total+=tempArr[j]*kernelArr[j-i];
				}
				outputArr[k++]=total;
			}
		}

		*outputArraySize=((inputArraySize-kernelArraySize+2*paddingWidth)
		/stride)+1;
	}
	
	return result;
}

void 
addPadding(double inputArr[],int inputArraySize,double outputArr[],int
*outputArraySize,int paddingWidth,void paddingMethod(double[], int, int)){

	int i;
	
	*outputArraySize=inputArraySize+(2*paddingWidth);

	for(i=0;i<*outputArraySize;i++){
		if(i>=paddingWidth && i<inputArraySize+paddingWidth)
		outputArr[i]=inputArr[i-paddingWidth];
	}

	paddingMethod(outputArr,*outputArraySize,paddingWidth);

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
/*			 End of HW04_TaipBayram_Komut_131044010_part2.c			  	*/
/*----------------------------------------------------------------------*/

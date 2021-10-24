/*_______________________________Part 2_________________________________*/
/*______________________________________________________________________*/
/*__________________HW02_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 12/03/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*__The program draw shape of a car according to the specific position__*/
/*______________________________________________________________________*/

/*_______________________________Includes_______________________________*/

#include<stdio.h>

/*_________________________Function Prototypes__________________________*/

void drawRectangle(int width,int height, int startingPointr, int printLastLine);
void drawDoubleCircle(int radius, int startingPoint , int whellDistance);
void drawCar();


int 
main(){
	
	drawCar();
	
	return 0;
}

void 
drawCar(){
	
	int radius;
	int startingPointc,startingPointr;
	int whellDistance;
	int width,height;
	int printLastLine;
	
	scanf("%d",&width);
	scanf("%d",&height);
	scanf("%d",&startingPointr);
	scanf("%d",&printLastLine);	
	
	scanf("%d",&radius);
	scanf("%d",&startingPointc);
	scanf("%d",&whellDistance);	
	
	drawRectangle(width,height,startingPointr,printLastLine);
	drawDoubleCircle(radius,startingPointc,whellDistance);
	
}

void 
drawRectangle(int width,int height, int startingPointr, int printLastLine){
	
	int i,j,control;

	control=0;
	
	for(i=0;i<printLastLine;i++)
	printf("\n");

	for(i=0;i<width;i++){
		control++;
		for(j=0;j<startingPointr;j++)
			printf(" ");
			printf("*");
		for(j=0;j<height-2;j++){
			if(control==1)
			printf("*");
			else
			printf(" ");
		}
			printf("*\n");	
	}
	
	control=0;
	
	for(i=0;i<width;i++){
		control++;
		printf("*");
		for(j=0;j<height+2*startingPointr-2;j++){
			if(control==1 || control==width)
			printf("*");
			else
			printf(" ");
		}
			printf("*\n");					
	}	

}

void 
drawDoubleCircle(int radius, int startingPoint , int whellDistance){

	int i,j,k,c;
	
	for(k=1;k<=2*radius+1;k++){
		if(k<=radius+1){
			for(i=0;i<=startingPoint+2*(radius-k);i++)
				printf(" ");
			for(j=0;j<2*k-1;j++){
				printf(" ");	
				printf("*");
			}
			for(c=1;c<=whellDistance-4*(k-1-radius);c++)
				printf(" ");
			for(j=0;j<2*k-1;j++){
				printf(" ");
				printf("*");
			}
			printf("\n");
		}
		else{
			for(i=0;i<=startingPoint+2*(k-radius-2);i++)
				printf(" ");
			for(j=2*k;j<=2*(2*radius+1);j++){
				printf(" ");	
				printf("*");
			}
			for(c=1;c<=whellDistance+4*(k-radius-1);c++)
				printf(" ");													
			for(j=2*k;j<=2*(2*radius+1);j++){
				printf(" ");
				printf("*");
			}
			printf("\n");				
		}
	}

}
/*----------------------------------------------------------------------*/
/*			 End of HW02_TaipBayram_Komut_131044010_part2.c			  	*/
/*----------------------------------------------------------------------*/

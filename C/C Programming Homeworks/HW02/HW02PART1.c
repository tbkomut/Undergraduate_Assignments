/*_______________________________Part 1_________________________________*/
/*______________________________________________________________________*/
/*__________________HW02_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 12/03/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*_In the program,Shape of an equation is drawn on the coordinate plane_*/
/*______________________________________________________________________*/

/*_______________________________Includes_______________________________*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>

/*_________________________Function Prototypes__________________________*/

int fTheFunction(int x,int functionNumber);
void drawFunction(int xAxis,int yAxis,int functionNumber);

int main(){

	
	int x;
	int functionNumber;
	int xAxis,yAxis;	

	scanf("%d",&x);
	scanf("%d",&functionNumber);
	
	printf("Result=%d.\n",fTheFunction(x,functionNumber));
	drawFunction(xAxis,yAxis,functionNumber);
	
	return 0;
}

int 
fTheFunction(int x,int functionNumber){

	int calculate;	
		
	if(functionNumber==1)
		calculate=2*x;	
	else if(functionNumber==2)
		calculate=(-5*x)-4;
	else if(functionNumber==3)
		calculate=-(3*x);
	else if(functionNumber==4)
		calculate=5;
	else if(functionNumber==5)
		calculate=(3*x)+5;
		
	return calculate;
}

void 
drawFunction(int xAxis,int yAxis,int functionNumber){
	
	int i,j;	
	int m,r;
	int count;
	
	scanf("%d",&xAxis);
	scanf("%d",&yAxis);
	scanf("%d",&functionNumber);

	r=fTheFunction(xAxis,functionNumber);

	m=(r/xAxis);
	printf("m=%d\n",m);
	
	if(m>0){
	for(i=0;i<yAxis+1;i++){
		printf("|");
		if(i<yAxis){
			if(i%m==0){	
			count=0;
			for(j=i/m;j<yAxis/m;j++){
				if(count<xAxis && count<yAxis)
				printf(" ");
				count++;
			}
			if(count<xAxis && count<yAxis)
				printf("*");
				count++;
			}
			printf("\n");
		}
		else{
			for(j=0;j<xAxis;j++)
			printf("-");
			printf("\n");
		}	
	}
	}

	else if(m==0){
		for(i=0;i<yAxis+1;i++){
		if(i<yAxis){
			if(yAxis-i==r){
				printf("|");
				for(j=0;j<xAxis;j++)
					printf("*");
				printf("\n");
			}
			else{
				if(i!=yAxis-1)
				printf("|\n");
				else
				printf("|");
			}
		}
		else{
			for(j=0;j<xAxis;j++)
				printf("-");
				printf("\n");
		}		
		}
	}
	
	else if(m<0){
		m=(-1*m);
		for(i=yAxis+1;i>0;i--){
			printf("|");
			if(i>1){
				if(i%m==0){	
				count=0;			
				for(j=i/m;j<=yAxis/m;j++){
				if(count<xAxis && count<yAxis)
				printf(" ");
				count++;
				}
				if(count<xAxis && count<yAxis)
					printf("*");
				count++;
				}
				printf("\n");
			}
			else{
				for(j=0;j<xAxis;j++)
				printf("-");
				printf("\n");
			}	
		}						
	}

}

/*----------------------------------------------------------------------*/
/*			 End of HW02_TaipBayram_Komut_131044010_part1.c			  	*/
/*----------------------------------------------------------------------*/

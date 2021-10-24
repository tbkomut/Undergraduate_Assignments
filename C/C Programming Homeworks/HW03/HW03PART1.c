/*_______________________________Part 1_________________________________*/
/*______________________________________________________________________*/
/*__________________HW03_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 19/03/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*__The program finds prime numbers and It proves goldbach conjecture___*/
/*________Goldbach conjecture claims that every even integer that_______*/ 
/*____is greater than 2 can	be written as a sum	of two prime numbers____*/
/*______________________________________________________________________*/

/*_______________________________Includes_______________________________*/

#include<stdio.h>

/*_________________________Function Prototypes__________________________*/

int goldbach(int num, int *p1, int *p2);
int isPrime(int num);

int 
main(){

	int num;
	int p1;
	int p2;

	scanf("%d",&num);
	
	printf("%d\n",goldbach(num,&p1,&p2));
	printf("->%d\n",p1);
	printf("-->%d\n",p2);
	
	return 0;
}

int 
isPrime(int num){
	
	int i;
	int result;

    result=1;

	if(num<2){
		result=0;
	}
	else{
    	for(i=2;i<num;i++){
    		if(num%i==0)
    		result=0;
    	}
	}
	
	return result;
	
}

int 
goldbach(int num, int *p1, int *p2){

    int i,j;
    int result;

	if(num<=2 || num%2==1){
		result=0;
	}
	else{
		for(i=0;i<num;i++){	
			for(j=0;j<num;j++){			
				if(num==i+j){
					if((isPrime(i)==1) && (isPrime(j)==1)){
					    *p1=i;
				        *p2=j;
                        result=1;
					}
				}
			}
		}
	}

    return result;
}

/*----------------------------------------------------------------------*/
/*			 End of HW03_TaipBayram_Komut_131044010_part1.c			  	*/
/*----------------------------------------------------------------------*/

/*_______________________________Part 2_________________________________*/
/*______________________________________________________________________*/
/*__________________HW01_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 03/03/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*___________The program calculates the age of any tree species_________*/ 
/*______________________________________________________________________*/

/*_______________________________Includes_______________________________*/

#include<stdio.h>

/*______________________________Definitions_____________________________*/

#define PI 3.14

/*_________________________Function Prototypes__________________________*/

float diameter(float circumference);
float ageOfTree(float diameter , float growth_factor);

int main(){

	float circumference;
	float pine;
	float age;
	float dia;

	printf("Please enter circumference of tree and its growth factor:\n");
	scanf("%f",&circumference);
	scanf("%f",&pine);

	dia=diameter(circumference);
	age=ageOfTree(dia,pine);

	printf("Age of Tree=%.3f\n",age);

	return 0;
}

float 
diameter(float circumference){

	printf("Diameter is %.3f\n",circumference/PI);

	return (circumference/PI);
}

float 
ageOfTree(float diameter,float growth_factor){

	float result;
	
	result=diameter*growth_factor;

	return 	result;
}

/*----------------------------------------------------------------------*/
/*			 End of HW01_TaipBayram_Komut_131044010_part2.c			  	*/
/*----------------------------------------------------------------------*/

/*

Program makes calculating Gaussian elimination with scaled partial pivoting.

*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void functionList(char arr[][20]);
void file(char* str);
void solutionOfEquations(char* str,char* ptr);
void scaledPivoting(char* str);
void GaussMethod(double number[][50],int queue,int line);

int 
main(){

	file("system.txt");
	scaledPivoting("system.txt");

	return 0;
}

void 
scaledPivoting(char* filename){
	
	FILE *fptr;
	char str[10][50];			/*	Satırdaki Denklemin stringi				*/
	char temp[50];
	int lcv,nlcv;				/*	Dosya sonu kontrolü	için counter		*/
	int numberofLine;			/*	Dosyadaki satır sayısı 					*/
	int size;
	int i,j,k,m;
	int firstQ;
	char Svalue[20];
	double totalOfS[20];	
	double need[20];
	double MaxS[10];
	double x1[10];
	double number[10][50];
	double max;
	double x[50];

	if((fptr=fopen(filename,"r"))==NULL){
		fprintf(stderr,"File was not founded!\n");
		exit(0);	
	}
	else{

		numberofLine=0;
		while(!feof(fptr)){
			fgets(str[0],50,fptr);
			numberofLine++;
		}

		numberofLine=numberofLine-1;

		fclose(fptr);

		/********************/

		fptr=fopen(filename,"r");

		lcv=0;

		m=0;
		while(lcv<numberofLine){
			fscanf(fptr,"%s",str[lcv]);

			/*Denklem sonundaki result kısmı atılır.*/
			size=strlen(str[lcv]);
			while(str[lcv][size-1]!=','){
				size--;
			}
			
			/* Katsayıların mutlak değerlerini buluyor her denklemdeki*/
			for(i=0,j=0;i<size;i++){
				k=0;
				while(str[lcv][i]!=','){
					if(str[lcv][i]!='-'){					
						Svalue[k++]=str[lcv][i];
					}
					i++;
				}
				Svalue[k]='\0';
				sscanf(Svalue,"%lf",&totalOfS[j++]);
				need[m++]=totalOfS[j-1];				
			}
			/*En büyük katsayıyı buluyor denklemdeki Yani S'i*/
			MaxS[lcv]=totalOfS[0];
			for(i=1;i<j;i++){
				if(MaxS[lcv]<totalOfS[i])
				MaxS[lcv]=totalOfS[i];
			}
			lcv++;
		}

		size=m;
		
		fclose(fptr);

		/********************/

		fptr=fopen(filename,"r");

		/*Bu Kod Pivotlanacak Satırların değerini buluyor*/		
		nlcv=0;
		while(nlcv<numberofLine){
			max=0;
			firstQ=0;
			/***************/
			for(i=nlcv;i<lcv;i++){
				x1[i]=need[i*j+nlcv]/MaxS[i];
				if(x1[i]>max){
					max=x1[i];
					firstQ=i;
					if(i>nlcv){
						strcpy(temp,str[firstQ]);
						strcpy(str[firstQ],str[0]);
						strcpy(str[0],temp);
					}
				}	
			}
			/***************/
			if(nlcv==0){
				for(m=0;m<numberofLine;m++){
					for(j=0,k=0;str[m][j]!='\0';j++){
						if(str[m][j-1]==',' || j==0){
							sscanf(&str[m][j],"%lf",&number[m][k]);
							k++;
						}
					}
				}
			}
			GaussMethod(number,nlcv,numberofLine);	/*	Gauss Metodu Burada.	*/
			nlcv++;
		}
		for(m=0;m<numberofLine;m++){
			for(j=0;j<k;j++){
				printf(" %.2f ",number[m][j]);
			}
			printf("\n");
		}

		/*	Son adımda da x'lerimizi hesaplıyoruz.	*/
		for(m=numberofLine-1;m>=0;m--){
			for(j=m,x[m]=0;j<k-1;j++){
				if(j==m)
					x[m]+=number[m][k-1];
				else if(j>m){
					x[m]+=-1*number[m][(k-1)-(j-m)]*x[numberofLine+(m-j)];	
				}
			}
			printf("x[%d]=%.2f\n",m+1,x[m]);
		}

		fclose(fptr);

		/*******************/

	}
}

void 
GaussMethod(double number[][50],int column,int line){

	int i,j;
	double oran;
	double pivot[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	for(j=column;j<line;j++){
		if(j==column){
			oran=number[column][column];
			for(i=column;i<=line;i++){
				number[j][i]=number[j][i]/oran;
				pivot[i-column]=number[j][i];
			}
		}
		else{
			oran=-number[j][column]/number[column][column];
			for(i=column;i<=line;i++){
				number[j][i]=number[j][i]+oran*pivot[i-column];
			}
		}
	}

}


void 
file(char* str){
	
	FILE *fptr;
	char equations[3][20];
	int  index;

	functionList(equations);	

	if((fptr=fopen(str,"w"))==NULL){
		fprintf(stderr,"File open error!\n");
		exit(0);
	}
	else{
		index=0;
		while(index<3){
			fprintf(fptr,"%s\n",equations[index++]);
		}
		fclose(fptr);
	}

}

void 
functionList(char arr[][20]){

	char choose;		
	
	do{
		fprintf(stderr,"You should choose one of them (a,b,c)\n");
		scanf(" %c",&choose);

		if(choose=='a' || choose=='A'){
			strcpy(arr[0],"3,-1,1,1");
			strcpy(arr[1],"3,6,2,0");
			strcpy(arr[2],"3,3,7,4");
		}
		else if(choose=='b' || choose=='B'){
			strcpy(arr[0],"10,-1,0,9");
			strcpy(arr[1],"-1,10,-2,7");	
			strcpy(arr[2],"0,-2,10,6");
		}
		else if(choose=='c' || choose=='C'){
			strcpy(arr[0],"2,-3,2,5");
			strcpy(arr[1],"-4,2,-6,14");	
			strcpy(arr[2],"2,2,4,8");
		}
		else{
			printf("Invalid choose! Please you take a between (a-c) character.\n");
			exit(0);
		}
	}while((choose=='a' || choose=='A') && (choose=='b' || choose=='B')
			&& (choose=='c' || choose=='C'));

}

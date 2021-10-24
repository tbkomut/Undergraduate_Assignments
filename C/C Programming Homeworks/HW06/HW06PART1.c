/*_______________________________Part 1_________________________________*/
/*______________________________________________________________________*/
/*__________________HW06_131044010_TaipBayram_Komut_____________________*/
/*______________________________________________________________________*/
/*______________________________________________________________________*/
/*_____________Created on 25/04/2017 by TaipBayram_Komut________________*/
/*______________________________________________________________________*/
/*______________________________Description_____________________________*/
/*______________________________________________________________________*/
/*___________________A game is called "Minesweeper"_____________________*/
/*________The goal is to find all the empty cells and open them_________*/ 
/*_______The game will give a "win" message if you find them all________*/ 
/*__________________If you choose to open a mined cell__________________*/
/*_____________The game will give a "loose" message and end_____________*/
/*______________________________________________________________________*/

/*_______________________________Includes_______________________________*/
#include<stdio.h>
#define GRIDSIZE 4

/*	Typedef Enum Structure	*/
typedef enum {
	mined,
	empty,
	flaggedMined,
	flaggedEmpty,
	closedEmpty,	
	closedMined
}cell;

/*	Functions	*/
int asMain();
void initGrid(cell grid[][GRIDSIZE]);
void printGrid (cell grid[][GRIDSIZE]);
int openCell(cell grid[][GRIDSIZE],int x,int y);
int isCellEmpty(cell grid[][GRIDSIZE],int x,int y);
int isLocationLegal(int x,int y);
void flagCell(cell grid[][GRIDSIZE],int x,int y);
/*	Helper Functions	*/
int stateOfgame(cell grid[][GRIDSIZE]);
/*	Main Function	*/
int 
main(){

	asMain();

	return 0;
}
/*	The function to take player's choice.	*/
int 
asMain(){

	int x,y;
	cell grid[GRIDSIZE][GRIDSIZE];
	char chosen;		/*	The variable will be opened or flagged	*/
	int stepCount;		/*	Total number of valid steps 			*/
	int breaklcv;		/*	The variable If it is found the mined cell,
							the game ends.*/

	initGrid(grid);

	stepCount=0;
	breaklcv=0;

	do{
		printGrid(grid);		
		printf("Please you entry [x,y] inputs.\n");
		scanf("%d",&x);
		scanf("%d",&y);
		printf("(%d,%d)\n",x,y);
		do{
			printf("Do you want to (un)flagged or open the cell?");
			printf("For choice press (o/f)\n");
			scanf(" %c",&chosen);
			if(chosen=='o' || chosen=='O'){
					if(grid[x][y]==closedEmpty){
						printf("%d\n",openCell(grid,x,y));
						stepCount++;
					}
					if(grid[x][y]==mined){
						breaklcv=1;	
						printf("You loose\n");		
					}
			}
			else if(chosen=='f' || chosen=='F'){
				if(isLocationLegal(x,y)==1){
					flagCell(grid,x,y);
					stepCount++;
				}
			}
			else{
				printf("Invalid choice.You should chosen open(o) or flag(f)\n");
			}
		}while(!(chosen=='f' || chosen=='F') && !(chosen=='o' || chosen=='O'));			
	}while(breaklcv!=1 && stateOfgame(grid)!=1);


	if(breaklcv!=1){
		printGrid(grid);
		printf("Congratulations! You win the game with %d moves\n",stepCount);
	}

	return 0;	
}
/*	Initially assigns values to the cells.	*/
void 
initGrid(cell grid[][GRIDSIZE]){

	int i,j;

	for(i=0;i<GRIDSIZE;i++){
		for(j=0;j<GRIDSIZE;j++){
			if(	(i==0 && (j==1 || j==2)) || (i==1 && (j==2 || j==3)) ){
				grid[i][j]=closedMined;
			}
			else{
				grid[i][j]=closedEmpty;
			}
		}
	}

}
/*	Shows the current game board.	*/
void 
printGrid(cell grid[][GRIDSIZE]){

	int i,j,k;

	for(i=0;i<GRIDSIZE;i++){
		for(k=0;k<GRIDSIZE*4+1;k++)
			printf("-");
		printf("\n|");
		for(j=0;j<GRIDSIZE;j++){
			if(grid[i][j]==empty){
				printf(" e |");
			}
			else if(grid[i][j]==closedEmpty || grid[i][j]==closedMined){
				printf(" . |");
			}
			else if(grid[i][j]==flaggedEmpty || grid[i][j]==flaggedMined){
				printf(" f |");
			}
		}
		printf("\n");
	}

	for(k=0;k<GRIDSIZE*4+1;k++)
		printf("-");
		printf("\n");

}
/*	The recursive function that the user wants to open the cell.	*/
int 
openCell(cell grid[][GRIDSIZE], int x, int y){

	int i,j;
	int result;

	if(isLocationLegal(x,y)==1){
		if(grid[x][y]==closedEmpty){
			grid[x][y]=empty;
			result=1;
			for(i=x-1;i<=x+1;i++){
				for(j=y-1;j<=y+1;j++){
					if(!(i==x && j==y)){
						if(isLocationLegal(i,j)==1){
							if(grid[i][j]==closedEmpty)
							result+=openCell(grid,i,j);
						}
					}
				}	
			}
		}

		else if(grid[x][y]==closedMined){
			grid[x][y]=mined;
			result=0;
		}
		else if(grid[x][y]==flaggedEmpty || grid[x][y]==flaggedMined){
			result=0;
		}
		else if(isCellEmpty(grid,x,y)==1){
			result=0;
		}
	}
	else{
		result=0;
	}

	return result;
}
/*	Checks whether the opened cell is empty.	*/
int 
isCellEmpty(cell grid[][GRIDSIZE], int x, int y){

	int result;

	if(grid[x][y]==empty){
		result=1;	
	}
	else{
		result=0;
	}

	return result;
}
/*	The selected cell is flagged, or the flag is removed if it is flagged.	*/
void 
flagCell(cell grid[][GRIDSIZE], int x, int y){

	if(grid[x][y]==closedMined){
		grid[x][y]=flaggedMined;
	}
	else if(grid[x][y]==closedEmpty){
		grid[x][y]=flaggedEmpty;
	}
	else if(grid[x][y]==flaggedMined){
		grid[x][y]=closedMined;
	}
	else if(grid[x][y]==flaggedEmpty){
		grid[x][y]=closedEmpty;
	}

}
/*	Is the selected cell in the game board?	*/
int 
isLocationLegal(int x, int y){

	int result;

	if(x>=GRIDSIZE || y >=GRIDSIZE){
		result=0;
	}
	else if(x<0 || y<0){
		result=0;
	}
	else{
		result=1;
	}

	return result;
}

/*	A function that checks whether all empty cells have been opened.	*/
int 
stateOfgame(cell grid[][GRIDSIZE]){

	int i,j;
	int finish;

	finish=1;

	for(i=0;i<GRIDSIZE;i++){
		for(j=0;j<GRIDSIZE;j++){
			if(grid[i][j]==flaggedEmpty || grid[i][j]==closedEmpty){
				finish=0;
			}
		}
	}

	return finish;
}
/*----------------------------------------------------------------------*/
/*				End of HW06_TaipBayram_Komut_131044010_part1.c			*/
/*----------------------------------------------------------------------*/

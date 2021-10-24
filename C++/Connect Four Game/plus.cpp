#include <iostream>
#include "plus.h"

namespace plusKomut{

	/*--------------------------Constructors and Others-------------------------*/

	ConnectFourPlus::ConnectFourPlus():ConnectFourAbstract(){


	}

	ConnectFourPlus::ConnectFourPlus(int rowSize,int colomnSize):ConnectFourAbstract(rowSize,colomnSize){


	}

	ConnectFourPlus::~ConnectFourPlus(){


	}

	ConnectFourPlus::ConnectFourPlus(const ConnectFourPlus& value):ConnectFourAbstract(value){


	}

	/*---------------------End of game is controled in here---------------------*/

	int ConnectFourPlus::gameStatus(int row,int colomn){

		int result=0;
		int vertical=verticalControl(row,colomn,0);
		int horizontal=horizontalControl(row,colomn,0);
		if(horizontal==4 || vertical==4){		
			result=1;
		}
		else{
			int count=0;
			for(int i=0;i<getBoardColomn();++i){
				if(gameBoard[0][i].getPlayer()=='.')
				count++;
			}
			if(count==0)	result=2;
		}

		return result;
	}


	/*----------------------------Computer Logic--------------------------------*/

	/*	For the next move,the computer player moves when the game is over. */
	int ConnectFourPlus::searchFourList(const int* row,int &colomn,char gamer){

		int i;
		int reset=0;
		colomn=0;
		for(i=0,reset=0;i<getBoardColomn() && reset==0;++i){
			if(legalPosition('A'+i)==1){
				gameBoard[row[i]-1][i].setPlayer(gamer);
				if(verticalControl(row[i]-1,i,1)==4){
					reset++;
					colomn=i;
				}
				if(horizontalControl(row[i]-1,i,1)==4){
					reset++;
					colomn=i;
				}
				gameBoard[row[i]-1][i].setPlayer('.');
			}
		}

		return reset;

	}

	/*	If User can finish the game for next move.It allows user's next move is blocked. */
	int ConnectFourPlus::blockEnemyList(const int* row,int &colomn,char gamer){

		int i;
		int block=0;
		colomn=0;
		for(i=0,block=0;i<getBoardColomn() && block==0;++i){
			if(legalPosition('A'+i)==1){
				gameBoard[row[i]-1][i].setPlayer(gamer);
				if(verticalControl(row[i]-1,i,1)==4){
					block++;
					colomn=i;
				}
				if(horizontalControl(row[i]-1,i,1)==4){
					block++;
					colomn=i;
				}
				gameBoard[row[i]-1][i].setPlayer('.');
			}
		}

		return block;
	
	}

	/*	If the game is not over for the next move,It tries to create a long list for computer. */
	void ConnectFourPlus::makeList(const int* row,int &colomn,char gamer){

		int i,j;
		int *maxNumber=new int[getBoardColomn()];
		int step1,step2;
		int max=0;
		int reset;
		int random;

		for(i=0;i<getBoardColomn();++i){
			if(legalPosition('A'+i)==1){
				step1=verticalControl(row[i]-1,i,1);
				step2=horizontalControl(row[i]-1,i,1);
				if(step1>max)	max=step1;
				if(step2>max)	max=step2;
			}
		}
	
		for(i=0,j=0;i<getBoardColomn();++i){
			if(legalPosition('A'+i)==1){
				step1=verticalControl(row[i]-1,i,1);
				step2=horizontalControl(row[i]-1,i,1);
				if((step1==max || step2==max)){
					maxNumber[j++]=i;
				}
			}
		}

		if(j!=0){
			srand(time(NULL));
			random=rand()%j;		
		}
		else{
			random=0;
		}

		colomn=maxNumber[random];

		delete maxNumber;

	}

	/*---------------------------Game's Logic Rules-----------------------------*/

	int ConnectFourPlus::verticalControl(int row,int colomn,int status){

		int count=0;
		int breakLoop=0;
		char gamer=gameBoard[row][colomn].getPlayer();

		for(int i=row;i<getBoardRow() && i<row+4 && breakLoop==0;++i){
			if(gameBoard[i][colomn].getPlayer()==gamer)	count++;
			else	breakLoop++;
		}
		if(count==4 && status==0)
			for(int j=row;j<row+4;++j){
				gameBoard[j][colomn].setPlayer(gamer+('a'-'A'));
		}

		return count;
	}

	int ConnectFourPlus::horizontalControl(int row,int colomn,int status){
	
		int i,j,k;
		int breakLoop;
		int count;
		int max=0;
		char gamer=gameBoard[row][colomn].getPlayer();

		for(i=colomn-3;i<=colomn && i<getBoardColomn();++i){
			if(i>=0 && i<=getBoardColomn()-3){
				for(j=i,count=0,breakLoop=0;j<i+4 && breakLoop==0;++j){
					if(gameBoard[row][j].getPlayer()==gamer)	count++;
					else	breakLoop++;
				}
				if(max<count)
				max=count;
				if(count==4 && status==0)
					for(k=i;k<i+4;++k){
						gameBoard[row][k].setPlayer(gamer+('a'-'A'));
				}
			}
		}

		return max;

	}

}

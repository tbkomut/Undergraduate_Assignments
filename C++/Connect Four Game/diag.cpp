#include <iostream>
#include "diag.h"

namespace diagKomut{

	/*--------------------------Constructors and Others-------------------------*/

	ConnectFourDiag::ConnectFourDiag():ConnectFourAbstract(){


	}

	ConnectFourDiag::ConnectFourDiag(int rowSize,int colomnSize):ConnectFourAbstract(rowSize,colomnSize){


	}

	ConnectFourDiag::~ConnectFourDiag(){


	}

	ConnectFourDiag::ConnectFourDiag(const ConnectFourDiag& value):ConnectFourAbstract(value){


	}

	/*---------------------End of game is controled in here---------------------*/

	int ConnectFourDiag::gameStatus(int row,int colomn){

		int result=0;
		int diagonal=diagonalControl(row,colomn,0);
		if(diagonal==4){		
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
	int ConnectFourDiag::searchFourList(const int* row,int &colomn,char gamer){

		int i;
		int reset=0;
		colomn=0;
		for(i=0,reset=0;i<getBoardColomn() && reset==0;++i){
			if(legalPosition('A'+i)==1){
				gameBoard[row[i]-1][i].setPlayer(gamer);
				if(diagonalControl(row[i]-1,i,1)==4){
					reset++;
					colomn=i;
				}
				gameBoard[row[i]-1][i].setPlayer('.');
			}
		}

		return reset;

	}

	/*	If User can finish the game for next move.It allows user's next move is blocked. */
	int ConnectFourDiag::blockEnemyList(const int* row,int &colomn,char gamer){

		int i;
		int block=0;
		colomn=0;
		for(i=0,block=0;i<getBoardColomn() && block==0;++i){
			if(legalPosition('A'+i)==1){
				gameBoard[row[i]-1][i].setPlayer(gamer);
				if(diagonalControl(row[i]-1,i,1)==4){
					block++;
					colomn=i;
				}
				gameBoard[row[i]-1][i].setPlayer('.');
			}
		}

		return block;
	
	}

	/*	If the game is not over for the next move,It tries to create a long list for computer. */
	void ConnectFourDiag::makeList(const int* row,int &colomn,char gamer){

		int i,j;
		int *maxNumber=new int[getBoardColomn()];
		int step;
		int max=0;
		int reset;
		int random;

		for(i=0;i<getBoardColomn();++i){
			if(legalPosition('A'+i)==1){
				step=diagonalControl(row[i]-1,i,1);
				if(step>max)	max=step;
			}
		}
	
		for(i=0,j=0;i<getBoardColomn();++i){
			if(legalPosition('A'+i)==1){
				step=diagonalControl(row[i]-1,i,1);
				if(step==max){
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

	int ConnectFourDiag::diagonalControl(int row,int colomn,int status){

		int i,j,k,r,c;
		int test1,test2;
		int count=0;
		int breakLoop;
		int max1=0,max2=0;
		int max=0;
		int reset;	
		char gamer=gameBoard[row][colomn].getPlayer();

		/*	Left top-> right bottom diagonal control	*/

		for(i=-3,reset=0;i<=3 && reset==0;++i){
			r=row+i;
			c=colomn+i;
			if(i<0){
				for(j=0,count=0,breakLoop=0;j<4 && breakLoop==0;++j){
					if(((r+j>=0) && (r+j<getBoardRow())) && ((c+j>=0) && (c+j<getBoardColomn()))){
						if(gameBoard[r+j][c+j].getPlayer()==gamer)	count++;
						else breakLoop++;
					}
					else breakLoop++;
				}
				if(count>max1)	max1=count;
				if(count==4 && status==0){
					reset++;
					for(k=0;k<4;++k)
					gameBoard[r+k][c+k].setPlayer(gamer+('a'-'A'));
				}
			}
			else if(i==0){
				for(j=0,test1=0,breakLoop=0;j<4 && breakLoop==0;++j){
					if(((r+j>=0) && (r+j<getBoardRow())) && ((c+j>=0) && (c+j<getBoardColomn()))){
						if(gameBoard[r+j][c+j].getPlayer()==gamer)	test1++;
						else breakLoop++;
					}
					else breakLoop++;
				}
				for(j=0,test2=0,breakLoop=0;j<4 && breakLoop==0;++j){
					if(((r-j>=0) && (r-j<getBoardRow())) && ((c-j>=0) && (c-j<getBoardColomn()))){
						if(gameBoard[r-j][c-j].getPlayer()==gamer)	test2++;
						else breakLoop++;
					}
					else breakLoop++;
				}
				if(test1==4  && status==0){
					reset++;
					for(k=0;k<4;++k)
					gameBoard[r+k][c+k].setPlayer(gamer+('a'-'A'));
				}
				else if(test2==4  && status==0){
					reset++;
					for(k=0;k<4;++k)
					gameBoard[r-k][c-k].setPlayer(gamer+('a'-'A'));
				}
				if(test1>test2)	count=test1;
				else			count=test2;
				if(count>max1)	max1=count;		
			}
			else{
				for(j=0,count=0,breakLoop=0;j<4 && breakLoop==0;++j){
					if(((r-j>=0) && (r-j<getBoardRow())) && ((c-j>=0) && (c-j<getBoardColomn()))){
						if(gameBoard[r-j][c-j].getPlayer()==gamer)	count++;
						else breakLoop++;
					}
					else breakLoop++;
				}
				if(count>max1)	max1=count;
				if(count==4 && status==0){
					reset++;
					for(k=0;k<4;++k)
					gameBoard[r-k][c-k].setPlayer(gamer+('a'-'A'));
				}
			}
		}

		/*	Right top -> left bottom diagonal control	*/

		for(i=-3,reset=0;i<=3 && reset==0;++i){
			r=row+i;
			c=colomn+(-1*i);
			if(i<0){
				for(j=0,count=0,breakLoop=0;j<4 && breakLoop==0;++j){
					if(((r+j>=0) && (r+j<getBoardRow())) && ((c-j>=0) && (c-j<getBoardColomn()))){
						if(gameBoard[r+j][c-j].getPlayer()==gamer)	count++;
						else breakLoop++;
					}
					else breakLoop++;
				}
				if(count>max2)	max2=count;
				if(count==4 && status==0){
					reset++;
					for(k=0;k<4;++k)
					gameBoard[r+k][c-k].setPlayer(gamer+('a'-'A'));
				}
			}
			else if(i==0){
				for(j=0,test1=0,breakLoop=0;j<4 && breakLoop==0;++j){
					if(((r+j>=0) && (r+j<getBoardRow())) && ((c-j>=0) && (c-j<getBoardColomn()))){
						if(gameBoard[r+j][c-j].getPlayer()==gamer)	test1++;
						else breakLoop++;
					}
					else breakLoop++;
				}
				for(j=0,test2=0,breakLoop=0;j<4 && breakLoop==0;++j){
					if(((r-j>=0) && (r-j<getBoardRow())) && ((c+j>=0) && (c+j<getBoardColomn()))){
						if(gameBoard[r-j][c+j].getPlayer()==gamer)	test2++;
						else breakLoop++;
					}
					else breakLoop++;
				}
				if(test1==4  && status==0){
					reset++;
					for(k=0;k<4;++k)
					gameBoard[r+k][c-k].setPlayer(gamer+('a'-'A'));
				}
				else if(test2==4  && status==0){
					reset++;
					for(k=0;k<4;++k)
					gameBoard[r-k][c+k].setPlayer(gamer+('a'-'A'));
				}
				if(test1>test2)	count=test1;
				else			count=test2;
				if(count>max2)	max2=count;		
			}
			else{
				for(j=0,count=0,breakLoop=0;j<4 && breakLoop==0;++j){
					if(((r-j>=0) && (r-j<getBoardRow())) && ((c+j>=0) && (c+j<getBoardColomn()))){
						if(gameBoard[r-j][c+j].getPlayer()==gamer)	count++;
						else breakLoop++;
					}
					else breakLoop++;
				}
				if(count>max2)	max2=count;
				if(count==4 && status==0){
					reset++;
					for(k=0;k<4;++k)
					gameBoard[r-k][c+k].setPlayer(gamer+('a'-'A'));
				}
			}
		}

		if(max1>=max2)	max=max1;
		else			max=max2;

		return max;
	}

}

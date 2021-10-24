#include <iostream>
#include "undo.h"

namespace undoKomut{

	/*-------------------------------Constructors-------------------------------*/

	ConnectFourPlusUndo::ConnectFourPlusUndo():ConnectFourPlus(){

		capacity=10;
		undoBoard=new Cell[capacity];
		totalIndex=0;
	}

	ConnectFourPlusUndo::ConnectFourPlusUndo(int rowSize,int colomnSize):ConnectFourPlus(rowSize,colomnSize){

		capacity=10;
		undoBoard=new Cell[capacity];
		totalIndex=0;
	}

	/*------------------------------And Big Threes-------------------------------*/

	ConnectFourPlusUndo::~ConnectFourPlusUndo(){
		delete[] undoBoard;
	}

	ConnectFourPlusUndo&  ConnectFourPlusUndo:: operator = (const ConnectFourPlusUndo& assign){

		cout << "Assignment" << endl;
		if(this==&assign){
			return *this;
		}
		else{
			deleteBoard();
			setBoardRow(assign.getBoardRow());
			setBoardColomn(assign.getBoardColomn());
			resizeBoard();
			for(int i=0;i<getBoardRow();++i){
				for(int j=0;j<getBoardColomn();++j){
					gameBoard[i][j]=assign.gameBoard[i][j];
				}
			}

			delete[] undoBoard;
			totalIndex=assign.totalIndex;
			capacity=assign.capacity;
			undoBoard=new Cell[capacity];
			for(int i=0;i<totalIndex;++i){
				undoBoard[i]=assign.undoBoard[i];
			}

			return* this;
		}

	}

	ConnectFourPlusUndo::ConnectFourPlusUndo(const ConnectFourPlusUndo& value):ConnectFourPlus(value){

		totalIndex=value.totalIndex;
		capacity=value.capacity;

		undoBoard=new Cell[capacity];

		for(int i=0;i<totalIndex;++i){
			undoBoard[i]=value.undoBoard[i];	
		}		

	}


	/*-------------------------Resize For undoBoard Capacity-------------------*/

	void ConnectFourPlusUndo::addCapacity(){

		Cell* temp=new Cell[totalIndex];
		for(int i=0;i<totalIndex;++i)
			temp[i]=undoBoard[i];
		delete []undoBoard;

		capacity=2*totalIndex;
		undoBoard=new Cell[capacity];
		for(int i=0;i<totalIndex;++i)
			undoBoard[i]=temp[i];

		delete []temp;
	}

	void ConnectFourPlusUndo::renew(){

		addCapacity();
		totalIndex--;

	}

	/*-------------------------------UNDO Processes----------------------------*/

	void ConnectFourPlusUndo::undoCommand(){

		// undo count (totalIndex) should not be zero.
		if(totalIndex>0){
			int lateRow=undoBoard[totalIndex-1].getRow();
			int lateColomn=undoBoard[totalIndex-1].getColomn()-'A';
			gameBoard[lateRow][lateColomn].setRow(lateRow);
			gameBoard[lateRow][lateColomn].setColomn(lateColomn);
			gameBoard[lateRow][lateColomn].setPlayer('.');
			renew();
		}

	}

	void ConnectFourPlusUndo::combineCell(const Cell& value){	

		int row=value.getRow();
		int colomn=value.getColomn()-'A';
		char player=value.getPlayer();
		
		if(totalIndex==capacity)	addCapacity();

		undoBoard[totalIndex].setRow(row);
		undoBoard[totalIndex].setColomn(value.getColomn());
		undoBoard[totalIndex].setPlayer(player);
		totalIndex++;

	}

	/*-------------------------Play with User or Computer----------------------*/

	void ConnectFourPlusUndo::playWithUser(string moves[],int moveSize,int count){

		char input;
		int legal;
		char filename[TEMP_SIZE];
		char copy[TEMP_SIZE];
		char gamer;	
		char type;
		int  row,colomn;
		int condition=0;
		int returnValue;
		int index=1;
		int save=0;
		int late=0;
		int jump=0;

		do{
			do{	
				strcpy(copy,moves[index].c_str());
				if(strlen(copy)==1){
					if(legalPosition(copy[0])==0 ){
						cerr << "This column is full or invalid." << endl;
						legal=-1;
					}
					else{
						input=copy[0];
						if(count%2==0)	cout << "Player1= " << input << endl;
						else			cout << "Player2= " << input << endl;
						legal=0;
					}
				}
				else if(strlen(copy)>4){
					if(strncmp("LOAD",copy,4)==0){
						legal=1;
						strcpy(filename,&copy[5]);
					}
					else if(strncmp("SAVE",copy,4)==0){
						legal=2;
						strcpy(filename,&copy[5]);
					}
					else legal=-1;
				}
				else if(strlen(copy)==4 && strncmp("UNDO",copy,4)==0){
					legal=3;
					if(totalIndex==0){	// If totalIndex=0. Game is started again with X So count should be zero. 
						count=0;
					}
				}
				else	legal=-1;
				if(legal==1){	/* LOAD */
					if(loadFromFile(filename,gamer,type)==0){
						if(gamer=='X')	count=0;
						else	count=1;
						cout << "Load same type game from file." << endl;
						displayBoard();
						cout << "Current Player= " << gamer << endl;
					}
					else{
						cerr << "Process is fail.Current Game will be continued." << endl;
						if(gamer=='X')	count=0;
						else	count=1;
					}
				}
				else if(legal==2){	/* SAVE */
					if(count%2==0)	gamer='X';
					else			gamer='O';
					if(saveCurrentGame(filename,gamer,'P')==0)
						cout << "Game was be saved." << endl;
					if(count%2==0)	gamer='X';
					else			gamer='O';	
				}
				else if(legal==3){	/*	UNDO	*/
					cout << "UNDO" << endl;
					undoCommand();
					displayBoard();
				}
				else if(legal==-1)	
					cerr << "You enter a character for colomn or command(LOAD or SAVE)." << endl;
				index++;
				if(index==moveSize && legal!=0)	late=1;	
				// If last element of list SAVE,LOAD vb, Game is stopped.Otherwise Game was continued so late variable a flag.
			}while(legal!=0 && index<moveSize && late==0);
			if(late==0){
				if(count%2==0)	gamer='X';		/* USER1 */
				else			gamer='O';		/* USER2 */
				Cell current(0,input,gamer);
				play(current);
				colomn=(input+('a'-'A'))-'a';
				returnValue=gameStatus(current.getRow(),colomn);
				if(returnValue==1 || returnValue==2)	condition=1;
				if(condition==0)	displayBoard();
				if(condition==1 && returnValue==1){
					if(index%2==0)
						cout << "The player1 won the game." << endl;	
					else
						cout << "The player2 won the game." << endl;	
				}	
				else if(condition==1 && returnValue==2){
					cout << "The game ended in a draw." << endl;	
				}
				count++;
			}
		}while(index<moveSize && condition==0);
		displayBoard();
	}

	void ConnectFourPlusUndo::playWithComputer(string moves[],int moveSize,int count){

		char input;
		int legal;
		char filename[TEMP_SIZE];
		char copy[TEMP_SIZE];
		char gamer;	
		char type;
		int  row,colomn;
		int condition=0;
		int returnValue;
		int index=1;
		int helper=moveSize;
		int save=0;
		char step;
		int queue=count;
		int exitloop=0;
		int undoCount;
		int late=0;

		do{
			if(count%2==0 || queue%2==0){
				undoCount=0;
				do{
					strcpy(copy,moves[index].c_str());
					if(strlen(copy)==1){
						if(legalPosition(copy[0])==0 ){
							cerr << "This column is full or invalid." << endl;
							legal=-1;
						}
						else{
							input=copy[0];
							legal=0;
							if(undoCount%2!=1)
							cout << "User: " << input << endl;
						}
					}
					else if(strlen(copy)>4){
						if(strncmp("LOAD",copy,4)==0){
							legal=1;
							strcpy(filename,&copy[5]);
						}
						else if(strncmp("SAVE",copy,4)==0){
							legal=2;
							strcpy(filename,&copy[5]);
							cout << filename << endl;
						}
						else legal=-1;
					}
					else if(strlen(copy)==4 && (strncmp("UNDO",copy,4)==0) ){
						legal=3;
						if(totalIndex>0)	undoCount++;
						// Undocount determines the current player when Undo process is realised. 
						else	undoCount=0;
						// UndoCount should be zero. Because totalIndex is a zero and Game is start with X.
					}
					else	legal=-1;
					if(legal==1){	/* LOAD */
						if(loadFromFile(filename,gamer,type)==0){
							if(gamer=='X')	queue=0;
							else	queue=1;
							cout << "Load same type game from file." << endl;
							displayBoard();
							cout << "Current Player= " << gamer << endl;
						}
						else{
							cerr << "Process is fail.Current Game will be continued." << endl;
							if(gamer=='X')	queue=0;
							else	queue=1;
						}	
					}
					else if(legal==2){	/* SAVE */
						if(count%2==0)	gamer='X';
						else			gamer='O';
						if(saveCurrentGame(filename,gamer,'C')==0)
							cout << "Game was be saved." << endl;
					}
					else if(legal==3){	/*	UNDO	*/
						cout << "UNDO" << endl;
						undoCommand();	// Undo process is realised here.
						displayBoard();
					}
					else if(legal==-1){
						cerr << "You enter a character for colomn or command(LOAD or SAVE)." << endl;
					}
					if(legal!=0) helper--;
					index++;
					if(index==moveSize && legal!=0 && legal!=3)	late=1;
				}while(legal!=0 && index<moveSize && late==0);
				if(late==0){
					if(undoCount%2==1){
						int computerStatus=play();
						if(computerStatus==1 || computerStatus==2)	condition=1;
						if(condition==0 && count<=2*(helper-1))	displayBoard();
						if(condition==1){
							if(computerStatus==1)
								cout << "The computer won the game." << endl;	
							else
								cout << "The game ended in a draw." << endl;
						}
					}
					gamer='X';
					if(undoCount%2==1)
						cout << "User: " << input << endl;
					colomn=(input+('a'-'A'))-'a';
					count++;
					queue++;
					if(input != copy[0]) exitloop=1;
					if(exitloop==0){
						Cell current(0,input,'X');
						play(current);
						colomn=(input+('a'-'A'))-'a';
						returnValue=gameStatus(current.getRow(),colomn);
						if(returnValue==1 || returnValue==2)	condition=1;
						if(condition==0 && count<=2*(helper-1))	displayBoard();
						if(condition==1){
							if(returnValue==1)
								cout << "The player won the game." << endl;		
							else
								cout << "The game ended in a draw." << endl;	
						}	
					}
				}
			}
			else{
				int computerStatus=play();
				count++;
				queue++;
				if(computerStatus==1 || computerStatus==2)	condition=1;
				if(condition==0 && count<=2*(helper-1))	displayBoard();
				if(condition==1){
					if(computerStatus==1)
						cout << "The computer won the game." << endl;	
					else
						cout << "The game ended in a draw." << endl;
				}
			}
		}while((count<2*(helper-1) && condition==0) && exitloop==0);
		cout << "Game Board Result" << endl;
		displayBoard();
	}

	/*------------------------------Play Functions-------------------------------*/

	int ConnectFourPlusUndo::play(){
		char input;
		int intVal;
		int rowVal;
	
		moveOfComputer(intVal);
		input='A'+intVal;
		assignToBoard(rowVal,intVal,'O');
		cout << "Computer = " << input << endl;
		Cell value(rowVal,input,'O');
		combineCell(value);
		int status=gameStatus(rowVal,intVal);
		int result;
	
		return status;
	}


	void ConnectFourPlusUndo::play(Cell& current){
		int rowValue;
		int colomnValue = (current.getColomn()-'A');
		assignToBoard(rowValue,colomnValue,current.getPlayer());
		current.setRow(rowValue);
		combineCell(current);
	}

	/*-----------------------------LOAD and SAVE-------------------------------*/

	int ConnectFourPlusUndo::loadFromFile(const char filename[],char &gamer,char &type){

		char *tempColomn;
		int testA1,testA2;
		int i,j;	
		char test1[TEMP_SIZE],test2[TEMP_SIZE],test3[TEMP_SIZE];
		ifstream loadFile;
		auto chr='a';				/* Auto Usage */
		int b=3;					/* To Show useage of decltype */
		decltype(b+2) result;		/* Decltype Usage */
		int allowed=0;
		char testB,testC;
		int size;
		int countRow=0,countColomn=0;

		loadFile.open(filename);

		if(loadFile.fail()){
			cerr << "File is not be found!\n";
			result=-1;
		}	
		else{
			int line=0;
			int count=0;
			i=0,j=0;
			while(loadFile.get(chr)){
				if(chr=='\n'){
					if(line==0){
						test1[count]='\0';
						count=0;
					}
					else if(line==1){
						test2[count]='\0';
						sscanf(test1,"%d",&testA1);	
						sscanf(test2,"%d",&testA2);
						count=0;
					}
					else if(line==4){
						test3[count]='\0';
						sscanf(test3,"%d",&size);
						tempColomn=new char[size];
					}
					else if(line>4){
						countColomn++;
					}
					line++;
				}
				else{
					if(line==0)			test1[count++]=chr;
					else if(line==1)	test2[count++]=chr;
					else if(line==2)	testB=chr;
					else if(line==3)	testC=chr;
					else if(line==4)	test3[count++]=chr;
					else{
						tempColomn[countColomn]=chr;
					}
				}
			}
		}

		if((testB=='P' || testB=='C') && (testC=='X' || testC=='O'))
		allowed=1;
		else	allowed=0;

		if(allowed==1){
			deleteBoard();
			delete []undoBoard;
			setBoardRow(testA1);
			setBoardColomn(testA2);
			resizeBoard();
			undoBoard=new Cell[totalIndex];
			type=testB;
			gamer=testC;
			totalIndex=size;
			for(i=0;i<totalIndex;++i){
				int rowVal;
				int intColomn=tempColomn[i]-'A';
				if(i%2==0)		assignToBoard(rowVal,intColomn,'X');
				else			assignToBoard(rowVal,intColomn,'O');
				gameBoard[rowVal][intColomn].setRow(rowVal);
				gameBoard[rowVal][intColomn].setColomn(tempColomn[i]);
				undoBoard[i].setRow(rowVal);
				undoBoard[i].setColomn(tempColomn[i]);
				if(i%2==0)		gameBoard[rowVal][intColomn].setPlayer('X');
				else			gameBoard[rowVal][intColomn].setPlayer('O');
				if(i%2==0)	undoBoard[i].setPlayer('X');
				else	undoBoard[i].setPlayer('O');
			}

			result=0;
		}
		else	result=-1;


		delete []tempColomn;	

		loadFile.close();

		return result;

	}

	int ConnectFourPlusUndo::saveCurrentGame(const char filename[],char gamer,char type)const{

		ofstream saveFile;
		int result=0;

		saveFile.open(filename);	
	
		if(saveFile.fail()){
			cerr << "File is not be found!\n";
			result=-1;
		}
		else{
			saveFile << getBoardRow() << endl;
			saveFile << getBoardColomn() << endl;
			saveFile << type << endl;
			saveFile << gamer << endl;
			saveFile << totalIndex << endl;
			for(int i=0;i<totalIndex;++i){
				saveFile << undoBoard[i].getColomn();
				saveFile << endl;
			}
		}

		saveFile.close();

		return result;
	}

}

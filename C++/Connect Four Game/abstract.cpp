#include "abstract.h"

namespace abstractKomut{

	/*-----------------------------CONSTRUCTORS---------------------------------*/

	ConnectFourAbstract::ConnectFourAbstract():boardRow(5),boardColomn(5){

		resizeBoard();

	}

	ConnectFourAbstract::ConnectFourAbstract(int rowSize,int colomnSize):boardRow(rowSize),boardColomn(colomnSize){

		resizeBoard();

	}

	/*----------------------------------And Big Threes---------------------------*/

	/*	  Destructor		*/
	ConnectFourAbstract::~ConnectFourAbstract(){

		deleteBoard();

	}

	/*	Copy Constructor	*/
	ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& copy){

		boardRow=copy.getBoardRow();
		boardColomn=copy.getBoardColomn();

		gameBoard=new Cell*[boardRow];
		for(int i=0;i<boardRow;++i)
			gameBoard[i]=new Cell[boardColomn];

		for(int i=0;i<boardRow;++i){
			for(int j=0;j<boardColomn;++j){
				gameBoard[i][j]=copy.gameBoard[i][j];	
			}
		}
	}

	/*	Assignment Operator	*/
	ConnectFourAbstract& ConnectFourAbstract::operator = (const ConnectFourAbstract& assign){

		if(this==&assign){
			return *this;
		}
		else{
			deleteBoard();
			boardRow=assign.getBoardRow();
			boardColomn= assign.getBoardColomn();
			resizeBoard();
			for(int i=0;i<boardRow;++i){
				for(int j=0;j<boardColomn;++j){
					gameBoard[i][j]=assign.gameBoard[i][j];
				}
			}
			return* this;
		}
	}

	/*-------------------Constructor Helper Functions---------------------------*/

	/*	Constructor's tests for size values	*/
	void ConnectFourAbstract::testInput()const{

		if(boardRow<4 || boardColomn<4){
			cerr << "Invalid value. Size is least from 4. Process is fail." << endl;
			exit(0);
		}
	}

	/* Constructors with no parameter or two integers paramater is used it */
	void ConnectFourAbstract::initBoard()const{

		for(int i=0;i<boardRow;++i){
			for(int j=0;j<boardColomn;++j){
				gameBoard[i][j].setRow(i);
				gameBoard[i][j].setColomn('A'+j);
				gameBoard[i][j].setPlayer('.');
			}
		}
	}


	/*--------------------------Creating And Delete------------------------------*/

	void ConnectFourAbstract::resizeBoard(){

		testInput();
		gameBoard=new Cell*[boardRow];
		for(int i=0;i<boardRow;++i)
			gameBoard[i]=new Cell[boardColomn];
		initBoard();

	}


	void ConnectFourAbstract::deleteBoard(){
		for(int i=0;i<boardRow;++i)
			delete[] gameBoard[i];
		delete[] gameBoard;
	}


	/*-----------------------------Setters and Getters--------------------------*/

	void ConnectFourAbstract::setBoardRow(int rowValue){
		boardRow=rowValue;
	}

	void ConnectFourAbstract::setBoardColomn(int colomnValue){
		boardColomn=colomnValue;
	}

	int ConnectFourAbstract::getBoardRow()const{
		return boardRow;
	}

	int ConnectFourAbstract::getBoardColomn()const{
		return boardColomn;
	}

	/*------------------------------Play Functions-----------------------------*/

	/* Game from file with command line.	*/
	void ConnectFourAbstract::playGame(){

	 	string line;
		string temp[BUFF_SIZE];

		cout << "Game is ready for you." << endl;


		deleteBoard();

		getline(cin,line);
		sscanf(line.c_str(),"%d",&boardRow);
		getline(cin,line);
		sscanf(line.c_str(),"%d",&boardColomn);

		cout << "Row Size = " << getBoardRow() << endl;
		cout << "Colomn Size = " << getBoardColomn() << endl;

		resizeBoard();

		int count=0;
		while(cin){       
			if(getline(cin,line)){
				temp[count]=line;
			}
			count++;
		}

		if(strcmp("P",temp[0].c_str())==0){
			playWithUser(temp,count-1);
		}
		else if(strcmp("C",temp[0].c_str())==0){
			playWithComputer(temp,count-1);
		}
		else{
			cerr << "Invalid Game Option" << endl;
			exit(0);
		}
	}

	/*-------------Functions for File Processes for this assignment-------------*/

	/* One game mode (P) type from file with command line.	*/
	void ConnectFourAbstract::playWithUser(string moves[],int moveSize,int count){

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
				else if(legal==-1)	
					cerr << "You enter a character for colomn or command(LOAD or SAVE)." << endl;
				index++;
			if(index==moveSize && legal!=0)	late=1;
			}while(legal!=0 && index<moveSize);
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

	/* One game mode (C) type from file with command line.	*/
	void ConnectFourAbstract::playWithComputer(string moves[],int moveSize,int count){

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
		int late=0;

		do{
			if(count%2==0 || queue%2==0){
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
							cout << "User: " << input << endl;
						}
					}
					else if(strlen(copy)>4){
						if(strncmp("LOAD",copy,4)==0){
							legal=1;
							strcpy(filename,&copy[5]);	
							cout << filename << endl;
						}
						else if(strncmp("SAVE",copy,4)==0){
							legal=2;
							strcpy(filename,&copy[5]);
							cout << filename << endl;
						}
						else legal=-1;
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
					else if(legal==-1)
						cerr << "You enter a character for colomn or command(LOAD or SAVE)." << endl;
					if(legal!=0) helper--;
					index++;
					if(index==moveSize && legal!=0)	late=1;
				}while(legal!=0 && index<moveSize);
				if(late==0){
					gamer='X';
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

	/*------------------------Play Functions for one step-----------------------*/

	int ConnectFourAbstract::play(){
		char input;
		int intVal;
		int rowVal;
	
		moveOfComputer(intVal);
		input='A'+intVal;
		assignToBoard(rowVal,intVal,'O');
		cout << "Computer = " << input << endl;
		int status=gameStatus(rowVal,intVal);
		int result;
	
		return status;
	}


	void ConnectFourAbstract::play(Cell& current){
		int rowValue;
		int colomnValue = (current.getColomn()-'A');
		assignToBoard(rowValue,colomnValue,current.getPlayer());
		current.setRow(rowValue);
	}

	/*-------------------------Keyboard for previous assignments---------------*/

	/*	It performs commands to play against the user . */
	void ConnectFourAbstract::playWithUser(int count){

		char input;
		int decision;
		char filename[TEMP_SIZE];
		char gamer;	
		char type;
		int  row,colomn;
		int condition=0;
		int returnValue;
		int status=0;

		do{
			do{
				status=0;
					do{
						decision=getInputs(input,filename);
						if(decision==1){	// LOAD 
							if(loadFromFile(filename,gamer,type)==0){
								if(gamer=='X')	count=0;
								else	count=1;
								displayBoard();
								cout << "Current Player= " << gamer << endl;
							}
							else{
								cerr << "Process is fail.Current Game will be continued." << endl;
								if(gamer=='X')	count=1;
								else	count=0;
							}	
						}
						else if(decision==2){	// SAVE 
							if(count%2==0)	gamer='X';
							else			gamer='O';
							if(saveCurrentGame(filename,gamer,'P')==0)
								cout << "Game was be saved." << endl;
						}
						else if(decision==-1)	
							cerr << "You should enter a character for column or command(LOAD or SAVE filename)." << endl;
					}while(decision==-1);
				if(decision==0 && legalPosition(input-('a'-'A'))==0){
					status=1;
					cerr << "This column is full or invalid." << endl;
				}
			}while(status==1);
			if(decision==0){
				if(count%2==0)	gamer='X';		// USER1
				else			gamer='O';		// USER2
				colomn=input-'a';
				assignToBoard(row,colomn,gamer);
				returnValue=gameStatus(row,colomn);
				if(returnValue==1 || returnValue==2)	condition=1;
				if(condition==0)	displayBoard();
				if(condition==1 && returnValue==1){
					if(count%2==0)
						cout << "The player1 won the game." << endl;	
					else
						cout << "The player2 won the game." << endl;	
				}	
				else if(condition==1 && returnValue==2){
					cout << "The game ended in a draw." << endl;	
				}
				count++;
			}
		}while(condition==0);
		displayBoard();
	}

	/*	It performs commands to play against the computer. */
	void ConnectFourAbstract::playWithComputer(int count){

		char input;
		char filename[TEMP_SIZE];
		char gamer;
		int row,colomn;	
		int condition=0;
		int returnValue;
		int decision;
		char step;
		char type;
		int status=0;

		do{
			if(count%2==1){
				gamer='O';			// COMPUTER
				moveOfComputer(colomn);
				step='A'+colomn;
				decision=0;		
			}
			else{
				do{	
					status=0;
					do{
						decision=getInputs(input,filename);
						if(decision==1){	// LOAD
							if(loadFromFile(filename,gamer,type)==0){
								if(gamer=='X')	count=0;
								else	count=1;
								displayBoard();
								cout << "Current Player= " << gamer << endl;
							}
							else{
								cerr << "Process is fail.Current Game will be continued." << endl;
								count=0;
							}	
						}					
						else if(decision==2){	// SAVE
							if(saveCurrentGame(filename,'X','C')==0)
								cout << "Game was be saved." << endl;
							count=0;				
						}
						else if(decision==-1)
							cerr << "You should enter a character for column or command(LOAD or SAVE filename)." << endl;
					}while(decision==-1);
					if(decision==0 && legalPosition(input-('a'-'A'))==0){
						status=1;
						cerr << "This column is full or invalid." << endl;
					}
				}while(status==1);
				gamer='X';			// USER
				colomn=input-'a';	
			}
			if(decision==0){
				assignToBoard(row,colomn,gamer);
				returnValue=gameStatus(row,colomn);
				if(returnValue==1 || returnValue==2)	condition=1;	
				if(condition==0)	displayBoard();
				if(condition==1 && returnValue==1){
					if(count%2==0)
						cout << "The player won the game." << endl;	
					else
						cout << "The computer won the game." << endl;	
				}
				else if(condition==1 && returnValue==2){
					cout << "The game ended in a draw." << endl << endl;	
				}	
				count++;
			}
		}while(condition==0);
		displayBoard();	
	}

	/* It takes input or command from user.	*/
	int 
	ConnectFourAbstract::getInputs(char &input,char filename[]){

		int i;
		char str[TEMP_SIZE];
		int status=0;
		int result;

		for(i=0;status==0;){
			cin.get(input);
			if(input=='\n')	status=1;
			else if(input==' ' || input=='\t');
			else str[i++]=input;
		}
		str[i]='\0';

		if(strlen(str)==1){
			input=str[0];
			if(input>='A' && input<='Z')	input=input+('a'-'A');
			result=0;
		}
		else if(strlen(str)>=4){
			if(strncmp(str,"LOAD",4)==0){
				result=1;
			}
			else if(strncmp(str,"SAVE",4)==0){
				result=2;
			}
			else	result=-1;
			if(result==1 || result==2){
				strcpy(filename,&str[4]);
			}
		}
		else	result=-1;
	
		return result;

	}

	/*-----------------LOAD AND SAVE COMMANDS FOR DIAG AND PLUS GAMES---------------*/

	/*	(LOAD command is realised) This function loads another game from a file that has a name. */
	int ConnectFourAbstract::loadFromFile(const char filename[],char &gamer,char &type){

		char **tempBoard;
		int testA1,testA2;
		int i,j;	
		char test1[TEMP_SIZE],test2[TEMP_SIZE];
		ifstream loadFile;
		auto chr='a';				/* Auto Usage */
		int b=3;					/* To Show useage of decltype */
		decltype(b+2) result;		/* Decltype Usage */
		int allowed=0;
		char testB,testC;

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
						tempBoard=new char*[testA1];
						for(int k=0;k<testA1;++k)
							tempBoard[k]=new char[testA2];
					}
					else if(line>=4){
						i++;
						j=0;
					}
					line++;
				}
				else{
					if(line==0)			test1[count++]=chr;
					else if(line==1)	test2[count++]=chr;
					else if(line==2)	testB=chr;
					else if(line==3)	testC=chr;
					else				tempBoard[i][j++]=chr;
				}
			}
		}

		if((testB=='P' || testB=='C') && (testC=='X' || testC=='O'))
		allowed=1;
		else	allowed=0;

		if(allowed==1){
			delete []gameBoard;
			boardRow=testA1;
			boardColomn=testA2;
			gameBoard=new Cell*[boardRow];
			for(j=0;j<boardRow;++j)
				gameBoard[j]=new Cell[boardColomn];
			type=testB;
			gamer=testC;
			for(i=0;i<boardRow;++i){
				for(j=0;j<boardColomn;++j){
					gameBoard[i][j].setRow(i);
					gameBoard[i][j].setColomn('A'+j);
					gameBoard[i][j].setPlayer(tempBoard[i][j]);
				}
			}
			result=0;
			delete []tempBoard;	
		}
		else	result=-1;

		loadFile.close();

		return result;

	}

	/*	(SAVE command is realised) This function saves current game to a file that has a name. */
	int ConnectFourAbstract::saveCurrentGame(const char filename[],char gamer,char type)const{

		ofstream saveFile;
		int result=0;

		saveFile.open(filename);	
	
		if(saveFile.fail()){
			cerr << "File is not be found!\n";
			result=-1;
		}
		else{
			saveFile << boardRow << endl;
			saveFile << boardColomn << endl;
			saveFile << type << endl;
			saveFile << gamer << endl;
			for(int i=0;i<boardRow;++i){
				for(int j=0;j<boardColomn;++j){
					saveFile << gameBoard[i][j].getPlayer();
				}
				saveFile << endl;
			}
		}

		saveFile.close();

		return result;

	}

	/*-----------------------------Computer Logic-------------------------------*/

	/*	It supplies the computer player to make its basic moves. */
	void ConnectFourAbstract::moveOfComputer(int &colomn){

		int i,j;
		int status;
		int *row=new int[boardColomn];

		for(i=0;i<boardColomn;++i){
			for(j=0,status=0;j<boardRow && status==0;++j){
				if(gameBoard[j][i].getPlayer()!='.' && gameBoard[j][i].getPlayer()!=' ')	status=1;
			}
			if(status==1)	row[i]=j-1;
			else 			row[i]=j;
		}

		if(searchFourList(row,colomn,'O')==0){
			if(blockEnemyList(row,colomn,'X')==0){
				makeList(row,colomn,'O');
			}
		}

		delete row;

	}

	/*------------------------------Game Statements----------------------------*/

	void ConnectFourAbstract::displayBoard()const{

		char chr;
		/*******************/
		cout << "  ";
		for(int i=0;i<boardColomn;++i){
			chr='A'+i;
			cout << chr << " ";
		}
		cout << endl;
		/*******************/
		cout << "  ";
		for(int i=0;i<boardColomn;++i)
			cout << '_' << " ";
		cout << endl;
		/*******************/
		for(int i=0;i<boardRow;++i){
			cout << " " << '|'; 	
			for(int j=0;j<boardColomn;++j){
				cout << gameBoard[i][j].getPlayer();
				if(j!=boardColomn-1)	cout << " ";
			}
			cout << '|'; 
			cout << endl;
		}
		/*******************/
		cout << endl;
	}

	/*	Move is legal?	*/
	int ConnectFourAbstract::legalPosition(char input)const{

		int result=0;
		char maxSize='A'+boardColomn;

		int count=0;
		while(count<boardRow && gameBoard[count][input-'A'].getPlayer()==' ')
			count++;
		while(count<boardRow && gameBoard[count][input-'A'].getPlayer()=='.')	
			count++;

		if(input<maxSize && input>='A'){	
			result=1;
		}
		if(count==0){
			if(gameBoard[0][input-'A'].getPlayer()!='.')	result=0;
		}
		else{
			if(gameBoard[count-1][input-'A'].getPlayer()!='.')	result=0;
		}

		return result;
	}

	/*	Input is assigned to a cell of board.	*/
	void ConnectFourAbstract::assignToBoard(int &row,int colomn,char gamer){

		int count=0;
		int index;

		while(count<boardRow && 
		(gameBoard[count][colomn].getPlayer()=='.' || gameBoard[count][colomn].getPlayer()==' ')){	
			count++;
		}
		if(count>0 && gameBoard[count-1][colomn].getPlayer()=='.'){
			gameBoard[count-1][colomn].setPlayer(count-1);
			gameBoard[count-1][colomn].setPlayer(colomn);
			gameBoard[count-1][colomn].setPlayer(gamer);	
			row=count-1;
		}
	}

	/*-----------FOR PREVIOUS ASSIGNMENTS(NOT CURRENT) RETURN FUNCTION-----------*/

	void startingToGame(ConnectFourAbstract& game1,ConnectFourAbstract& game2){

		char type;
		char mode;
		int status;
	
		cout << "P (plus game) or D (diag game) chose one of them" << endl;
		do{	
			status=0;
			if(!(cin >> mode)){
				cin.clear();
				cin.ignore(10000,'\n');
				status=1;
				cerr << "Game mode is can be letter(P,D) ";
			}		
			if(mode!='P' && mode!='D'){
				 status=1;	
				cerr << "Game mode is can be letter(P,D) ";
			}
		}while(status==1);

		cout << "Game type is choosen " << endl;
		do{	
			status=0;
			cerr << "Game type should be C(pvc) or P(pvp)  " << endl;
			if(!(cin >> type)){
				cin.clear();
				cin.ignore(10000,'\n');
				status=1;
			}		
			if(!((type=='C' || type=='c') || (type=='P' || type=='p')))	status=1;
		}while(status==1);

		if(mode=='P'){
			if(type=='C' || type =='c'){
				game1.displayBoard();
				game1.playWithComputer();	/* Default Argument */	
			}
			else if(type=='P' || type=='p'){
				game1.displayBoard();
				game1.playWithUser();		/* Default Argument */
			}
		}

		else if(mode=='D'){
			if(type=='C' || type =='c'){
				game2.displayBoard();
				game2.playWithComputer();	/* Default Argument */	
			}
			else if(type=='P' || type=='p'){
				game2.displayBoard();
				game2.playWithUser();		/* Default Argument */
			}
		}
	
	}

}

#include <fstream>
#include <cstring>
#include <string>
#include "cell.h"
#define TEMP_SIZE 50
#define BUFF_SIZE 1024

#ifndef ABSTRACT_H
#define ABSTRACT_H

using namespace cellKomut;

namespace abstractKomut{

	class ConnectFourAbstract{
		public:
			// Big Threes and Constructors
			ConnectFourAbstract();
			ConnectFourAbstract(int rowSize,int colomnSize);
			~ConnectFourAbstract();
			ConnectFourAbstract(const ConnectFourAbstract& copy);
			ConnectFourAbstract& operator = (const ConnectFourAbstract& assign);
			//The friend function used to read inputs from keyboard in previous assignments.
			friend void startingToGame(ConnectFourAbstract& game1,ConnectFourAbstract& game2,ConnectFourAbstract& game3);
			// Starting Game Functions
			void playGame();
			// Current Board is displayed
			void displayBoard()const;
			// Setters and Getters
			void setBoardRow(int rowValue);
			void setBoardColomn(int colomnValue);
			int getBoardRow()const;
			int getBoardColomn()const;
			//	These functions used to read inputs from keyboard in previous assignments
			void playWithComputer(int count=0);
			void playWithUser(int count=0);
		protected:
			//	Testing and creating functions
			void resizeBoard();
			void testInput()const;
			void initBoard()const;
			// Deleting locations
			void deleteBoard();
			// virtual functions for plus and diag games
			virtual int gameStatus(int rowValue,int colomnValue)=0;
			virtual int searchFourList(const int* row,int &colomnValue,char gamer)=0;
			virtual int blockEnemyList(const int* row,int &colomnValue,char gamer)=0;
			virtual void makeList(const int* row,int &colomnValue,char gamer)=0;
			// virtual functions for undo games
			virtual void playWithUser(string moves[],int moveSize,int count=0);
			virtual void playWithComputer(string moves[],int moveSize,int count=0);
			virtual int loadFromFile(const char filename[],char &gamer,char &type);
			virtual int saveCurrentGame(const char filename[],char gamer,char type)const;
			virtual int play();
			virtual void play(Cell& current);
			//	This function used to read inputs from keyboard in previous assignments
			int getInputs(char &input,char filename[]);
			// These function are helpers.
			int legalPosition(char input)const;
			void assignToBoard(int &rowValue,int colomnValue,char gamer);
			void moveOfComputer(int &colomnValue);
			// Cell two dimension array
			Cell** gameBoard;
		private:
			int boardRow;
			int boardColomn;
	};


}


#endif

#include "plus.h"
#ifndef UNDO_H
#define UNDO_H

using namespace plusKomut;

namespace undoKomut{

	class ConnectFourPlusUndo: public ConnectFourPlus{
		public:
			// Constructors
			ConnectFourPlusUndo();
			ConnectFourPlusUndo(int rowSize,int colomnSize);
			// Big Threes
			~ConnectFourPlusUndo();
			ConnectFourPlusUndo& operator = (const ConnectFourPlusUndo& assign);
			ConnectFourPlusUndo(const ConnectFourPlusUndo& value);
			// Play with user or computer
			void playWithUser(string moves[],int moveSize,int count=0);
			void playWithComputer(string moves[],int moveSize,int count=0);
		protected:
			// Capacity updating
			void addCapacity();
			void renew();
			// Play Functions
			int play();	
			void play(Cell& current);
			// Load save undo Functions
			int loadFromFile(const char filename[],char &gamer,char &type);
			int saveCurrentGame(const char filename[],char gamer,char type)const;
			// Undo Functions
			void undoCommand();
			void combineCell(const Cell& value);
		private:
			Cell* undoBoard; // keeps informations about cell
			int totalIndex;	 // undo count
			int capacity;	 // capacity for undo records
	};



}

#endif

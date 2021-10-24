#include <iostream>
#ifndef CELL_H
#define CELL_H

using namespace std;

namespace cellKomut{

	class Cell{
		public:
			// Constructors
			Cell(int rowValue,char colomnValue,char playerValue);
			Cell();
			// Setters and Getters
			int getRow()const;
			char getColomn()const;
			char getPlayer()const;
			void setRow(int variable);
			void setColomn(char variable);
			void setPlayer(char variable);
		private:
			int	row;		/*	row of cell		*/
			char colomn;	/*	colomn of cell	*/
			char player;	/*	player of cell	*/
	};

}

#endif

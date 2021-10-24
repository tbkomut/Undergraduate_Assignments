#include "cell.h"

namespace cellKomut{

	Cell::Cell(int rowValue,char colomnValue,char playerValue):row(rowValue),colomn(colomnValue),player(playerValue)
	{				}

	Cell::Cell():row(0),colomn('A'),player('X')
	{				}

	void Cell::setRow(int variable){
		row=variable;
	}
	void Cell::setColomn(char variable){
		colomn=variable;
	}

	void Cell::setPlayer(char variable){
		player=variable;
	}

	int Cell::getRow()const{ return row; }
	char Cell::getColomn()const{ return colomn; }
	char Cell::getPlayer()const{ return player; }

}

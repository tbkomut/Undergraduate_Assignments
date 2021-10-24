#include "abstract.h"
#ifndef PLUS_H
#define PLUS_H

using namespace abstractKomut;

namespace plusKomut{

	class ConnectFourPlus: public ConnectFourAbstract{
		public:
			// Constructors and Others
			ConnectFourPlus();
			ConnectFourPlus(int rowSize,int colomnSize);
			~ConnectFourPlus();
			ConnectFourPlus(const ConnectFourPlus& value);
		protected:
			// check game end.
			int gameStatus(int rowValue,int colomnValue);
			// computer player uses there.
			int searchFourList(const int* row,int &colomnValue,char gamer);
			int blockEnemyList(const int* row,int &colomnValue,char gamer);
			void makeList(const int* row,int &colomnValue,char gamer);
			// Game end depend on vertical and horizontal control.
			int verticalControl(int rowValue,int colomnValue,int status);
			int horizontalControl(int rowValue,int colomnValue,int status);
	};

}

#endif

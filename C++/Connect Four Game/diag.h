#include "abstract.h"
#ifndef DIAG_H
#define DIAG_H

using namespace abstractKomut;

namespace diagKomut{

	class ConnectFourDiag: public ConnectFourAbstract{
		public:
			// Constructors and Others.
			ConnectFourDiag();
			ConnectFourDiag(int rowSize,int colomnSize);
			~ConnectFourDiag();
			ConnectFourDiag(const ConnectFourDiag& value);
		protected:
			// check game end.
			int gameStatus(int rowValue,int colomnValue);
			// computer player uses there.
			int searchFourList(const int* row,int &colomnValue,char gamer);
			int blockEnemyList(const int* row,int &colomnValue,char gamer);
			void makeList(const int* row,int &colomnValue,char gamer);
			// Game end only diagonal control.
			int diagonalControl(int rowValue,int colomnValue,int status);
	};

}

#endif

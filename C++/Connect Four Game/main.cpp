#include <iostream>
#include "plus.h"
#include "diag.h"
#include "undo.h"

using namespace std;
using namespace plusKomut;
using namespace diagKomut;
using namespace undoKomut;

int
main(){

	string line;
	int row,colomn;
	ConnectFourPlus game1;
	ConnectFourDiag game2;
	ConnectFourPlusUndo game3;

	getline(cin,line);
	if(strcmp("P",line.c_str())==0){
		cout << "Welcome to Plus Game Type" << endl;
		// call playGame for game1 whose type is plus
		game1.playGame();
	}
	else if(strcmp("D",line.c_str())==0){
		cout << "Welcome to Diag Game Type" << endl;
		// call playGame for game1 whose type is diag
		game2.playGame();
	}
	else if(strcmp("U",line.c_str())==0){
		cout << "Welcome to Undo Game Type" << endl;
		// call playGame for game1 whose type is undo
		game3.playGame();
	}
	else{
		cerr << "Game Mode Error! It should be P or D or U." << endl;
		exit(0);
	}

	return 0;
}


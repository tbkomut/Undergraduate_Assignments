all: main.cpp
	 g++ -std=c++11 main.cpp abstract.cpp cell.cpp plus.cpp diag.cpp undo.cpp -o exe
 
clean: 
	 rm -f all *.o exe
	
install: all
	cp all /usr/bin

all: project

project: gtushell.o bunedu.o lsfcommand.o pwdcommand.o catcommand.o wccommand.o
	gcc -o gtushell gtushell.o
	gcc -o bunedu bunedu.o
	gcc -o lsfcommand lsfcommand.o
	gcc -o pwdcommand pwdcommand.o
	gcc -o catcommand catcommand.o
	gcc -o wccommand wccommand.o			

gtushell.o: gtushell.c 
	gcc -c gtushell.c

bunedu.o: bunedu.c 
	gcc -c bunedu.c

lsfcommand.o: lsfcommand.c 
	gcc -c lsfcommand.c

pwdcommand.o: pwdcommand.c 
	gcc -c pwdcommand.c

catcommand.o: catcommand.c 
	gcc -c catcommand.c

wccommand.o: wccommand.c 
	gcc -c wccommand.c

clean:
	rm *.o $(objects) gtushell bunedu lsfcommand pwdcommand catcommand wccommand
				
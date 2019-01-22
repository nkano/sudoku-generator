sudoku.exe : main.o Board.o
	g++ main.o Board.o -o sudoku.exe
	make clean
main.o : main.cpp Board.h
	g++ -c main.cpp
Board.o : Board.cpp Board.h
	g++ -c Board.cpp
clean:
	rm ./*.o 

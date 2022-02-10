board: main.o Board.o
	g++ main.o Board.o -o board

main.o: main.cpp
	g++ -c main.cpp 

Board.o: Board.cpp
	g++ -c Board.cpp

clean:
	rm *.o board
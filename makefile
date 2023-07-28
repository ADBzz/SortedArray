main.exe: main.o
	g++ -o main.exe main.o
	
main.o: main.cpp SortedArray.h
	g++ -c main.cpp -o main.o

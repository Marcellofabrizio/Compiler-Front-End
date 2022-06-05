main: main.o
	g++ -o main main.o

main.o: main.cpp
	g++ -c main.cpp

parser.o: parser.cpp
	g++ -c parser.cpp
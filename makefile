main: main.o
	g++ -o main main.o parser.o

parser.o: parser.o
	g++ -o parser parser.hpp


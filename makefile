main: main.o
	g++ -o main main.cpp parser.o

parser.o: parser.o
	g++ -o parser parser.hpp token.o

token.o: token.o
	g++ -o token token.hpp

main: main.o
	g++ -o main main.o

main.o: main.cpp
	g++ -c main.cpp

parser.o: parser.cpp
	g++ -c parser.cpp

syntatic.o: syntatic.cpp
	g++ -c syntatic.cpp

clean:
	rm ./main && rm ./main.o
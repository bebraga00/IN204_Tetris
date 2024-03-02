all: sfml-app

sfml-app: object.o
	g++ object.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

object.o: main.o tetromino.o parameters.o
	ld -r main.o tetromino.o -o object1.o
	ld -r object1.o parameters.o -o object.o

main.o: main.cpp
	g++ -c main.cpp

tetromino.o: resources/tetromino.cpp
	g++ -c resources/tetromino.cpp

parameters.o: resources/parameters.cpp
	g++ -c resources/parameters.cpp

clean:
	rm -f *.o sfml-app
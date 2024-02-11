all: sfml-app

sfml-app: object.o
	g++ object.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

object.o: main.o tetromino.o
	ld -r main.o tetromino.o -o object.o

main.o: main.cpp
	g++ -c main.cpp

tetromino.o: tetromino.cpp
	g++ -c tetromino.cpp

clean:
	rm -f *.o sfml-app
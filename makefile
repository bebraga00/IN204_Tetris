all: sfml-app

sfml-app: object.o 
	g++ object.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system
	make clean

object.o: main.o tetromino.o server.o client.o
	ld -r main.o tetromino.o -o object1.o
	ld -r object1.o server.o -o object2.o
	ld -r object2.o client.o -o object.o

main.o: main.cpp
	g++ -c main.cpp

tetromino.o: resources/tetromino.cpp
	g++ -c resources/tetromino.cpp

server.o: resources/server.cpp
	g++ -c resources/server.cpp

client.o: resources/client.cpp
	g++ -c resources/client.cpp

clean:
	rm -f *.o
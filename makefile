# Makefile for compiling main.cpp with SFML

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# SFML libraries
CC = g++
CFLAGS = -I"C:\\Users\\hguid\\Documents\\SFML\\SFML-2.6.1\\include" -DSFML_STATIC
LDFLAGS = -L"C:\\Users\\hguid\\Documents\\SFML\\SFML-2.6.1\\lib" -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

SRCS = main.cpp tetromino.cpp
OBJS = $(SRCS:.cpp=.o)

all: main

main: $(OBJS)
	$(CC) $(OBJS) -o main $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del -f $(OBJS) main
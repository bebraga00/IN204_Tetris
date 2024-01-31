# Makefile for compiling main.cpp with SFML

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Target executable
TARGET = app.exe

# Source file
SRC = main.cpp

# Object file
OBJ = main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@ $(SFML_LIBS)

$(OBJ): $(SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

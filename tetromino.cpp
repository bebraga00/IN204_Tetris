#ifndef TETROMINO_CPP
#define TETROMINO_CPP

#include "tetromino.hpp"
#include "globals.hpp"
#include <vector>

// the constructor receives the tetromino shape and initialises its rotation as zero and calls the init_tetromino method
Tetromino::Tetromino(char shape) : rotation(0), shape(shape), tetromino_matrix(init_tetromino(shape)){}

// function that initialises the given tetromino
std::vector<Position> Tetromino::init_tetromino(char shape){
    std::vector<Position> tetromino_return(4);
    switch(shape){
        case 'I':{
            tetromino_return[0] = {1, -1};
            tetromino_return[1] = {0, -1};
            tetromino_return[2] = {-1, -1};
            tetromino_return[3] = {-2, -1};
            return tetromino_return;
        }
        case 'O':{
            tetromino_return[0] = {0, 0};
            tetromino_return[1] = {0, -1};
            tetromino_return[2] = {-1, -1};
            tetromino_return[3] = {-1, 0};
            return tetromino_return;
        }
        case 'T':{
            tetromino_return[0] = {0, 0};
            tetromino_return[1] = {1, 0};
            tetromino_return[2] = {0, -1};
            tetromino_return[3] = {-1, 0};
            return tetromino_return;
        }
        case 'S':{
            tetromino_return[0] = {0, 0};
            tetromino_return[1] = {1, 0};
            tetromino_return[2] = {0, -1};
            tetromino_return[3] = {-1, -1};
            return tetromino_return;
        }
        case 'Z':{
            tetromino_return[0] = {0, 0};
            tetromino_return[1] = {1, -1};
            tetromino_return[2] = {0, -1};
            tetromino_return[3] = {-1, 0};
            return tetromino_return;
        }
        case 'L':{
            tetromino_return[0] = {0, 0};
            tetromino_return[1] = {1, 0};
            tetromino_return[2] = {-1, -1};
            tetromino_return[3] = {-1, 0};
            return tetromino_return;
        }
        case 'J':{
            tetromino_return[0] = {0, 0};
            tetromino_return[1] = {1, 0};
            tetromino_return[2] = {1, -1};
            tetromino_return[3] = {-1, 0};
            return tetromino_return;
        }

    }
    exit(1);
}

std::vector<Position> Tetromino::get_tetromino_matrix(){
    return tetromino_matrix;
}
#endif
#ifndef TETROMINO_CPP
#define TETROMINO_CPP

#include "tetromino.hpp"
#include "globals.hpp"
#include "window.hpp"
#include <vector>

// the constructor receives the tetromino shape and initialises its rotation as zero and calls the init_tetromino method
Tetromino::Tetromino(char shape, int offset) : rotation(0), shape(shape), tetromino_matrix(init_tetromino(shape, offset)){}

// function that initialises the given tetromino
std::vector<Position> Tetromino::init_tetromino(char shape, int offset){
    std::vector<Position> tetromino_return(4);
    switch(shape){
        case 'I':{
            // tetromino_return[0] = {1, -1};
            // tetromino_return[1] = {0, -1};
            // tetromino_return[2] = {-1, -1};
            // tetromino_return[3] = {-2, -1};
            tetromino_return[0] = {3 + offset, 0};
            tetromino_return[1] = {2 + offset, 0};
            tetromino_return[2] = {1 + offset, 0};
            tetromino_return[3] = {0 + offset, 0};
            return tetromino_return;
        }
        case 'O':{
            // tetromino_return[0] = {0, 0};
            // tetromino_return[1] = {0, -1};
            // tetromino_return[2] = {-1, -1};
            // tetromino_return[3] = {-1, 0};
            tetromino_return[0] = {1 + offset, 1};
            tetromino_return[1] = {1 + offset, 0};
            tetromino_return[2] = {0 + offset, 0};
            tetromino_return[3] = {0 + offset, 1};
            return tetromino_return;
        }
        case 'T':{
            // tetromino_return[0] = {0, 0};
            // tetromino_return[1] = {1, 0};
            // tetromino_return[2] = {0, -1};
            // tetromino_return[3] = {-1, 0};
            tetromino_return[0] = {1 + offset, 1};
            tetromino_return[1] = {2 + offset, 1};
            tetromino_return[2] = {1 + offset, 0};
            tetromino_return[3] = {0 + offset, 1};
            return tetromino_return;
        }
        case 'S':{
            // tetromino_return[0] = {0, 0};
            // tetromino_return[1] = {1, 0};
            // tetromino_return[2] = {0, -1};
            // tetromino_return[3] = {-1, -1};
            tetromino_return[0] = {1 + offset, 1};
            tetromino_return[1] = {2 + offset, 1};
            tetromino_return[2] = {1 + offset, 0};
            tetromino_return[3] = {0 + offset, 0};
            return tetromino_return;
        }
        case 'Z':{
            // tetromino_return[0] = {0, 0};
            // tetromino_return[1] = {1, -1};
            // tetromino_return[2] = {0, -1};
            // tetromino_return[3] = {-1, 0};
            tetromino_return[0] = {1 + offset, 1};
            tetromino_return[1] = {2 + offset, 0};
            tetromino_return[2] = {1 + offset, 0};
            tetromino_return[3] = {0 + offset, 1};
            return tetromino_return;
        }
        case 'L':{
            // tetromino_return[0] = {0, 0};
            // tetromino_return[1] = {1, 0};
            // tetromino_return[2] = {-1, -1};
            // tetromino_return[3] = {-1, 0};
            tetromino_return[0] = {1 + offset, 1};
            tetromino_return[1] = {2 + offset, 1};
            tetromino_return[2] = {0 + offset, 0};
            tetromino_return[3] = {0 + offset, 1};
            return tetromino_return;
        }
        case 'J':{
            // tetromino_return[0] = {0, 0};
            // tetromino_return[1] = {1, 0};
            // tetromino_return[2] = {1, -1};
            // tetromino_return[3] = {-1, 0};
            tetromino_return[0] = {1 + offset, 1};
            tetromino_return[1] = {2 + offset, 1};
            tetromino_return[2] = {2 + offset, 0};
            tetromino_return[3] = {0 + offset, 1};
            return tetromino_return;
        }

    }
    exit(1);
}

char Tetromino::get_shape(){
    return this->shape;
}

std::vector<Position> Tetromino::get_tetromino_matrix(){
    return tetromino_matrix;
}

bool Tetromino::move_down(const std::vector<std::vector<unsigned char>>& game_matrix){
    for(Position& mino : this->tetromino_matrix){
        if(WINDOW_HEIGHT == abs(mino.y) + 1){
            return false;
        }
        if(game_matrix[mino.x][abs(mino.y) + 1]){
            return false;
        }
    }

    for(Position& mino : this->tetromino_matrix){
        mino.y++;
    }

    return true;
}

void Tetromino::move_left(const std::vector<std::vector<unsigned char>>& game_matrix){
    for(Position& mino : this->tetromino_matrix){
        if(mino.x - 1 < 0){
            return;
        }
        if(game_matrix[mino.x - 1][mino.y] > 0){
            return;
        }
    }
    for(Position& mino : this->tetromino_matrix){
        mino.x--;
    }
}

void Tetromino::move_right(const std::vector<std::vector<unsigned char>>& game_matrix){
    for(Position& mino : this->tetromino_matrix){
        if(mino.x + 1 == WINDOW_WIDTH){
            return;
        }
        if(game_matrix[mino.x + 1][mino.y] > 0){
            return;
        }
    }
    for(Position& mino : this->tetromino_matrix){
        mino.x++;
    }
}

#endif
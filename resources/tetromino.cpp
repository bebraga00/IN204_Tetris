#ifndef TETROMINO_CPP
#define TETROMINO_CPP

#include "../headers/tetromino.hpp"
#include "../headers/globals.hpp"
#include "../headers/parameters.hpp"
#include <vector>
#include <stdio.h>
#include <iostream>

// the constructor receives the tetromino shape and initialises its rotation as zero and calls the init_tetromino method
Tetromino::Tetromino(char shape, int offset) : rotation(0), shape(shape), tetromino_matrix(init_tetromino(shape, offset)){}

// function that initialises the given tetromino
std::vector<Position> Tetromino::init_tetromino(char shape, int offset){
    std::vector<Position> tetromino_return(4);
    switch(shape){
        case 'I':{
            tetromino_return[0] = {3 + offset, 0};
            tetromino_return[1] = {2 + offset, 0};
            tetromino_return[2] = {1 + offset, 0};
            tetromino_return[3] = {0 + offset, 0};
            return tetromino_return;
        }
        case 'O':{
            tetromino_return[0] = {1 + offset, 1};
            tetromino_return[1] = {1 + offset, 0};
            tetromino_return[2] = {0 + offset, 0};
            tetromino_return[3] = {0 + offset, 1};
            return tetromino_return;
        }
        case 'T':{
            tetromino_return[0] = {1 + offset, 1}; // central piece
            tetromino_return[1] = {2 + offset, 1};
            tetromino_return[2] = {1 + offset, 0};
            tetromino_return[3] = {0 + offset, 1};
            return tetromino_return;
        }
        case 'S':{
            tetromino_return[0] = {1 + offset, 1}; // central piece
            tetromino_return[1] = {2 + offset, 1};
            tetromino_return[2] = {1 + offset, 0};
            tetromino_return[3] = {0 + offset, 0};
            return tetromino_return;
        }
        case 'Z':{
            tetromino_return[0] = {1 + offset, 1}; // central piece
            tetromino_return[1] = {2 + offset, 0};
            tetromino_return[2] = {1 + offset, 0};
            tetromino_return[3] = {0 + offset, 1};
            return tetromino_return;
        }
        case 'L':{
            tetromino_return[0] = {1 + offset, 1}; // central piece
            tetromino_return[1] = {2 + offset, 1};
            tetromino_return[2] = {0 + offset, 0};
            tetromino_return[3] = {0 + offset, 1};
            return tetromino_return;
        }
        case 'J':{
            tetromino_return[0] = {1 + offset, 1}; // central piece
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

void Tetromino::rush_down(const std::vector<std::vector<unsigned char>>& game_matrix){
    while(move_down(game_matrix)){
        continue;
    }
    return;
}

bool Tetromino::reset(char shape, const std::vector<std::vector<unsigned char>>& game_matrix){
    rotation = 0;
    tetromino_matrix = get_tetromino_matrix();
    for(Position& mino: tetromino_matrix)
    {
        if(0 < game_matrix[mino.x][mino.y])
        {
            return 0; //Full matrix, need to restart
        }
    }
            return 1; //Matrix not full
}


void Tetromino::rotate(const std::vector<std::vector<unsigned char>>& game_matrix){
    if(this->get_shape() == 'O'){
        return;
    }else if(this->get_shape() != 'I'){
        std::vector<Position> rotated_tetromino = this->get_tetromino_matrix();
        int delta_x;
        int delta_y;
        for(int i = 1; i < 4; i++){
            // 90 degree clockwise rotation centered around tetromino_matrix[0] 
            delta_x = tetromino_matrix[i].x - tetromino_matrix[0].x;
            delta_y = tetromino_matrix[i].y - tetromino_matrix[0].y;
            // rotation formula: x <- y and y <- -x
            rotated_tetromino[i].x = delta_y + tetromino_matrix[0].x;
            rotated_tetromino[i].y = tetromino_matrix[0].y - delta_x;
            // guarantee we do not exceed the board dimensions
            if(rotated_tetromino[i].y >= WINDOW_HEIGHT){
                return;
            }
        }
        // verify that the tetromino does not not exit the board
        for(Position& mino : rotated_tetromino){
            if(mino.x < 0){
                rotated_tetromino[0].x += 1;
                rotated_tetromino[1].x += 1;
                rotated_tetromino[2].x += 1;
                rotated_tetromino[3].x += 1;
                break;
            }else if(mino.x >= WINDOW_WIDTH - 1){
                rotated_tetromino[0].x -= 1;
                rotated_tetromino[1].x -= 1;
                rotated_tetromino[2].x -= 1;
                rotated_tetromino[3].x -= 1;
                break;
            }
        }
        // verify that there is no other block there
        for(Position& mino : rotated_tetromino){
            if(game_matrix[mino.x][mino.y] != 0){
                return;
            }
        }
        this->tetromino_matrix = rotated_tetromino;
        this->rotation = (this->rotation + 1) % 4;
        return;
    }else{
        // rotations for the 'I' shape done manually
        std::vector<Position> rotated_tetromino = this->get_tetromino_matrix();        
        if(this->rotation == 0){ // from upper horizontal position
            rotated_tetromino[0].x -= 1;
            rotated_tetromino[0].y -= 2;
            rotated_tetromino[1].y -= 1;
            rotated_tetromino[2].x += 1;
            rotated_tetromino[3].x += 2;
            rotated_tetromino[3].y += 1;
        }else if(this->rotation == 1){ // from right vertical position
            rotated_tetromino[0].x -= 2;
            rotated_tetromino[0].y += 1;
            rotated_tetromino[1].x -= 1;
            rotated_tetromino[2].y -= 1;
            rotated_tetromino[3].x += 1;
            rotated_tetromino[3].y -= 2;
        }else if(this->rotation == 2){ // from lower horizontal position
            rotated_tetromino[0].x += 1;
            rotated_tetromino[0].y += 2;
            rotated_tetromino[1].y += 1;
            rotated_tetromino[2].x -= 1;
            rotated_tetromino[3].x -= 2;
            rotated_tetromino[3].y -= 1;
        }else if(this->rotation == 3){ // from left horizontal position
            rotated_tetromino[0].x += 2;
            rotated_tetromino[0].y -= 1;
            rotated_tetromino[1].x += 1;
            rotated_tetromino[2].y += 1;
            rotated_tetromino[3].x -= 1;
            rotated_tetromino[3].y += 2;
        }else{
            exit(1);
        }

        int x_to_subtract = 0;
        for(Position& mino : rotated_tetromino){
            if(mino.y >= WINDOW_HEIGHT or mino.y < 0){
                return;
            }
            // find the maximum value to 
            if(mino.x < 0 && mino.x < x_to_subtract){
                x_to_subtract = mino.x;
            }else if(mino.x >= WINDOW_WIDTH && mino.x - (WINDOW_WIDTH - 1) > x_to_subtract){
                x_to_subtract = mino.x - (WINDOW_WIDTH - 1);
            }
        }
        for(int i = 0; i < 4; i++){
            rotated_tetromino[i].x -= x_to_subtract;
        }
        for(Position& mino : rotated_tetromino){
            if(game_matrix[mino.x][mino.y] != 0){
                return;
            }
        }        
        this->tetromino_matrix = rotated_tetromino;
        this->rotation = (this->rotation + 1) % 4;
        return;
    }
}

void Tetromino::update_matrix(std::vector<std::vector<unsigned char>>& game_matrix){
    for(Position& mino : tetromino_matrix){
        game_matrix[mino.x][mino.y] = this->get_shape();
    }
}

void Tetromino::get_positions_x(char* array){
    array[0] = this->tetromino_matrix[0].x;
    array[1] = this->tetromino_matrix[1].x;
    array[2] = this->tetromino_matrix[2].x;
    array[3] = this->tetromino_matrix[3].x;
}

void Tetromino::get_positions_y(char* array){
    array[0] = this->tetromino_matrix[0].y;
    array[1] = this->tetromino_matrix[1].y;
    array[2] = this->tetromino_matrix[2].y;
    array[3] = this->tetromino_matrix[3].y;
}

#endif
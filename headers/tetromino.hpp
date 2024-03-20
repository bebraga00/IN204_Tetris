#ifndef TETROMINOS_H
#define TETROMINOS_H

#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "globals.hpp"

class Tetromino{
    public: 
        // class constructor
        Tetromino(char shape, int offset);
        // return the shape matrix
        std::vector<Position> init_tetromino(char shape, int offset);
        // return the positions matrix
        std::vector<Position> get_tetromino_matrix();
        // return the shape char
        char get_shape();

        // movement methods
        bool move_down(const std::vector<std::vector<unsigned char>>& game_matrix);
        void move_left(const std::vector<std::vector<unsigned char>>& game_matrix);
        void move_right(const std::vector<std::vector<unsigned char>>& game_matrix);
        void rush_down(const std::vector<std::vector<unsigned char>>& game_matrix);
        void rotate(const std::vector<std::vector<unsigned char>>& game_matrix);

        void get_positions_x(char* array);
        void get_positions_y(char* array);
        
        //reset functio,
        bool reset(char shape, const std::vector<std::vector<unsigned char>>& game_matrix);
        // update the matrix with the current tetromino position
        void update_matrix(std::vector<std::vector<unsigned char>>& game_matrix);

    private:
        char shape;
        int rotation;
        std::vector<Position> tetromino_matrix;
};

#endif 

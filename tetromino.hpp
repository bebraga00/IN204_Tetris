#ifndef TETROMINOS_H
#define TETROMINOS_H

#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "globals.hpp"

// typedef std::vector<std::vector<bool>> MatrixShape;

class Tetromino{
    public: 
        Tetromino(char shape);
        std::vector<Position> init_tetromino(char shape);
        // std::vector<Position> get_tetromino();
        std::vector<Position> get_tetromino_matrix();
    // private:
        char shape;
        int rotation;
        std::vector<Position> tetromino_matrix;


    //     void rotate();
    //     std::vector<Position> get_tetromino();

    //     Tetromino(int t, int o, sf::Vector2f pos);
    //     Tetromino (int t, int o);
    //     Tetromino();
    //     virtual ~Tetromino();

    //     int getTypePiece();
    //     void setTypePiece(int type);
    //     int getOrientation();
    //     void setOrientation(int o);
    //     sf::Vector2f getPosition();
    //     void setPosition(sf::Vector2f pos);

    //     sf::Color getColor();
    //     MatrixShape getMatrixShape();
        
    //     static const bool pieces[7][4][4][4];
    //     static const sf::Color couleurs[7];

    // protected:
    //     void setMatrixShape();

    // private:
    //     int type_piece;
    //     int orientation;
    //     sf::Vector2i position;

    //     sf::Color couleur;

    //     MatrixShape piece;
};

#endif 

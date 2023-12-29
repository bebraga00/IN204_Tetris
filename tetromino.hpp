#ifndef TETROMINOS_H
#define TETROMINOS_H

#include <SFML/System.hpp>
#include <vector>



typedef vector<vector<bool> > MatrixShape;


class Tetromino 
{
    public: 
        Tetromino(int t, int o, sf::vector2i pos );
        Tetromino (int t, int o);
        Tetromino();
        virtual ~Tetromino();

        int getTypePiece();
        void setTypePiece(int type);
        int getOrientation();
        void setOrientation(int o);
        sf::Vector2i getPosition();
        void setPosition(sf::Vector2i pos);

        sf::Color getColor();
        MatrixShape getMatrixShape();
        
        static const bool pieces[7][4][4][4];
        static const sf::Color couleurs[7];

         protected:

        void setMatrixShape();

    private:



        int type_piece;
        int orientation;
        sf::Vector2i position;

        sf::Color couleur;

        MatrixShape piece;
};

#endif 

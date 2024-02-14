#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>

#include"window.hpp"      // window and cell dimensions definitions
#include"colors.hpp"      // RGBA colors definitions
#include"tetromino.hpp"   // blocks definitions
#include"globals.hpp"

int CELL_SIZE = 8;

char get_random_shape(){
    int shape = rand() % 7;
    switch (shape){
    case 0:
        return 'I';
    case 1:
        return 'O';
    case 2:
        return 'T';
    case 3:
        return 'S';
    case 4:
        return 'Z';
    case 5:
        return 'L';
    default:
        return 'J';
    }
    exit(1);
}

sf::Color get_shape_color(char shape){
    switch (shape){
    case 'I':
        return color_I;
    case 'O':
        return color_O;
    case 'T':
        return color_T;
    case 'S':
        return color_S;
    case 'Z':
        return color_Z;
    case 'L':
        return color_L;
    default:
        return color_J;
    }
    exit(1);
}

int main(){
    // define window dimensions, name and view
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH * PIXELS_PER_CELL * WINDOW_RESIZE, WINDOW_HEIGHT * PIXELS_PER_CELL * WINDOW_RESIZE), "Tetris v1.0");
    window.setView(sf::View(sf::FloatRect(0, 0, PIXELS_PER_CELL * WINDOW_WIDTH, CELL_SIZE * WINDOW_HEIGHT)));       

    srand(time(NULL));

    std::vector<std::vector<unsigned char>> matrix(WINDOW_WIDTH, std::vector<unsigned char>(WINDOW_HEIGHT));

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // fill the window
        sf::RectangleShape cell(sf::Vector2f(PIXELS_PER_CELL - 1, PIXELS_PER_CELL - 1));
        
        window.clear();

        for(int i = 0; i < WINDOW_WIDTH; i++){
            for(int j = 0; j < WINDOW_HEIGHT; j++){
                cell.setPosition(PIXELS_PER_CELL * i, PIXELS_PER_CELL * j);
                cell.setFillColor(grey_background);
                window.draw(cell);
            }
        }

        // MODIFIER
        char shape_actuel = get_random_shape();
        cell.setFillColor(get_shape_color(shape_actuel));
        Tetromino actuel(shape_actuel);
        for (Position& mino : actuel.get_tetromino_matrix()){
            printf("%c", actuel.shape);
            printf("(%d, %d)", mino.x, mino.y);
            cell.setPosition((mino.x + 3) * PIXELS_PER_CELL, (mino.y + 3) * PIXELS_PER_CELL);
            window.draw(cell);
        }
        printf("\n");
        window.display();
    }

    return 0;
}
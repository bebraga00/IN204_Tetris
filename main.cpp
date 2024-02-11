#include <SFML/Graphics.hpp>

#include"window.hpp"      // window and cell dimensions definitions
#include"colors.hpp"      // RGBA colors definitions
#include"tetromino.hpp"   // blocks definitions
#include"globals.hpp"

int CELL_SIZE = 8;

int main(){
    // define window dimensions, name and view
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH * PIXELS_PER_CELL * WINDOW_RESIZE, WINDOW_HEIGHT * PIXELS_PER_CELL * WINDOW_RESIZE), "Tetris v1.0");
    window.setView(sf::View(sf::FloatRect(0, 0, 2 * PIXELS_PER_CELL * WINDOW_WIDTH, CELL_SIZE * WINDOW_HEIGHT)));

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
        char shape_actuel = 'O';
        cell.setFillColor(color_O);
        Tetromino actuel(shape_actuel);
        for (Position& mino : actuel.get_tetromino_matrix()){
            cell.setPosition(mino.x * PIXELS_PER_CELL, mino.y * PIXELS_PER_CELL);
            printf("%d, %d\n", mino.x, mino.y);
            window.draw(cell);
        }
        window.display();
    }

    return 0;
}
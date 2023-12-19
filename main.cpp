#include <SFML/Graphics.hpp>

#include"window.hpp" // window and cell dimensions definition
#include"colors.hpp" // RGBA colors definitions

int main(){
    // define window dimensions, name and view
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH * PIXELS_PER_CELL * WINDOW_RESIZE, WINDOW_HEIGHT * PIXELS_PER_CELL * WINDOW_RESIZE), "Tetris v1.0");
    window.setView(sf::View(sf::FloatRect(0, 0, PIXELS_PER_CELL * WINDOW_WIDTH, PIXELS_PER_CELL * WINDOW_HEIGHT)));

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // fill the window
        sf::RectangleShape cell(sf::Vector2f(PIXELS_PER_CELL - 1, PIXELS_PER_CELL - 1));
        cell.setFillColor(grey_background);



        window.clear();

        for(int i = 0; i < WINDOW_WIDTH; i++){
            for(int j = 0; j < WINDOW_HEIGHT; j++){
                cell.setPosition(PIXELS_PER_CELL * i, PIXELS_PER_CELL * j);
                window.draw(cell);
            }
        }

        window.display();
    }

    return 0;
}
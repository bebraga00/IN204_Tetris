#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include <math.h>

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
    // the game matrix on which we will write all the information
    std::vector<std::vector<unsigned char>> matrix(WINDOW_WIDTH, std::vector<unsigned char>(WINDOW_HEIGHT));

    // define window dimensions, name and view
    sf::RenderWindow window(sf::VideoMode(2 * WINDOW_WIDTH * PIXELS_PER_CELL * WINDOW_RESIZE, WINDOW_HEIGHT * PIXELS_PER_CELL * WINDOW_RESIZE), "Tetris v1.2");
    window.setView(sf::View(sf::FloatRect(0, 0, 2 * PIXELS_PER_CELL * WINDOW_WIDTH, PIXELS_PER_CELL * WINDOW_HEIGHT)));       

    // the random seed to generate the tetrominos
    srand(time(0));

    // SFML event
    sf::Event event;

    // current falling tetromino
    Tetromino current_tetromino(get_random_shape(), rand() % 7);
    // next tetramino
    Tetromino next_tetromino(get_random_shape(), 0);

    // record the current time
    std::chrono::time_point<std::chrono::steady_clock> previous_time = std::chrono::steady_clock::now();
    unsigned int lag = 0;

    while (window.isOpen()){
        // record the time difference
        unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();
        lag += delta_time;
        previous_time += std::chrono::microseconds(delta_time);

        // if we have surpassed the frame duration, we initiate our operations
        while(lag >= FRAME_DURATION){
            lag -= FRAME_DURATION;

            // close the window
            while (window.pollEvent(event)){
                switch(event.type){
                    case sf::Event::Closed:{
                        window.close();
                        break;
                    }
                    case sf::Event::KeyPressed:{
                        if(event.key.code == sf::Keyboard::Right){
                            current_tetromino.move_right(matrix);
                        }else if(event.key.code == sf::Keyboard::Left){
                            current_tetromino.move_left(matrix);
                        }
                    }
                }
            }
            
            // draw the window with the gray background and the set tetrominos
            sf::RectangleShape cell(sf::Vector2f(PIXELS_PER_CELL - 1, PIXELS_PER_CELL - 1));
            window.clear();
            for(int i = 0; i < WINDOW_WIDTH; i++){
                for(int j = 0; j < WINDOW_HEIGHT; j++){
                    if(matrix[i][j] == 0){
                        cell.setFillColor(grey_background);
                    }else{
                        cell.setFillColor(get_shape_color(matrix[i][j]));
                    }
                    cell.setPosition(PIXELS_PER_CELL * i, PIXELS_PER_CELL * j);
                    window.draw(cell);
                }
            }

            // draw the current tetromino
            cell.setFillColor(get_shape_color(current_tetromino.get_shape()));
            for(Position& mino : current_tetromino.get_tetromino_matrix()){
                cell.setPosition(mino.x * PIXELS_PER_CELL, mino.y * PIXELS_PER_CELL);
                window.draw(cell);
            }

            // draw the next tetromino
            cell.setFillColor(get_shape_color(next_tetromino.get_shape()));
            for(Position& mino : next_tetromino.get_tetromino_matrix()){
                cell.setPosition((mino.x + round(WINDOW_WIDTH * 1.5)) * PIXELS_PER_CELL, (mino.y + round(WINDOW_WIDTH * 0.5)) * PIXELS_PER_CELL);
                window.draw(cell);
            }

            // display the current drawn window
            window.display();
            
            // update the tetromino
            if(not(current_tetromino.move_down(matrix))){
                current_tetromino.update_matrix(matrix);
                current_tetromino = Tetromino(next_tetromino.get_shape(), rand() % 7);
                next_tetromino = Tetromino(get_random_shape(), 0);
            }
        }
    }

    return 0;
}
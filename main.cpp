#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include <math.h>
#include <iostream>

#include "parameters.hpp"      // window and cell dimensions definitions
#include "colors.hpp"          // RGBA colors definitions
#include "tetromino.hpp"       // blocks definitions
#include "globals.hpp"

// get a random char which represents each shape
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

// get the corresponding rgba color for each shape
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

// get the corresponding rgba border color for each shape
sf::Color get_border_color(char shape){
    switch (shape){
    case 'I':
        return color_I_border;
    case 'O':
        return color_O_border;
    case 'T':
        return color_T_border;
    case 'S':
        return color_S_border;
    case 'Z':
        return color_Z_border;
    case 'L':
        return color_L_border;
    default:
        return color_J_border;
    }
    exit(1);
}

// calculate the number of points per round
int calculate_points(int cleared_lines, int level) {
    switch(cleared_lines) {
        case 1: return 40 * (level + 1);
        case 2: return 100 * (level + 1);
        case 3: return 300 * (level + 1);
        case 4: return 1200 * (level + 1);
        default: return 0;
    }
}

void draw_window_matrix(std::vector<std::vector<unsigned char>>& matrix, sf::RenderWindow& window, sf::RectangleShape& cell){
    for(int i = 0; i < WINDOW_WIDTH; i++){
        for(int j = 0; j < WINDOW_HEIGHT; j++){
            if(matrix[i][j] == 0){
                cell.setFillColor(background);
                cell.setOutlineColor(background);
            }else{
                cell.setFillColor(get_shape_color(matrix[i][j]));
                cell.setOutlineColor(get_border_color(matrix[i][j]));
            }
            cell.setPosition(PIXELS_PER_CELL * i, PIXELS_PER_CELL * j);
            window.draw(cell);
        }
    }
}

void draw_current_tetromino(Tetromino& current_tetromino, sf::RenderWindow& window, sf::RectangleShape& cell){
    cell.setFillColor(get_shape_color(current_tetromino.get_shape()));
    cell.setOutlineColor(get_border_color(current_tetromino.get_shape()));
    for(Position& mino : current_tetromino.get_tetromino_matrix()){
        cell.setPosition(mino.x * PIXELS_PER_CELL, mino.y * PIXELS_PER_CELL);
        window.draw(cell);
    }
}

void draw_next_tetromino(Tetromino& next_tetromino, sf::RenderWindow& window, sf::RectangleShape& cell){
    cell.setFillColor(get_shape_color(next_tetromino.get_shape()));
    cell.setOutlineColor(get_border_color(next_tetromino.get_shape()));
    for(Position& mino : next_tetromino.get_tetromino_matrix()){
        cell.setPosition((mino.x + round(WINDOW_WIDTH * 1.5)) * PIXELS_PER_CELL, (mino.y + round(WINDOW_WIDTH * 0.5)) * PIXELS_PER_CELL);
        window.draw(cell);
    }
}

void draw_vertical_line(sf::RenderWindow& window, sf::RectangleShape& cell){
    cell.setFillColor(line);
    cell.setOutlineColor(line_border);
    for(int i = 0; i < WINDOW_HEIGHT; i++){
        cell.setPosition(WINDOW_WIDTH * PIXELS_PER_CELL, PIXELS_PER_CELL * i);
        window.draw(cell);
    }
}

int get_level(int total_lines_cleared){
    return (floor(float(total_lines_cleared) / 10.0));
}

unsigned char get_current_fall_speed(int level){
    if(level >= 29){
        return 1;
    }else{
        return LEVEL_SPEEDS[level];
    }
}

int main(){
    // guarantee we only move once per click
    bool already_moved = false;

    // timer for the falling tetromino
    unsigned char current_fall_speed = START_FALL_SPEED;
    unsigned char fall_timer = 0;
    
    //define the player score
    int score = 0;
    // variable which defines the level
    int total_lines_cleared = 0;

    // the game matrix on which we will write all the information
    std::vector<std::vector<unsigned char>> matrix(WINDOW_WIDTH, std::vector<unsigned char>(WINDOW_HEIGHT));

    // define window dimensions, name and view
    sf::RenderWindow window(sf::VideoMode(2 * WINDOW_WIDTH * PIXELS_PER_CELL * WINDOW_RESIZE, WINDOW_HEIGHT * PIXELS_PER_CELL * WINDOW_RESIZE), "Tetris v1.2");
    window.setView(sf::View(sf::FloatRect(0, 0, 2 * PIXELS_PER_CELL * (WINDOW_WIDTH + 0.5), PIXELS_PER_CELL * (WINDOW_HEIGHT))));       

    // REVIEW FONT RESOLUTION AND BLURRYNESS
    // define the font
    sf::Font font;
    if (!font.loadFromFile("font/PixeloidSans.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        exit(1);
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);     // font size
    text.setFillColor(font_color); // text color
   
    // the random seed to generate the tetrominos
    srand(time(0));

    // SFML event which captures pressed keys
    sf::Event event;

    // current falling tetromino
    Tetromino current_tetromino(get_random_shape(), rand() % 7);
    // next tetromino
    Tetromino next_tetromino(get_random_shape(), 0);

    // record the current time
    std::chrono::time_point<std::chrono::steady_clock> previous_time = std::chrono::steady_clock::now();
    unsigned int lag = 0;

    while(window.isOpen()){
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
                    case (sf::Event::Closed):{
                        window.close();
                        break;
                    }
                    case sf::Event::KeyPressed:{
                        if(not(already_moved)){
                            switch(event.key.code){
                                case(sf::Keyboard::Right):{
                                    already_moved = true;
                                    current_tetromino.move_right(matrix);
                                    break;
                                }
                                case(sf::Keyboard::Left):{
                                    already_moved = true;
                                    current_tetromino.move_left(matrix);
                                    break;
                                }
                                case(sf::Keyboard::Down):{
                                    already_moved = true;
                                    fall_timer = current_fall_speed;
                                    current_tetromino.rush_down(matrix);    
                                    break;
                                }
                                case(sf::Keyboard::Up):{
                                    already_moved = true;
                                    current_tetromino.rotate(matrix);
                                    break;
                                }
                            }    
                            break;
                        }else{
                            break;
                        }
                    }
                    case sf::Event::KeyReleased:{
                        switch(event.key.code){
                            case(sf::Keyboard::Right):{
                                already_moved = false;
                                break;
                            }
                            case(sf::Keyboard::Left):{
                                already_moved = false;
                                break;
                            }
                            case(sf::Keyboard::Down):{
                                already_moved = false;
                                break;
                            }
                            case(sf::Keyboard::Up):{
                                already_moved = false;
                                break;
                            }
                        }
                        break;
                    }
                }
            }

            window.clear();

            // drawing operations
            sf::RectangleShape cell(sf::Vector2f(PIXELS_PER_CELL - 3, PIXELS_PER_CELL - 3));
            cell.setOutlineThickness(1.0);

            // draw the window with the gray background and the set tetrominos
            draw_window_matrix(matrix, window, cell);

            // draw the current falling tetromino
            draw_current_tetromino(current_tetromino, window, cell);

            // draw the next tetromino
            draw_next_tetromino(next_tetromino, window, cell);

            // draw the vertical line separating the board 
            draw_vertical_line(window, cell);

            // display the text score
            text.setPosition(((int(WINDOW_WIDTH * 1.2)) * PIXELS_PER_CELL), ((int(WINDOW_WIDTH * 1.5)) * PIXELS_PER_CELL )); // POSITION
            text.setString("Score: " + std::to_string(score));
            window.draw(text);
            text.setPosition(((int(WINDOW_WIDTH * 1.2)) * PIXELS_PER_CELL), ((int(WINDOW_WIDTH * 1.2)) * PIXELS_PER_CELL ));
            text.setString("Level: " + std::to_string(get_level(total_lines_cleared)));
            window.draw(text);

            window.display();
            
            if(fall_timer == current_fall_speed){
                fall_timer = 0;
                if(not(current_tetromino.move_down(matrix))){
                    current_tetromino.update_matrix(matrix);
                    // Count the lines cleared in this move
                    int cleared_lines = 0;
                    for(unsigned char row = 0; row < WINDOW_HEIGHT; row++){
                        bool clear_line = 1;
                        for(unsigned char col = 0; col < WINDOW_WIDTH; col++){
                            if(matrix[col][row] == 0){
                                clear_line = 0;
                                break;
                            }
                        }
                        if(clear_line == 1){
                            cleared_lines++;
                            for(unsigned char col = 0; col < WINDOW_WIDTH; col++){
                                matrix[col][row] = 0;
                                for(unsigned char upwards_row = row; upwards_row > 0; upwards_row--){
                                    matrix[col][upwards_row] = matrix[col][upwards_row - 1];
                                    matrix[col][upwards_row - 1] = 0;
                                }
                            }                        
                        }
                    }
                    current_tetromino = Tetromino(next_tetromino.get_shape(), rand() % 7);
                    next_tetromino = Tetromino(get_random_shape(), 0);
                    if(current_tetromino.reset(next_tetromino.get_shape(), matrix) == 0){
                        // CREATE GAME OVER SCREEN
                        for(unsigned char i = 0; i< WINDOW_WIDTH; i++){
                            for(unsigned char j = 0; j< WINDOW_HEIGHT; j++){
                                matrix[i][j] = 0;
                            }
                        }
                    }
                    score += calculate_points(cleared_lines, get_level(total_lines_cleared));
                    total_lines_cleared += cleared_lines;

                    current_fall_speed = get_current_fall_speed(get_level(total_lines_cleared));
                }
            }else{
                fall_timer++;
            }           
        }
    }
    return 0;
}
#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include <math.h>
#include <iostream>
#include <fstream>

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

// calculate the current level
int get_level(int total_lines_cleared){
    return (floor(float(total_lines_cleared) / 10.0));
}

// obtain the current fall speed
unsigned char get_current_fall_speed(int level){
    if(level >= 29){
        return 1;
    }else{
        return LEVEL_SPEEDS[level];
    }
}

void draw_window_matrix(std::vector<std::vector<unsigned char>>& matrix, sf::RenderWindow& window, sf::RectangleShape& cell){
    for(int i = 0; i < WINDOW_WIDTH; i++){
        for(int j = 0; j < WINDOW_HEIGHT; j++){
            if(matrix[i][j] == 0){
                cell.setFillColor(sf::Color::Black);
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
        cell.setPosition((mino.x + round(WINDOW_WIDTH * 1.4)) * PIXELS_PER_CELL, (mino.y + round(WINDOW_WIDTH * 1.0)) * PIXELS_PER_CELL);
        window.draw(cell);
    }
}

void draw_preview_tetromino(Tetromino& preview_tetromino, sf::RenderWindow& window, sf::RectangleShape& cell){
    cell.setFillColor(sf::Color(0,0,0,0));
    cell.setOutlineColor(get_border_color(preview_tetromino.get_shape()));
    for(Position& mino : preview_tetromino.get_tetromino_matrix()){
        cell.setPosition(mino.x * PIXELS_PER_CELL, mino.y * PIXELS_PER_CELL);
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

void display_score(sf::Text& text, int score, int high_score, sf::RenderWindow& window){
    text.setPosition(((int(WINDOW_WIDTH * 1.2)) * PIXELS_PER_CELL), ((int(WINDOW_WIDTH * 0.1)) * PIXELS_PER_CELL)); // POSITION
    std::string scoreString = std::to_string(score);
    std::string high_scoreString = std::to_string(high_score);    
    text.setString("HIGH SCORE\n" + std::string(6 - high_scoreString.length(), '0') + high_scoreString + "\nSCORE\n" + std::string(6 - scoreString.length(), '0') + scoreString);
    window.draw(text);
}

void draw_game_over_screen(sf::RenderWindow& window, sf::Text& text, int score, int highscore){
    sf::RectangleShape new_cell(sf::Vector2f(PIXELS_PER_CELL, PIXELS_PER_CELL));
    new_cell.setFillColor(game_over_override);
    new_cell.setOutlineColor(game_over_override);
    
    for(int i = 0; i < (VIEW_HEIGHT / PIXELS_PER_CELL); i++){
        for(int j = 0; j < (VIEW_WIDTH / PIXELS_PER_CELL); j++){
            new_cell.setPosition(i * PIXELS_PER_CELL, j * PIXELS_PER_CELL);
            window.draw(new_cell);
        }
    }

    text.setPosition((int(VIEW_WIDTH * 0.33)), int(VIEW_HEIGHT * 0.5));
    text.setString("GAME OVER");
    window.draw(text);
    display_score(text, score, highscore, window);
    window.display();

    sleep(2.5);
    text.setString("PRESS ANY KEY TO CONTINUE");
    text.setPosition(((int(WINDOW_WIDTH * 0.15)) * PIXELS_PER_CELL), int(VIEW_HEIGHT * 0.6));
    window.draw(text);
    window.display();
}

void display_level(sf::Text& text, int level, sf::RenderWindow& window){
    text.setPosition(((int(WINDOW_WIDTH * 1.2)) * PIXELS_PER_CELL), ((int(WINDOW_WIDTH * 1.6)) * PIXELS_PER_CELL ));
    std::string levelString = std::to_string(level);
    text.setString("LEVEL \n  " + std::string(2 - levelString.length(), '0') + levelString);
    window.draw(text);
}

void display_next_shape_text(sf::Text& text, sf::RenderWindow& window){
    text.setPosition(((int(WINDOW_WIDTH * 1.2)) * PIXELS_PER_CELL), ((int(WINDOW_WIDTH * 0.7)) * PIXELS_PER_CELL ));
    text.setString("NEXT");
    window.draw(text);
}

void save_highscore(int score, int highscore){
    if(score > highscore){
        std::ofstream output_file("highscore.txt");
        if (!output_file.is_open()) {
            std::cerr << "Error: Unable to open the highscore file." << std::endl;
            exit(1); 
        }
        output_file << score; 
        output_file.close();
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
    // define and search the current highscore
    int highscore = 0;
    std::ifstream entry_file("highscore.txt");
    if (!entry_file.is_open()) {
        std::cerr << "Error: Unable to open the highscore file." << std::endl;
        exit(1); 
    }
    entry_file >> highscore; 
    entry_file.close();

    // variable which defines the level
    int total_lines_cleared = 0;

    // the game matrix on which we will write all the information
    std::vector<std::vector<unsigned char>> matrix(WINDOW_WIDTH, std::vector<unsigned char>(WINDOW_HEIGHT));

    // define window dimensions, name and view
    sf::RenderWindow window(sf::VideoMode(2 * WINDOW_WIDTH * PIXELS_PER_CELL * WINDOW_RESIZE, WINDOW_HEIGHT * PIXELS_PER_CELL * WINDOW_RESIZE), "Tetris v1.2");
    window.setView(sf::View(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT)));

    // import the font
    sf::Font font;
    if (!font.loadFromFile("font/Pixel_NES.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        exit(1);
    }
    // ensure font is not blurry
    const_cast<sf::Texture&>(font.getTexture(FONT_SIZE)).setSmooth(false);

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(FONT_SIZE);     // font size
    text.setFillColor(font_color); // text color
   
    // the random seed to generate the tetrominos
    srand(time(0));

    // SFML event which captures pressed keys
    sf::Event event;

    // current falling tetromino
    int offset = rand() % 7;
    Tetromino current_tetromino(get_random_shape(), offset);
    // next tetromino
    Tetromino next_tetromino(get_random_shape(), 0);
    // preview tetromino
    Tetromino preview_tetromino(current_tetromino.get_shape(), offset);
    preview_tetromino.rush_down(matrix);

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

            while (window.pollEvent(event)){
                switch(event.type){
                    // close the window
                    case (sf::Event::Closed):{
                        save_highscore(score, highscore);
                        window.close();
                        break;
                    }
                    // guarantee we only move once when the key is pressed
                    case sf::Event::KeyPressed:{
                        if(not(already_moved)){
                            switch(event.key.code){
                                case(sf::Keyboard::Right):{
                                    already_moved = true;
                                    current_tetromino.move_right(matrix);
                                    preview_tetromino = current_tetromino;
                                    preview_tetromino.rush_down(matrix); 
                                    break;
                                }
                                case(sf::Keyboard::Left):{
                                    already_moved = true;
                                    current_tetromino.move_left(matrix);
                                    preview_tetromino = current_tetromino;
                                    preview_tetromino.rush_down(matrix); 
                                    break;
                                }
                                case(sf::Keyboard::Down):{
                                    already_moved = true;
                                    fall_timer = current_fall_speed; // end the current round
                                    current_tetromino.rush_down(matrix);    
                                    break;
                                }
                                case(sf::Keyboard::Up):{
                                    already_moved = true;
                                    current_tetromino.rotate(matrix);
                                    preview_tetromino = current_tetromino;
                                    preview_tetromino.rush_down(matrix); 
                                    break;
                                }
                            }    
                            break;
                        }else{
                            break;
                        }
                    }
                    // reset the movements 
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

            // draw the preview tetromino
            draw_preview_tetromino(preview_tetromino, window, cell);

            // draw the vertical line separating the board 
            draw_vertical_line(window, cell);

            // display text
            display_score(text, score, highscore, window);
            display_level(text, get_level(total_lines_cleared), window);
            display_next_shape_text(text, window);

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

                    // update for next turn
                    offset = rand() % 7;
                    current_tetromino = Tetromino(next_tetromino.get_shape(), offset);
                    preview_tetromino = Tetromino(current_tetromino.get_shape(), offset);
                    preview_tetromino.rush_down(matrix);
                    next_tetromino = Tetromino(get_random_shape(), 0);
                    score += calculate_points(cleared_lines, get_level(total_lines_cleared));
                    total_lines_cleared += cleared_lines;
                    current_fall_speed = get_current_fall_speed(get_level(total_lines_cleared));

                    // if we can't reset, the game is over
                    if(current_tetromino.reset(next_tetromino.get_shape(), matrix) == 0){
                        save_highscore(score, highscore);
                        draw_game_over_screen(window, text, score, highscore);
                        // detect any key press
                        while(1){
                            window.pollEvent(event);
                            if(event.type == sf::Event::KeyPressed){
                                window.close();
                                break;
                            }else if(event.type == sf::Event::Closed){
                                window.close();
                                break;
                            }   
                        }
                        
                        
                    }
                }
            }else{
                fall_timer++;
            }           
        }
    }
    return 0;
}
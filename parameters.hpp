#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

// level and scoring information taken from https://tetris.fandom.com/wiki/Tetris_(NES,_Nintendo) and https://en.wikipedia.org/wiki/Tetris_(NES_video_game)# 

#include<vector>

// window dimensions
constexpr unsigned int WINDOW_WIDTH       = 10;     // number of columns in tetris matrix
constexpr unsigned int WINDOW_HEIGHT      = 20;     // number of rows in tetris matrix
constexpr unsigned int PIXELS_PER_CELL    = 20;     // how many pixels in one tetris cell
constexpr unsigned int WINDOW_RESIZE      = 2;      // window resize value

// view dimensions
constexpr unsigned int VIEW_WIDTH         = 2 * PIXELS_PER_CELL * (WINDOW_WIDTH + 0.5);
constexpr unsigned int VIEW_HEIGHT        = WINDOW_HEIGHT * PIXELS_PER_CELL;

// timing constants
constexpr unsigned int FRAME_DURATION     = 16667;  // frame duration in microseconds
constexpr unsigned int START_FALL_SPEED   = 48;     // initial fall period in frames

// font size
constexpr unsigned int FONT_SIZE          = 20;

// fall periods per level
constexpr unsigned char LEVEL_SPEEDS[]    = {48,43,38,33,28,23,18,13,8,6,5,5,5,4,4,4,3,3,3,2,2,2,2,2,2,2,2,2,2};

// home screen welcome page design                                                                     TOP LEFT                                                                                         BOTTOM LEFT
constexpr unsigned char welcome_matrix[VIEW_WIDTH / PIXELS_PER_CELL][VIEW_HEIGHT / PIXELS_PER_CELL] =  {{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'I','I','I','I','T'}, 
                                                                                                        {  0,  0,  0,'I','I','I','I',  0,  0,  0,  0,  0,  0,  0,'Z','Z','L','L','T','T'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'Z','Z','L','S','T'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'L','S','S'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'O','O','S'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'O','O','L'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'L','L','L'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'S','S','Z'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'S','S','Z','Z'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'J','J','Z',  0}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'J','L','O','O'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'J','L','O','O'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'L','L','I'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'I','I','I','I','I'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'S','S','I'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'S','S','L','I'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'Z','L','I'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'Z','Z','L','L'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,'T','T','T',  0,  0,  0,  0,'Z','J','J','J'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'T',  0,  0,  0,  0,'S','S','O','O','J'}, 
                                                                                                        {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,'S','S',  0,'O','O',  0}};
//                                                                                                    TOP RIGHT                                                                                         BOTTOM RIGHT
#endif
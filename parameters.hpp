#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

// window dimensions
constexpr unsigned int WINDOW_WIDTH = 10;       // number of columns in tetris matrix
constexpr unsigned int WINDOW_HEIGHT = 20;      // number of rows in tetris matrix
constexpr unsigned int PIXELS_PER_CELL = 20;    // how many pixels in one tetris cell
constexpr unsigned int WINDOW_RESIZE = 2;       // window resize value

// timing constants
constexpr unsigned int FRAME_DURATION = 16667;  // frame duration in microseconds
constexpr unsigned int START_FALL_SPEED = 48;   // initial fall period in frames

// fall periods per level
constexpr unsigned char LEVEL_SPEEDS[] = {48,43,38,33,28,23,18,13,8,6,5,5,5,4,4,4,3,3,3,2,2,2,2,2,2,2,2,2,2};

#endif
#ifndef COLORS_HPP
#define COLORS_HPP

#include <SFML/Graphics.hpp>

// light blue board background
sf::Color background(24,24,36,255);
sf::Color line(120,120,120,255);
sf::Color line_border(50,50,50,255);

// shape colors
sf::Color color_O(0,0,240,255);     // blue
sf::Color color_I(240,0,0,255);     // red
sf::Color color_S(0,240,240,255);   // blue-green
sf::Color color_Z(0,240,0,255);     // green
sf::Color color_L(240,160,0,255);   // orange
sf::Color color_J(240,240,0,255);   // yellow
sf::Color color_T(160,0,240,255);   // purple

// shape border colors (darker)
sf::Color color_O_border(0,0,120,255);
sf::Color color_I_border(120,0,0,255);
sf::Color color_S_border(0,120,120,255);
sf::Color color_Z_border(0,120,0,255);
sf::Color color_L_border(120,80,0,255);
sf::Color color_J_border(120,120,0,255);
sf::Color color_T_border(80,0,120,255);

// font color
sf::Color font_color(255, 255, 255, 255);

// game over 
sf::Color game_over_override(0,0,0,200);

#endif
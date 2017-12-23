#pragma once

#include <string>
#include <iostream>

enum piece_color {RED, BLACK, WHITE, INVALID, NONE};

//struct for a game piece
struct Piece {
	Piece(piece_color, std::string, std::string);
	Piece();
	piece_color c;
	std::string name, display;
};

//declarations for color/string conversions
std::string colorToString(piece_color);
piece_color stringToColor(std::string);
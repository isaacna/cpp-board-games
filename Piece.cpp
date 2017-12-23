#include "stdafx.h"
#include "Piece.h"

using namespace std;

//color to string method
string colorToString(piece_color c) {
	switch (c) {
	case RED:
		return "red";
	case BLACK:
		return "black";
	case WHITE:
		return "white";
	case NONE:
		return "none";
	default:
		return "invalid";
	}
	
}

//string to color method
piece_color stringToColor(string s) { //pass by value
	//to_lowcase(s);
	if (s == "red") {
		return RED;
	}
	else if (s == "black") {
		return BLACK;
	}
	else if (s == "white") {
		return WHITE;
	}
	else if (s == " " || s == "") {
		return NONE;
	}
	else {
		return INVALID;
	}

}

Piece::Piece(piece_color col, string the_name, string the_disp) : c(col), name(the_name), display(the_disp) {}
Piece::Piece() : c(NONE), name(""), display(" ") {}
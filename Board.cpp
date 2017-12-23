#include "stdafx.h"
#include "Board.h"
#include <string>
using namespace std;

//method that prints the board and handles spacing properly based on the index and longest string
int printBoard(const vector<Piece> & pieceV, unsigned width, unsigned height, unsigned max_h) {
	int maxSize = width*height; //max range of the board
	unsigned index = 0;

	unsigned spaces = max_h - 1;
	if (spaces <= 0) {
		spaces = 1;
		max_h++;
	}

	if (pieceV.size() == maxSize) { //test if size of vector matches dimensions of game board
		for (unsigned j = height-1; j > 0; --j) {
			if (j != 1) {
				cout << (j - 1);
			}
			for (unsigned a = 0; a < max_h - to_string(j-1).length(); ++a)
			{
				cout << " ";
			}

			for (unsigned i = 1; i < width; ++i) {
				for (unsigned a = 0; a < to_string(i).length(); ++a) {
				

						cout << " ";
					
				}
				cout << pieceV[(width * (j-1)) + (i)].display;
				
			}
			cout << endl;
		}
		cout << " ";
		for (unsigned i = 0; i < width-1; ++i)
		{
			for (unsigned a = 0; a < spaces; ++a) {
				cout << " ";

			}
			if (i != 0) {
			cout << i;
		}
			
		}
		cout << endl;
		return printSuccess;
	}
	else {
		return printFail;
	}

}
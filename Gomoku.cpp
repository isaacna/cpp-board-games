#include "stdafx.h"
#include "GameBase.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "Enums.h"
#include "Board.h"
#include "Gomoku.h"

using namespace std;

unsigned Gomoku::x_y_toIndex(unsigned x, unsigned y)//this helper method allows us to easily convert x and y coordinates into their location in the pieces array
{
	return (y * width + x);
}

bool Gomoku::done()
{
	//starting corner index of the gomoku board
	int pivotIndex = width + 1;

	//the horizontal and vertical checks compares pieces with the previous piece and returns a win if there are the proper win amount in a row

	//horizontal win check
	for (unsigned int i = pivotIndex; i <= ((pivotIndex) + ((width-2) * width)); i = i + width) {

		unsigned int count = 1;

		for (unsigned int j = i; j < i + (width-1); ++j) {
			if (pieces[j].display != " ") { //disregards completely blank board
				if (pieces[j].display == pieces[j-1].display) { //if matches the comparison value
					++count;
				}
				else {
					count = 1;
				}
				if (count == win_amount) {
					return true;
				}
			}
		}
		
	}
	//going vertically
	for (unsigned int i = pivotIndex; i <= pivotIndex + (height-2); i++) {

		unsigned int count = 1;

		for (unsigned int j = i; j <= (i + (height-2) * height); j = j + height) {
			if (pieces[j].display != " ") { //disregards completely blank board
				if (pieces[j].display == pieces[j - height].display) { //if matches the comparison value
					++count;
				}
				else {
					count = 1;
				}
				if (count == win_amount) {
					return true;
				}
			}
		}

	}
	
	//go to bottom right from top
	unsigned x = 0;
	unsigned start_x = 0;
	unsigned y = 0;
	unsigned start_y = 0;
	

	

	//go to bottom rigth from side

	for (start_y = height -1; start_y > win_amount; --start_y)//change the y coordinate we start at
	{//so we start searching from 1,19 then 1,18 then 1, 17 etc
		unsigned count = 1;
		y = start_y;
		for (x = 1; x < width-1; ++x)//start x at one every time
		{
			if (pieces[x_y_toIndex(x, y)].display != " ")//make sure we don't say someone one by saying the blank match up
			{
				if (pieces[x_y_toIndex(x, y)].display == pieces[x_y_toIndex(x + 1, y - 1)].display)//check if piece is same colour as the one after it (bottom right)
				{
					++count;
				}
				else
				{
					count = 1;//reset when we don't have a match
				}
				if (count == win_amount)//if we have enough matches in a row (win_amount -1 ) then we have a winner
				{
					return true;
				}
				if (y > 1)
				{
					--y;//decrease y for the inner loop
				}
				else
				{
					x = width;//make the inner loop end when our y gets out of bounds if this happens before x gets there
				}
			}
		}
	}

	for (start_x = 1; start_x < width - win_amount - 1; ++start_x)//the logic for this loop is exactly the same as the one above, but we move the starting point along the
	{//top of the square and then go down right instead of going down the side of the square
		unsigned count = 1;
		x = start_x;
		for (y = height - 1; y > 1; --y)
		{
			if (pieces[x_y_toIndex(x, y)].display != " ")
			{
				if (pieces[x_y_toIndex(x, y)].display == pieces[x_y_toIndex(x + 1, y - 1)].display)
				{
					++count;
				}
				else
				{
					count = 1;
				}
				if (count == win_amount)
				{
					return true;
				}
				if (x < width - 1)
				{
					++x;
				}
				else
				{
					y = 0;
				}
			}
		}
	}

	for (start_x = 1; start_x < width - win_amount; ++start_x)//same as above but we go toward the top right instead of toward the bottom right
	{//this one moves the starting point along the bottom
		x = start_x;
		unsigned count = 1;
		for (y = 1; y < height - 1; ++y)
		{
			if (pieces[x_y_toIndex(x, y)].display != " ")
			{
				if (pieces[x_y_toIndex(x, y)].display == pieces[x_y_toIndex(x + 1, y + 1)].display)
				{
					++count;
				}
				else
				{
					count = 1;
				}
				if (count == win_amount)
				{
					return true;
				}
				if (x < width -1)
				{
					++x;
				}
				else
				{
					 y = height;
				}
			}
		}
	}
	for (start_y = 1; start_y < height - win_amount; ++start_y)//same as above but we move the starting point along the bottom
	{
		y = start_y;
		unsigned count = 1;
		for (x = 1; x < width - 1; ++x)
		{
			if (pieces[x_y_toIndex(x, y)].display != " ")
			{
				if (pieces[x_y_toIndex(x, y)].display == pieces[x_y_toIndex(x + 1, y + 1)].display)
				{
					++count;
				}
				else
				{
					count = 1;
				}
				if (count == win_amount)
				{
					return true;
				}
				if (y < y - 1)
				{
					++y;
				}
				else
				{
					x = width;
				}
			}
		}
	}



	return false;
}


/*
The logic of the draw method is to test whether it is possible for one person to move
by filling the board with all of their pieces and seeing if that ends in a win
then doing the opposite with their opponents pieces.  If either of these positions results 
in a win then the game is not a draw.  Note that this assumes we do not have to consider the 
fact that play requires people to alternate moves and very very rarely that would mean that 
there was an actual draw but this does not detect those, but the instructor posted on 
Piazza that we do not need to consider those cases.
*/
bool Gomoku::draw()
{
	Piece dummy_black = Piece(BLACK, "black", "B");
	Piece dummy_white = Piece(WHITE, "white", "W");

	vector<Piece> black_test = pieces;
	vector<Piece> white_test = pieces;

	for (unsigned i = 1; i < width-1; ++i)
	{
		for (unsigned j = 1; j < height - 1; ++j)
		{
			if (pieces[x_y_toIndex(i, j)].display == " ")
			{
				black_test[x_y_toIndex(i, j)] = dummy_black;
				white_test[x_y_toIndex(i, j)] = dummy_white;
			}
		}
	}
	
	Gomoku b_go = Gomoku(black_test, height, width, win_amount);
	Gomoku w_go = Gomoku(white_test, height, width, win_amount);

	return (!(b_go.done() || w_go.done()));
}

//Method that keeps track of turns and
int Gomoku::turn()
{
	unsigned x; unsigned y;
	if (turnCount % 2 == 0) {
		cout << "Black's turn" << endl;
	}
	else {
		cout << "White's turn" << endl;
	}
	try {
		prompt(x, y);
		string s = to_string(x) + "," + to_string(y);
		moves.push_back(s);
	}
	catch (er_mes user_quit)
	{
		throw user_quit;
	}
	if (turnCount % 2 == 0) {
		Piece new_move = Piece(BLACK, "black", "B");
		pieces[x_y_toIndex(x, y)] = new_move;
	}
	else {
		Piece new_move = Piece(BLACK, "white", "W");
		pieces[x_y_toIndex(x, y)] = new_move;
	}

	print();
	++turnCount;
	return success;
}

//play method ties everything together and calls on the previous methods to handle the flow of the game
int Gomoku::play() {
	//restore();
	print();
	while (!done() && !draw())
	{
		for (unsigned i = 0; i < pieces.size(); ++i) {//update longest string if we find a display bigger than
			if (pieces[i].display.length() > longestStr) {//the current max
				longestStr = pieces[i].display.length();
			}
		}
		try {
			turn();
		}
		catch (er_mes er) {
			switch (er) {
			case user_quit:
				break;
			case game_drawn:
				cout << "the game is a draw as there are no more legal moves";
				break;
			}
			return er;
		}
		if (done()) {
			if (turnCount % 2 == 0)
			{
				cout << "White wins!" << endl;
			}
			else
			{
				cout << "Black wins!" << endl;
			}
		}
		else if (draw())
		{
			cout << "the game ends in a draw" << endl;
			return game_drawn;
		}
	}
	return success;
}

//ostream operator that handles printing the board and pieces
ostream & operator<< (ostream & os, const Gomoku &t) {
	try {
		unsigned h = t.height;
		unsigned w = t.width;
		vector<Piece> p = t.pieces;
		printBoard(p, w, h, t.longestStr);
		return os;
	}
	catch (er_mes a) {
		throw a;
	}
	return os;
}

//constructors
Gomoku::Gomoku() :GameBase(GO_HEIGHT, GO_WIDTH), win_amount(DEFAULT_WIN_AMOUNT) {
	restore();
}//constructs the default 19x19 game with 5 in a row to win 
Gomoku::Gomoku(unsigned h, unsigned w, unsigned win_a) :GameBase(h + 2, w + 2), win_amount(win_a) {
	restore();
} 
Gomoku::Gomoku(vector<Piece> p, unsigned h, unsigned w, unsigned win_a) : GameBase(h, w), win_amount(win_a) {
	for (unsigned i = 0; i < p.size(); ++i)
	{
		pieces[i] = p[i];
	}
}
Gomoku::~Gomoku() {}

//overriden pritn function that inserts *this into the ostream
void Gomoku::print() {
	cout << *this << endl;
}

void Gomoku::save(bool saved) {
	ofstream myfile("Gomoku.txt");

	if (saved) {
		if (myfile.is_open()) {
			myfile << "Gomoku\n";
			string dim = to_string(height);
			myfile << dim << "\n";
		}
		else {
			cout << "not created" << endl;
		}
		for (unsigned int i = 0; i < moves.size(); ++i) {
			if (myfile.is_open()) {
				//int x = moves[i]
				myfile << moves[i] + "\n";
			}
		}
	}
	else {//player chooses to not save
		if (myfile.is_open()) {
			myfile << "NO DATA";
		}
	}
}


void Gomoku::restore() {
	ifstream myfile;
	myfile.open("Gomoku.txt");
	string line;
	if (myfile.is_open())
	{
		int widthCount = 0;
	//	int tempWidth;
		getline(myfile, line);
		getline(myfile, line);
		istringstream ss(line);
		unsigned dim;
		ss >> dim;
		if (dim != height)
		{
			cout << "dimension of your save file is not the same as you asked for, did not load it" << endl;
			return;
		}
		while (getline(myfile, line))
		{
			//if (widthCount == 0) {//read width on second line 
			//	istringstream ss(line);
			//	if (ss >> width) {
			//		width = stoi(line);
			//		++widthCount;
			//	}

			//}
			replace(line.begin(), line.end(), ',', ' ');
			istringstream ss(line);
			unsigned x, y;
			if (ss >> x) {
				if (ss >> y) {
					//unsigned index = y * width + x;

					if (turnCount % 2 == 0) {
						Piece new_move = Piece(BLACK, "black", "B");
						pieces[x_y_toIndex(x, y)] = new_move;
						moves.push_back(line);
					}
					else {
						Piece new_move = Piece(BLACK, "white", "W");
						pieces[x_y_toIndex(x, y)] = new_move;
						moves.push_back(line);
					}
					++turnCount;

				}
			}
		}
	}
}
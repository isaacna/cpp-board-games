#include "stdafx.h"
#include "GameBase.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "Enums.h"
#include "Board.h"
#include "Sudoku.h"
#include "Enums.h"

using namespace std;
/*
This is a helper method for our done.  It takes a vector of ints and makes sure they are all unique 
so if there are 9 ints it makes sure you have 1 through 9
*/
bool Sudoku::all_nine(vector<int> nums) {

	for (unsigned i = 1; i <= nums.size(); ++i) {
		bool has_this = false;
		for (unsigned j = 0; j < nums.size(); ++j)
		{
			if (nums[j] == i)
			{
			has_this = true;
			}

		}
		if (!has_this)
		{
			return false;
		}
	}
	return true;
}

//this helper method allows us to easily convert x and y coordinates into their location in the pieces array
unsigned Sudoku::x_y_toIndex(unsigned x, unsigned y)
{
	return (y * SUDOKU_HEIGHT + x);
}

//virtual method must exist, but there is no draw in sudoku so we just say false
bool Sudoku::draw()
{
	return false;
}

//test if the board is full i.e no empty squares
bool Sudoku::full()
{
	for (unsigned i = 1; i < height - 1; ++i)
	{
		for (unsigned j = 1; j < height - 1; ++j)
		{
			string test = "-";
			if (pieces[i*height + j].display == test)
			{
				return false;
			}
		}
	}
	return true;
}

/*
this method tests if the game is over by pushing all of the ints in each row, column, and box
individually and then uses the all_nine method to check that all 9 numbers are there
if no lines or boxes without all nine are found then the game is won and we return true
*/
bool Sudoku::done()
{
	
	for (unsigned i = 1; i < height - 1; ++i)//check if the board is full
	{
		for (unsigned j = 1; j < height - 1; ++j)
		{
			string test = "-";
			if (pieces[i*height + j].display == test)
			{
				return false;
			}
		}
	}
	for (unsigned i = 1; i < height - 1; ++i)//check all the rows and columns
	{
		vector<int> this_row;
		for (unsigned j = 1; j < height -1; ++j)
		{

			this_row.push_back(stoi(pieces[i*height + j].display));

		}
		if (!all_nine(this_row))
		{
			return false;
		}

		vector<int> this_col;
		for (unsigned j = 1; j < height - 1; ++j)
		{
			this_row.push_back(stoi(pieces[j*height + i].display));

		}
		if (!all_nine(this_col))
		{
			return false;
		}

	}
	

	for (unsigned i = 1; i < height - 1; i+=3)//test the boxes
	{
		for (unsigned j = 1; j < height-1; j+=3)
		{
			unsigned start = i*height + j;
			vector<int> this_box;
			for (unsigned k = 0; k < height/3; ++k)
			{
				for (unsigned l = 0; l < height/3; ++l)
				{
					this_box.push_back(stoi(pieces[start + k*height + l].display));
				}
			}
			if (!all_nine(this_box))
			{
				return false;
			}
		}

	}

	return true; //if none of the rows columns or boxes failed having all nine nums then return tru
}

int Sudoku::turn()
{

	unsigned x;
	unsigned y;
	unsigned val;
	try {
		prompt(x, y, val);
	}
	catch (er_mes e)
	{
		throw e;
	}
	if (canEdit[x_y_toIndex(x, y)])
	{
		string s = to_string(x) + "," + to_string(y) + "," + to_string(val);
		moves.push_back(s);
		cout << "f" << endl;
		Piece new_move = Piece(BLACK, "num", to_string(val));
		pieces[x_y_toIndex(x, y)] = new_move;
		print();
	}
	else
	{
		cout << "you can't edit that one because its an original clue!" << endl ;
		return turn();
	}
	if (full() && !done())
	{
		cout << "The board is full but you didn't win, try changing your numbers" << endl;
	}
	return 0;
}

void Sudoku::print()//print the board to the console
{
	cout << *this << endl;
}

string Sudoku::disp_at(unsigned a, unsigned b)//display a single element of the board
{
	return (pieces[x_y_toIndex(a, b)].display);
}

//ostream operator where we print the board and format it so there is distinction between boxes, rows, and columns 
ostream & operator<< (ostream & os, const Sudoku &t) {

	Sudoku temp =  Sudoku(t.pieces); //copy constructor
	
	//top border 
	for (unsigned k = 1; k < t.width - 1; ++k) {
		if (k % 3 == 0) {
			cout << "==";
		}
		else {
			cout << "===";
		}
	}
	cout << endl;


	for (unsigned i = t.height - 2; i > 0; --i) {

		if (i != 0) {//print out y-coordinates 
			cout << i - 1 << "||";
		}
		for (unsigned j = 1; j < t.width-1; ++j) {//print out pieces, and add an extra border around boxed ones
			if (t.pieces[temp.x_y_toIndex(j, i)].display == "-") {//for blank squares
				cout << " " << "|";
			}
			else {//for filled squares
				cout << t.pieces[temp.x_y_toIndex(j, i)].display << "|";
			}
			if (j % 3 == 0) {//add extra border for box 
				cout << "|";
			}
		}
		cout << endl;
		if (i % 3 == 1) { //print out horizontal box border 
			for (unsigned k = 1; k < t.width - 1; ++k) {
				if (k % 3 == 0) {
					cout << "==";
				}
				else {
					cout << "===";
				}
			}
			cout << endl;
		}
		else {//print out normal horizontal border 
			for (unsigned k = 1; k < t.width - 1; ++k) {
				if (k % 3 == 0) {
					cout << "--";
				}
				else {
					cout << "---";
				}
			}
			cout << endl;
		}
	}

	//print out y-coordinates 
	cout << "#" << "||";
	for (unsigned j = 1; j < t.width - 1; ++j) {//print out pieces, and add an extra border around boxed ones
		cout << j -1 << "|";
		if (j % 3 == 0) {
			cout << "|";
		}
	}

	return os;
}

/*
Our save method that writes to Sudoku.txt and stores the board to be read for later
*/
void Sudoku::save(bool saved)
{
	ofstream myfile("Sudoku.txt");

	if (saved) {
		if (myfile.is_open()) {
			myfile << "Sudoku\n";
		}
		else {
			cout << "not created" << endl;
		}
		for (unsigned int i = 0; i < pieces.size(); i+=11) { //loop through pieces and write board to Sudoku.txt
			for (unsigned int j = 0; j < 10; ++j) {
				if (myfile.is_open()) {
					myfile << pieces[i + j].display + " ";
				}
			}
			myfile << "\n";
		}
	}
	else {//player chooses to not save
		if (myfile.is_open()) {
			myfile << "NO DATA";
		}
	}

}

/*
Method to load the default board given in the lab web page
*/
void Sudoku::load_default()
{
	ifstream myfile;
	myfile.open("sudoku0.txt");
	string line;
	unsigned a = 1; unsigned b = 1;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			replace(line.begin(), line.end(), ',', ' ');
			istringstream ss(line);
			unsigned x;
			while (ss >> x) {
				if (x >= 0 && x < height - 1) {}//check if the value is 1-9
				else {
					cout << "there was a bad number in the input file" << endl;
					throw bad_piece_in_file;
				}

				if (x == 0)// for blank pieces
				{
					Piece new_move = Piece(BLACK, "white", "-");
					pieces[x_y_toIndex(b, a)] = new_move;
				}
				else
				{//for not blank pieces, set canEdit index to false for original clues
					canEdit[x_y_toIndex(b, a)] = false;
					string s = to_string(x);
					Piece new_move = Piece(BLACK, "white", s);
					pieces[x_y_toIndex(b, a)] = new_move;
				}
				++b;
			}
			if (b != 10)
			{
				cout << "bad save file" << endl;
				throw wrong_num_pieces;
			}
			++a;
			b = 1;
		}
		if (a != 10)
		{
			cout << "bad save file" << endl;
			throw wrong_num_pieces;
		}
	}
}

/*
read the txt file for a saved game and push it into the pieces vector
*/
void Sudoku::restore()
{
	try {
		load_default();
	}
	catch (er_mes e)
	{
		throw e;
	}
	ifstream myfile;
	myfile.open("Sudoku.txt");
	string line;
	int a = -1; unsigned b = 1;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{

			replace(line.begin(), line.end(), '-', '0');
			istringstream ss(line);
			unsigned x;
			while (ss >> x) {
				if (x >= 0 && x < height - 1) {}
				else {
					cout << "there was a bad number in the input file" << endl;
					throw bad_piece_in_file;
				}
				if (canEdit[x_y_toIndex(b, a)] == true) 
				{
					string s = to_string(x);
					string f = "0";
					if (s == f)
					{
						s = "-";
					}
					Piece edited_move = Piece(BLACK, "white", s);
					pieces[x_y_toIndex(b, a)] = edited_move;
				}
				++b;
			}
			++a;
			if (b != 10 && a > 2 && a < 11)//check for a bad file 
			{
				cout << "bad save file" << endl;
				throw wrong_num_pieces;
			}
			b = 1;
		}
		if (a >0 &&a != 11)//check for a bad file 
		{
			cout << "bad save file" << endl;
			throw wrong_num_pieces;
		}
	}
}

/*
Play method that checks for win condition and calls turn()
*/
int Sudoku::play()
{

	print();
	while (!draw() && !done())
	{
		try {
			turn();
		}
		catch(er_mes e){
			throw e;
		}
	}
	if (done())
	{
		cout << "you win!" << endl;
	}
	return 0;
}

/*
Copy Constructor
*/
Sudoku::Sudoku(std::vector<Piece> the_pieces): GameBase(SUDOKU_HEIGHT, SUDOKU_WIDTH){
	for (unsigned i = 0; i < the_pieces.size(); ++i)
	{
		pieces[i] = the_pieces[i];
	}
}


/*
Default Constructor 
push true into canEdit
later on canEdit determines whether a piece is an original clue (included in sudoku0
*/
Sudoku::Sudoku():GameBase(SUDOKU_HEIGHT, SUDOKU_WIDTH) {
	
	for (int i = 0; i < SUDOKU_HEIGHT; ++i)
	{
		for (int j = 0; j < SUDOKU_HEIGHT; ++j)
		{
			canEdit.push_back(true);
		}
	}
	try {
		restore();
	}
	catch (er_mes e)
	{
		throw e;
	}
}
Sudoku::~Sudoku() {}
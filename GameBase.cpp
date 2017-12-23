#include "stdafx.h"
#include "GameBase.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Enums.h"
#include "Piece.h"
#include <fstream>
#include <string>
#include "Gomoku.h"
#include "Sudoku.h"
#include "TicTacToe.h"

using namespace std;

shared_ptr<GameBase> GameBase::ptr;


//checks if board is full
bool GameBase::is_filled(unsigned x, unsigned y)
{
	if (x >= 0 && y >= 0 && x < width && y < width) {
		
		Piece temp = pieces[width*y + x];
		if (temp.c == NONE)
		{
			return false;
		}
		else
		{
			return true;
		}

	}

	throw(out_of_bounds);
}

//prompts the user for the proper input 
void GameBase::prompt(unsigned &x, unsigned &y) {
	
	cout << "enter your move 'x,y' or quit" << endl;
	string input_line = "";
	getline(cin, input_line);
	bool worked = false;

	if (input_line.compare("quit") == 0) {
		cout << "Do you want to save your game? (yes/no)" << endl;
		string save_line = "";
		getline(cin, save_line);
		if (save_line.compare("yes") == 0) { //check for save response
			//call save method 
			save(true);
			cout << "saved" << endl;
		}
		else {
			save(false);
			cout << "Not saved: your old game is erased" << endl;
		}
		throw user_quit;
	}

	else {
		unsigned x_in, y_in;
		replace(input_line.begin(), input_line.end(), ',', ' ');
		stringstream ss(input_line);
		if (ss >> x_in) 
		{
			if (ss >> y_in)
			{
				if (x_in > 0 && y_in > 0 && x_in < width - 1 && y_in < height - 1)
				{
					if (!is_filled(x_in, y_in))
					{
						x = x_in;
						y = y_in;
						return;
						worked = true;
					}
				}
				else 
				{
					cout << "out of range" << endl;
					prompt(x, y);
					return;
				}
			}
			else
			{
				cout << "please enter two unsigned int coordinates" << endl;
				prompt(x, y);
				return;
			}
		}
		else
		{
			cout << "make sure your coordinates are unsigned ints" << endl;
			prompt(x, y);
			return;
		}
	}
	if (!worked)
	{
		cout << "not the right input, make sure you are entering a valid square" << endl;
		cout << "that is not currently occuppied" << endl;
		prompt(x, y);
	}
}
void GameBase::prompt(unsigned &x, unsigned &y, unsigned &val) {//prompt for sudoku 


	cout << "enter your move 'x,y,val' or quit" << endl;
	string input_line = "";
	getline(cin, input_line);
	bool worked = false;

	if (input_line.compare("quit") == 0) {
		cout << "Do you want to save your game? (yes/no)" << endl;
		string save_line = "";
		getline(cin, save_line);
		if (save_line.compare("yes") == 0) { //check for save response
											 //call save method 
			try {
				save(true);
			}
			catch (int e)
			{
				throw e;
			}
			cout << "saved" << endl;

		}
		else {			
			try {
				save(false);
			}
			catch (int e)
			{
				throw e;
			}
			cout << "Not saved: your old game is erased" << endl;
		}
		throw user_quit;
	}

	else {
		unsigned x_in, y_in, val_in;
		replace(input_line.begin(), input_line.end(), ',', ' ');
		stringstream ss(input_line);
		if (ss >> x_in)
		{
			if (ss >> y_in)
			{
				if (x_in >= 0 && y_in >= 0 && x_in < width - 1 && y_in < height - 1)
				{
					if (ss >> val_in)
					{
						if (val_in > 0 && val_in < height - 1) {
							x = x_in + 1;
							y = y_in + 1;
							val = val_in;
							return;
							worked = true;
						}
						else
						{
							cout << "you may only enter numbers between 1 and " << height - 2 << " into the board" << endl;
							prompt(x, y, val);
							return;
						}
					}
				}
				else
				{
					cout << "out of range" << endl;
					prompt(x, y, val);
					return;
				}
			}
			else
			{
				cout << "please enter three unsigned int coordinates" << endl;
				prompt(x, y, val);
				return;
			}
		}
		else
		{
			cout << "make sure your coordinates are unsigned ints" << endl;
			prompt(x, y, val);
			return;
		}
	}
	if (!worked)
	{
		cout << "not the right input, make sure you are entering a valid square" << endl;
		cout << "that is not currently occuppied" << endl;
		prompt(x, y, val);
	}
}


//constructor for base game class
GameBase::GameBase(unsigned h, unsigned w) : height(h), width(w), turnCount(0)
{
	longestStr = 1;
	string s = to_string(h);
	if (s.length() > longestStr)
	{
		longestStr = s.length();
	}
	s = to_string(w);
	
	if (s.length() > longestStr)
	{
			longestStr = s.length();
	}
	
	Piece blank = Piece();
	for (unsigned i = 0; i < h * w; ++i)
	{
		pieces.push_back(blank);
	}
}

GameBase::~GameBase() {}


//public static instance method that returns a shared smart pointer to the game base class
//checks for nullptr
shared_ptr<GameBase> GameBase::instance() {

	if (ptr != nullptr) {
		return ptr;
	}
	throw null_pointer;



}

/*
This is our command line argument parsing method that also initializes the game instance and sets the game pointer properly
*/
void GameBase::determine(int argc, char* argv[]) {
	try {
		if (ptr != nullptr) {//if shared smart pointer is nullptr 
			throw not_null_ptr;
		}
		else {//initialize game from command arguments and store address in smart ptr 
			string toe = "TicTacToe";
			string go = "Gomoku";
			string su = "Sudoku";

			if (argc < 2) { //check for minimum num of arguments 
				cout << " Usage: Lab4.exe (TicTacToe or Gomoku) " << endl;
				throw wrong_num_args;
			}
			else if (argc == 2) { //if only two arguments, initialize a new object for the corresponding game with the default contructor

				if (argv[1] == toe) {
					GameBase * game = new TicTacToe();
					ptr.reset(game);
				}
				else if (argv[1] == go) {
					GameBase * game = new Gomoku();
					ptr.reset(game);
				}
				else if (argv[1] == su) {
					GameBase * game = new Sudoku();
					ptr.reset(game);
				}
				else {
					throw - 1;//not a game
				}
			}
			else if (argc == 4) {//if two extra arguments specified, initialize a gomoku game where the first extra argument is the dimension, and the second is the win condition
				if (argv[1] == go) {
					if (stoi(argv[2]) >= 1) {
						if (stoi(argv[3]) >= 3) { //if win condition is at least 3
							GameBase * game = new Gomoku(stoi(argv[2]), stoi(argv[2]), stoi(argv[3]));
							ptr.reset(game);
						}
						else
						{ // if win condition is smaller than 3, default to 5
							GameBase * game = new Gomoku(stoi(argv[2]), stoi(argv[2]), DEFAULT_WIN_AMOUNT);
							ptr.reset(game);
						}
					}
					else if (stoi(argv[3]) >= 3) { //if they provide the dimension as 0, default to the standard go paramaters
						GameBase * game = new Gomoku();
						ptr.reset(game);
					}
				}
				else {
					cout << "Only Gomoku uses this number of arguments. " << endl;
					throw wrong_num_args;
				}
			}

			else if (argc == 3) { //if only one extra argument is provided
				if (argv[1] == go) {
					if (stoi(argv[2]) >= 1) {
						if (stoi(argv[2]) < DEFAULT_WIN_AMOUNT) { //if dimension is smaller than win amount, default to the dimension as the win amount  
							GameBase * game = new Gomoku(stoi(argv[2]), stoi(argv[2]), stoi(argv[2]));
							ptr.reset(game);

						}
						else {//if dimension is minimum size use default win condition
							GameBase * game = new Gomoku(stoi(argv[2]), stoi(argv[2]), DEFAULT_WIN_AMOUNT);
							ptr.reset(game);
						}

					}
					else
					{ //standard gomoku game 
						GameBase * game = new Gomoku();
						ptr.reset(game);
					}
				}
				else {
					cout << "Only Gomoku uses this number of arguments" << endl;
					throw wrong_num_args;
				}

			}
			else {
				throw wrong_num_args;
			}
		}
	}

	catch (std::bad_alloc & ba) {//check for bad_alloc exception thrown by new 
		cout << "bad allocation" << endl;
	}
	catch (er_mes e)
	{
		throw e;
	}
}
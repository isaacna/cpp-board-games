#include "stdafx.h"
#include "GameBase.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "Enums.h"
#include "Board.h"
#include "TicTacToe.h"

using namespace std;

//This method checks to see if tic tac toe has a draw by checking if the board is completely filled 
bool TicTacToe::draw()
{
	if (turnCount == (height-2)*(width-2)) {
		return true;
	}
	return false;
}

//Method that checks for a win diagonally, horizontally, and vertically 
bool TicTacToe::done()
{
	if (pieces[6].display == pieces[12].display && pieces[12].display == pieces[18].display) {
		if (pieces[12].display != " ") {
			return true;
		}
	}
	if (pieces[8].display == pieces[12].display && pieces[12].display == pieces[16].display) {
		if (pieces[12].display != " ") {
			return true;
		}
	}

	//vertical check
	for (unsigned int i = 6; i <= 16; i = i + 5) {

		string firstVal = pieces[i].display; //first value of row/col arbitrarily picked as comparison value
		unsigned int count = 0;

		for (unsigned int j = i; j < i + 3; ++j) {
			if (pieces[j].display != " ") { //disregards completely blank board
				if (pieces[j].display == firstVal) { //if matches the comparison value
					++count;
				}
			}
		}
		if (count == 3) {//if three in a row
			return true;
		}
	}

	//horizontal check
	for (unsigned int i = 6; i <= 8; ++i) {

		string firstVal = pieces[i].display;
		unsigned int count = 0;

		for (unsigned int j = i; j <= i + 10; j = j + 5) {
			if (pieces[j].display == firstVal) { //if matches the comparison value 
				if (pieces[j].display != " ") { //disregards completely blank board
					++count;
				}
			}
		}
		if (count == 3) { //if three in a row 
			return true;
		}
	}
	
	return false;

}

//Method that keeps track of turns and stores the past moves for each player in a vector
//prompts the user for input and checks for win/draw conditions
int TicTacToe::turn()
{

	if (turnCount % 2 == 0)
	{
		cout << "Xs turn" << endl;
	}
	else
	{
		cout << "Os turn" << endl;
	}
	unsigned col; 
	unsigned row;

	try {
		prompt(col, row); //get the input from the user
	}
	catch (er_mes er) {
		throw er;

	}
	string s = to_string(col) + "," + to_string(row);
	unsigned index = row * 5 + col;

	if (turnCount % 2 == 0)
	{
		Piece to_insert = Piece(RED, "Xs", "x");
		pieces[index] = to_insert;
		moves.push_back(s);
	}
	else
	{
		Piece to_insert = Piece(BLACK, "Os", "o");
		pieces[index] = to_insert;
		moves.push_back(s);
	}
	turnCount++;
	if (done())//check to see if somebody won
	{
		print();
		if (turnCount %2 ==0)//determine which player won
		{
			cout << "Os wins" << endl;
		}
		else
		{
			cout << "Xs wins" << endl;
		}
	}
	else if (draw())//check if the game is drawn
	{
		print();
		cout << "draw" << endl;
		throw game_drawn;
	}


	return 0;

}

/*
Restore method for tictactoe where we read the file and parse the previous moves, then push it into the pieces vector
*/
void TicTacToe::restore() {
	ifstream myfile;
	myfile.open("TicTacToe.txt");
	string line;
	if (myfile.is_open())
	{
		while (getline(myfile,line))
		{
			replace(line.begin(), line.end(), ',', ' ');
			istringstream ss(line);
			unsigned x, y;
			if (ss >> x) {
				if (ss >> y) {
					unsigned index = y * 5 + x;

					if (turnCount % 2 == 0)
					{
						Piece to_insert = Piece(RED, "Xs", "x");
						pieces[index] = to_insert;
						moves.push_back(line);
					}
					else
					{
						Piece to_insert = Piece(BLACK, "Os", "o");
						pieces[index] = to_insert;
						moves.push_back(line);
					}
					++turnCount;

				}
			}
		}
	}
	

}


//play method ties all the methods together to run the game and handles the user quitting
int TicTacToe::play()
{

	while (!done() && !draw())
	{

		print();
		if (turnCount % 2 == 0) {//print out player Os entire set of moves each time they move
			cout << "X: ";
			for (unsigned i = 0; i < moves.size(); i+= 2) {
				cout << moves[i] << ";";
			}
			cout << "" << endl;
		}
		else//print out player Xs entire set of moves each time they move
		{
			cout << "O: ";
			for (unsigned i = 1; i < moves.size(); i+= 2) {
				cout << moves[i] << ";" ;
			}
			cout << "" << endl;
		}


		try
		{
			turn();
		}
		catch (er_mes a) {//handle quit or draw, or restore

			switch (a) {
			case user_quit:
				cout << "you quit" << endl;
				break;
			case game_drawn:
				cout << "the game is a draw as there are no more legal moves";
				break;
			case wrong_num_args:
				cout << "wrong argument number";
				break;
			}
			return a;
		}
	}


	remove("TicTacToe.txt");//remove the old file 
	
	return 0;
}

//overriden print method that inserts *this into the ostream
void TicTacToe::print() {
	cout << *this << endl;
}


//ostream operator that calls the printboard function to display the board/pieces
ostream & operator<< (ostream & os, const TicTacToe &t) {
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



//constructors for TicTacToe
TicTacToe::TicTacToe() :GameBase(TOE_HEIGHT, TOE_WIDTH) {
	restore();
}
TicTacToe::TicTacToe(vector<Piece> the_pieces) : GameBase(TOE_HEIGHT, TOE_WIDTH) {
	for (unsigned i = 0; i < the_pieces.size(); ++i)
	{
		pieces[i] = the_pieces[i];
	}
}
TicTacToe::~TicTacToe(){
}

/*
Save method that writes the moves into a txt file
*/
void TicTacToe::save(bool saved) {
	ofstream myfile("TicTacToe.txt");
	if (saved) {
		if (myfile.is_open()) {
			myfile << "TicTacToe\n";
		}
		else {
			cout << "not created" << endl;
		}
		for (unsigned int i = 0; i < moves.size(); ++i) {
			if (myfile.is_open()) {
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


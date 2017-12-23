#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Piece.h"
#include <memory>



//the base game class that contains protected member variables and virtual methods
class GameBase {
protected:
	unsigned height, width, longestStr, turnCount, win_amount;
	std::vector<Piece> pieces;
	std::vector<std::string> moves;

	static std::shared_ptr<GameBase> ptr;
public:
	GameBase(unsigned, unsigned);
	~GameBase();

	void prompt(unsigned&, unsigned&);
	void prompt(unsigned&, unsigned&, unsigned&);
	bool is_filled(unsigned, unsigned);
	//static GameBase * determine(int argc, char* argv[]);
	static void determine(int argc, char* argv[]);
	virtual bool draw() = 0;
	virtual bool done() = 0;
	virtual int play() = 0;
	virtual int turn() = 0;
	virtual void print() = 0;

	virtual void save(bool saved) = 0;
	//virtual void restore() = 0;

	static std::shared_ptr<GameBase> instance();
};




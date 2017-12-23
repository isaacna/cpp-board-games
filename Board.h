#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Piece.h"
#include "Enums.h"

using namespace std;

enum printBoard { printSuccess = 0, printFail = 1 };
int printBoard(const vector<Piece> & pieceV, unsigned width, unsigned height, unsigned max);
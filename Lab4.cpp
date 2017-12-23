// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string"
#include "GameBase.h"
#include <memory>

#include "Enums.h"

using namespace std;


//method that puts strings to lowercase
void to_lowcase(string &s)
{
	for (auto c = s.begin(); c != s.end(); ++c)
	{
		if (*c > 64 && *c < 91)
		{
			*c = *c + 32;
		}
	}
}

int main(int argc, char *argv[])
{

	//we call our static method that handles argument parsing and play the proper game 
	/*shared_ptr<GameBase> base(GameBase::determine(argc, argv));
	try {
		return base->play();
	}
	catch (int er) {
		return er;
	}
	*/
	try {
		GameBase::determine(argc, argv);
		return (*GameBase::instance()).play();
	}
	catch (er_mes er) {
		return er;
	}
	return 0;
}


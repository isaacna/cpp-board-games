#include "GameBase.h"

const unsigned TOE_HEIGHT = 5; //constants for the size of the tictactoe board size
const unsigned TOE_WIDTH = 5;

//the derived game class for TicTacToe that contains the proper overriden methods and constructors
class TicTacToe : public GameBase {
	friend std::ostream &operator<<(std::ostream &, const TicTacToe &);

public:
	TicTacToe(std::vector<Piece>); //copy constructor 
	TicTacToe(); // constructs a new TicTacToe game
	~TicTacToe();
	bool draw();
	bool done();
	int play();
	int turn();
	virtual void print();

	void save(bool saved);
	void restore();

};
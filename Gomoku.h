#include "GameBase.h"

const unsigned GO_HEIGHT = 21;
const unsigned GO_WIDTH = 21;
const unsigned DEFAULT_WIN_AMOUNT = 5;

//the derived game class for Gomoku that contains the proper methods and constructors
class Gomoku : public GameBase {
	friend std::ostream &operator<<(std::ostream &, const Gomoku &);

public:
	Gomoku(std::vector<Piece>, unsigned, unsigned, unsigned);
	Gomoku(unsigned, unsigned, unsigned);
	Gomoku();
	~Gomoku();
	bool draw();
	bool done();
	int play();
	int turn();
	unsigned x_y_toIndex(unsigned, unsigned);
	virtual void print();

	void save(bool saved);
	void restore();

private:
	unsigned win_amount;
};
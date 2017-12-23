#include "GameBase.h"


const unsigned SUDOKU_HEIGHT = 11;
const unsigned SUDOKU_WIDTH = 11;

class Sudoku : public GameBase {
	friend std::ostream &operator<<(std::ostream &, const Sudoku &);

public:
	Sudoku(std::vector<Piece>);
	Sudoku();
	~Sudoku();
	bool draw();
	bool done();
	int play();
	int turn();
	virtual void print();
	unsigned x_y_toIndex(unsigned, unsigned);
	std::string disp_at(unsigned, unsigned);
	bool all_nine(std::vector<int>);
	void save(bool saved);
	void load_default();
	void restore();
	bool full();
private:
	std::vector<bool> canEdit;
};

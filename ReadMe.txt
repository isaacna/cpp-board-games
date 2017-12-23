Lab 4 - Isaac Na and Chauncey Hill 
Wustl Keys: isaacyna and chauncey.hill

Workflow:
Isaac: part 2 game lifecycle management, saving and restoring, printing sudoku gameboard, argument parsing, debugging/error handling
Chauncey: saving and restoring, sudoku design and win condition check, debugging/error handling, argument parsing

Errors we ran into:
-Printing the sudoku board and printing it with correct spacing
-We were not sure what the best method was for saving/restoring, but we eventually decided on 
string moves for gomoku/tictactoe, and storing the board itself for sudoku
-We had some errors orienting the inputs and storing pieces properly for sudoku, and we had to fix
a problem with a flipped board due to index miscalculations.
-We also had abort errors because we were catching ints, rather than our enum type for error messages
-We decided to change the blank squares to 0's to prevent errors with reading lines and grabbing each piece

Copy Control Design Decisions

Copy constructor
-we used a copy constructor that copies a game into another one, which we used to copy into a temp game to use in our printing method

move constructor
-we didn't use a move constructor because we didn't find it necessary for our implementation

copy-assignment operator
-We did not use a copy assignment operator because we didn't find it necessary for our implementation

move-assignment operator
-we didn't use a move constructor or a move-assignment operator because we didn't find it necessary

destructor 
-we didn't use a destructor because our shared_ptr covered for the job of the destructor

Testing:

lab4. exe TicTacToe
-Met all the conditions for TicTacToe as in Lab 3, and started a new game if no save file was found, and loaded
the saved game if there was an old game. The user can quit at any time in the game and choose whether to save or not. 
TicTacToe only works if the command line argument is the proper one as above

lab4.exe Gomoku 
lab4.exe Gomoku 5 5 (example: Gomoku with a board size of 5)
lab4.exe Gomoku 3 (example: Gomoku with a win condition of 3)
-Met all conditions for Gomoku as in Lab 3, and started a Gomoku game if there was an old game, and if not it would just 
start a new game with extra conditions that can be added through extra command line arguments if desired (such as board size or win condition).
-saving, restoring, and command line arguments work properly as expected 
-we also checked condition where if a saved game file's dimensions don't match the dimensions of the newly requested game, the new game is started instead
and the old game is not loaded.

lab4.exe Sudoku 
-Starts a new sudoku game on a 9x9 board with squares numbered 0-8. The game behaves properly and the win condition works if the game is properly won 
-Players can't edit over squares that were originally given, but they can edit over squares they inputted. 
-If the board is full and they haven't won, they are told that they can write over there old answers to try to get the winning board.
-Sudoku saves and restores properly, and only runs if the command line argument matches the correct argument as before.
-Sudoku has the default board as sudoku0.txt from the lab web page





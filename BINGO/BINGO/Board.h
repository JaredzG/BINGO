#ifndef BOARD_H
#define BOARD_H

const int BOARD_SIZE = 24;
const int MIN_RANDOM_VALUE = 10;
const int MAX_RANDOM_VALUE = 40;
const int UNIQUE_RANDOM_LIMIT = 31;

class Board
{
private:
	int random;
	int uniqueRandoms;
	int* randomsUsed;
	int* board1;
	int* board2;
	bool playerWin;
	bool playerOneWin;
	bool playerTwoWin;
	void nextTurn();
	void drawBoard(int, int*);
	void setRandom();
	bool checkRandomValidity();
	void checkAndReplace();
	void checkWin();
	bool horizontalCheck();
	bool verticalCheck();
	bool diagonalCheck();
	bool cornerCheck();
	void displayWinner(bool);
public:
	Board();
	void setBoard(int[], int[]);

//**********************************************************//
// This is a destructor to deallocate the memory temporarily//
// used to store the player bingo boards and the unique		//
// random numbers that have been selected.					//
//**********************************************************//
	~Board()
	{
		delete[] randomsUsed;
		delete[] board1;
		delete[] board2;
	}
};
#endif
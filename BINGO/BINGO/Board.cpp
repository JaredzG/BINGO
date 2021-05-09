#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "Board.h"

using namespace std;

//**********************************************************//
// Board is a constructor that allocates memory for the		//
// two player boards and to hold the random numbers that	//
// have been chosen. Also, this function initializes the	//
// private variables of the Board class, and sets the seed	//
// for the random number generator.							//
//**********************************************************//
Board::Board()
{
	srand(static_cast<unsigned int>(time(0)));
	random = 0;
	uniqueRandoms = 0;
	randomsUsed = new int[UNIQUE_RANDOM_LIMIT];
	for (int i = 0; i < UNIQUE_RANDOM_LIMIT; i++)
		randomsUsed[i] = 0;
	board1 = new int[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
		board1[i] = 0;
	board2 = new int[BOARD_SIZE];
	for (int i = 0; i < BOARD_SIZE; i++)
		board2[i] = 0;
	playerWin = false;
	playerOneWin = false;
	playerTwoWin = false;
}

//**********************************************************//
// setBoard is a function that places the user-input numbers//
// into their respective boards.							//
//**********************************************************//
void Board::setBoard(int playerOneInput[], int playerTwoInput[])
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		board1[i] = playerOneInput[i];
		board2[i] = playerTwoInput[i];
	}
	nextTurn();
}

//**********************************************************//
// nextTurn is a function that initiates the next turn of	//
// the bingo game. It first calls the drawBoard method to	//
// display each of the players' boards according to the		//
// initial player input and any changes that have been made.//
// After the boards are drawn, it calls the checkWin method,//
// which checks if any player(s) have met the conditions	//
// to win. If any player(s) have won, then nextTurn calls	//
// the displayWinner function which prints a message		//
// indicating who won. After every iteration of the			//
// boards being drawn, nextTurn lets the user press a key	//
// to continue to the next turn. Finally, nextTurn calls	//
// the setRandom function to set the next random number to	//
// be checked.												//
//**********************************************************//
void Board::nextTurn()
{
	drawBoard(1, board1);
	drawBoard(2, board2);
	cout << endl;
	checkWin();
	if (playerWin)
	{
		displayWinner(playerWin);
		return;
	}
	system("PAUSE");
	cout << endl
		<< "--------------------------------------------------------------"
		<< endl << endl;
	setRandom();
}

// drawBoard is a function that displays the two player		//
// boards as output in the console. It facilitates the		//
// occurrences of when numbers in the board match the		//
// randomly generated numbers, turning into zeros.			//
void Board::drawBoard(int player, int* board)
{
	cout << endl
		<< "Player " << player << " Board:"
		<< endl << endl
		<< setw(3) << "B"
		<< setw(6) << "I"
		<< setw(6) << "N"
		<< setw(6) << "G"
		<< setw(6) << "O"
		<< endl;
	cout << setfill('_')
		<< setw(6) << "|"
		<< setw(6) << "|"
		<< setw(6) << "|"
		<< setw(6) << "|"
		<< "_____"
		<< setfill(' ')
		<< endl;
	for (int i = 0; i < 24; i += 5)
	{
		if (i == 10)
		{
			cout << setw(6) << "|"
				<< setw(6) << "|"
				<< setw(6) << "|"
				<< setw(6) << "|"
				<< endl;
			cout << setw(3) << board[i]
				<< setw(3) << "|"
				<< setw(3) << board[i + 1]
				<< setw(3) << "|"
				<< setw(3) << "0"
				<< setw(3) << "|"
				<< setw(3) << board[i + 2]
				<< setw(3) << "|"
				<< setw(3) << board[i + 3]
				<< endl;
			cout << setfill('_')
				<< setw(6) << "|"
				<< setw(6) << "|"
				<< setw(6) << "|"
				<< setw(6) << "|"
				<< "_____"
				<< setfill(' ')
				<< endl;
			i--;
		}
		else
		{
			cout << setw(6) << "|"
				<< setw(6) << "|"
				<< setw(6) << "|"
				<< setw(6) << "|"
				<< endl;
			cout << setw(3) << board[i]
				<< setw(3) << "|"
				<< setw(3) << board[i + 1]
				<< setw(3) << "|"
				<< setw(3) << board[i + 2]
				<< setw(3) << "|"
				<< setw(3) << board[i + 3]
				<< setw(3) << "|"
				<< setw(3) << board[i + 4]
				<< endl;
			if (i != 19)
			{
				cout << setfill('_')
					<< setw(6) << "|"
					<< setw(6) << "|"
					<< setw(6) << "|"
					<< setw(6) << "|"
					<< "_____"
					<< setfill(' ')
					<< endl;
			}
			else
			{
				cout << setw(6) << "|"
					<< setw(6) << "|"
					<< setw(6) << "|"
					<< setw(6) << "|"
					<< endl;
			}
		}
	}
}

//**********************************************************//
// setRandom is a function sets the next random number to be//
// checked for in the boards. A random number is only set if//
// it is within the bounds, from 10 to 40, and if the number//
// has not been chosen before. These criteria are tested by	//
// calling the checkRandomValidity function. This function	//
// then displays the random number that was successfully	//
// generated and the amount of random numbers that have been//
// chosen. Finally, the checkAndReplace function is called	//
// to check if the random number is in any of the boards	//
// and, if it is, then, in the board(s), it will be replaced//
// with a zero.												//
//**********************************************************//
void Board::setRandom()
{
	do
	{
		random = (rand() % 31) + MIN_RANDOM_VALUE;
	} while (!checkRandomValidity());
	cout << "The random number is: " << random << endl;
	cout << "The number of random numbers chosen is: "
		<< uniqueRandoms << endl;
	checkAndReplace();
}

//**********************************************************//
// checkRandomValidity is a function that tests if the		//
// random number that was generated by the setRandom		//
// function is valid. The criteria for validity is that the	//
// number should be between 10 and 40 inclusive, and the	//
// random number should not have been chosen before. Each	//
// time the random number is invalid, checkRandomValidity	//
// returns a false boolean, causing the setRandom function	//
// to generate another random number to be tested. If the	//
// random number is valid, the number of unique random		//
// numbers gets incremented. Even before testing the random	//
// number's validity, this function tests if the amount of	//
// random numbers that have been successfully chosen matches//
// the maximum amount of random numbers possible,			//
// UNIQUE_RANDOM_LIMIT, which has the value of 31. If there	//
// have already been 31 random numbers chosen, then the		//
// displayWinner function is called with the playerWin		//
// boolean variable, which is still false if the checkWin	//
// function has not set it to true, passed to it.			//
//**********************************************************//
bool Board::checkRandomValidity()
{
	if (uniqueRandoms == UNIQUE_RANDOM_LIMIT)
	{
		displayWinner(playerWin);
	}
	bool isValid = true;
	if (random < MIN_RANDOM_VALUE || random > MAX_RANDOM_VALUE)
	{
		isValid = false;
		return isValid;
	}
	for (int i = 0; i <= UNIQUE_RANDOM_LIMIT; i++)
	{
		if (random == randomsUsed[i])
		{
			isValid = false;
			return isValid;
		}
	}
	uniqueRandoms++;
	randomsUsed[uniqueRandoms] = random;
	return isValid;
}

//**********************************************************//
// checkAndReplace checks if the random number that was		//
// chosen is in any of the boards, and, if it is, then the	//
// number in the board(s) that matches it gets turned into	//
// a zero. After every number in the boards gets checked	//
// and replaced, if it was possible, then nextTurn is		//
// called to display the two updated boards.				//
//**********************************************************//
void Board::checkAndReplace()
{
	for (int i = 0; i < 24; i++)
	{
		if (random == board1[i])
			board1[i] = 0;
		if (random == board2[i])
			board2[i] = 0;
	}
	nextTurn();
}

//**********************************************************//
// checkWin is a function that evaluates whether any of the	//
// players have won.										//
//**********************************************************//
void Board::checkWin()
{
	if (horizontalCheck() || verticalCheck() || diagonalCheck() || cornerCheck())
		playerWin = true;
}

//**********************************************************//
// horizontalCheck is a function that determines if any		//
// player has an entire row of zeros on their board.		//
//**********************************************************//
bool Board::horizontalCheck()
{
	if (board1[0] == board1[1] && board1[0] == board1[2] && board1[0] == board1[3] && board1[0] == board1[4])
		playerOneWin = true;
	else if (board1[5] == board1[6] && board1[5] == board1[7] && board1[5] == board1[8] && board1[5] == board1[9])
		playerOneWin = true;
	else if (board1[10] == board1[11] && board1[10] == board1[12] && board1[10] == board1[13])
		playerOneWin = true;
	else if (board1[14] == board1[15] && board1[14] == board1[16] && board1[14] == board1[17] && board1[14] == board1[18])
		playerOneWin = true;
	else if (board1[19] == board1[20] && board1[19] == board1[21] && board1[19] == board1[22] && board1[19] == board1[13])
		playerOneWin = true;

	if (board2[0] == board2[1] && board2[0] == board2[2] && board2[0] == board2[3] && board2[0] == board2[4])
		playerTwoWin = true;
	else if (board2[5] == board2[6] && board2[5] == board2[7] && board2[5] == board2[8] && board2[5] == board2[9])
		playerTwoWin = true;
	else if (board2[10] == board2[11] && board2[10] == board2[12] && board2[10] == board2[13])
		playerTwoWin = true;
	else if (board2[14] == board2[15] && board2[14] == board2[16] && board2[14] == board2[17] && board2[14] == board2[18])
		playerTwoWin = true;
	else if (board2[19] == board2[20] && board2[19] == board2[21] && board2[19] == board2[22] && board2[19] == board2[13])
		playerTwoWin = true;

	if (playerOneWin || playerTwoWin)
		return true;
	return false;
}

//**********************************************************//
// verticalCheck is a function that determines if any		//
// player has an entire column of zeros on their board.		//
//**********************************************************//
bool Board::verticalCheck()
{
	if (board1[0] == board1[5] && board1[0] == board1[10] && board1[0] == board1[14] && board1[0] == board1[19])
		playerOneWin = true;
	else if (board1[1] == board1[6] && board1[1] == board1[11] && board1[1] == board1[15] && board1[1] == board1[20])
		playerOneWin = true;
	else if (board1[2] == board1[7] && board1[2] == board1[16] && board1[2] == board1[21])
		playerOneWin = true;
	else if (board1[3] == board1[8] && board1[3] == board1[12] && board1[3] == board1[17] && board1[3] == board1[22])
		playerOneWin = true;
	else if (board1[4] == board1[9] && board1[4] == board1[13] && board1[4] == board1[18] && board1[4] == board1[23])
		playerOneWin = true;

	if (board2[0] == board2[5] && board2[0] == board2[10] && board2[0] == board2[14] && board2[0] == board2[19])
		playerTwoWin = true;
	else if (board2[1] == board2[6] && board2[1] == board2[11] && board2[1] == board2[15] && board2[1] == board2[20])
		playerTwoWin = true;
	else if (board2[2] == board2[7] && board2[2] == board2[16] && board2[2] == board2[21])
		playerTwoWin = true;
	else if (board2[3] == board2[8] && board2[3] == board2[12] && board2[3] == board2[17] && board2[3] == board2[22])
		playerTwoWin = true;
	else if (board2[4] == board2[9] && board2[4] == board2[13] && board2[4] == board2[18] && board2[4] == board2[23])
		playerTwoWin = true;

	if (playerOneWin || playerTwoWin)
		return true;
	return false;
}

//**********************************************************//
// diagonalCheck is a function that determines if any		//
// player has an entire diagonal of zeros on their board.	//
//**********************************************************//
bool Board::diagonalCheck()
{
	if (board1[0] == board1[6] && board1[0] == board1[17] && board1[0] == board1[23])
		playerOneWin = true;
	else if (board1[4] == board1[8] && board1[4] == board1[15] && board1[4] == board1[19])
		playerOneWin = true;

	if (board2[0] == board2[6] && board2[0] == board2[17] && board2[0] == board2[23])
		playerTwoWin = true;
	else if (board2[4] == board2[8] && board2[4] == board2[15] && board2[4] == board2[19])
		playerTwoWin = true;

	if (playerOneWin || playerTwoWin)
		return true;
	return false;
}

//**********************************************************//
// cornerCheck is a function that determines if any			//
// player has zeros in all of the corners of their board.	//
//**********************************************************//
bool Board::cornerCheck()
{
	if (board1[0] == board1[4] && board1[0] == board1[19] && board1[0] == board1[23])
		playerOneWin = true;

	if (board2[0] == board2[4] && board2[0] == board2[19] && board2[0] == board2[23])
		playerTwoWin = true;

	if (playerOneWin || playerTwoWin)
		return true;
	return false;
}

//**********************************************************//
// displayWinner prints a message indicating which players,	//
// if any, have won.										//
//**********************************************************//
void Board::displayWinner(bool playerWin)
{
	if (!playerWin)
	{
		cout << "Neither player won...\n";
		return;
	}
	if (playerOneWin && !playerTwoWin)
	{
		cout << "Player 1 Wins and Player 2 Loses!\n";
		return;
	}
	else if (!playerOneWin && playerTwoWin)
	{
		cout << "Player 2 Wins and Player 1 Loses!\n";
		return;
	}
	else if (playerOneWin && playerTwoWin)
	{
		cout << "Both Player 1 and Player 2 Win!\n";
		return;
	}
}
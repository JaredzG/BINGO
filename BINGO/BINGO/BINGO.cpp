#include <iostream>
#include <iomanip>
#include <string>
#include "Board.h"

using namespace std;

void getPlayerInput(int, int*, const int size);	// Function to get player input
bool isInteger(const string&);	// Function to check player input type
bool checkInputDuplicate(int, int[], const int size); // Function to check for player input duplicates

int main()
{
	int playerOneInput[BOARD_SIZE];		// Declaration of the array to hold player one input
	int playerTwoInput[BOARD_SIZE];		// Declaration of the array to hold player two input
	getPlayerInput(1, playerOneInput, BOARD_SIZE);
	getPlayerInput(2, playerTwoInput, BOARD_SIZE);
	Board startGame;		// Instantiation of a Board object to initialize all of the data needed for the bingo game
	startGame.setBoard(playerOneInput, playerTwoInput);		// Places the player input into the boards to play the game.
}

//**********************************************************//
// getPlayerInput is a function that gets numbers from the
// players to input into their boards. This function also
// makes sure that the player input is valid by checking the
// input bounds itself and if the input is duplicated by
// calling the checkInputDuplicate function.
//**********************************************************//
void getPlayerInput(int player, int* playerInput, const int size)
{
	string input;	// Variable to hold player input
	int temp;	// Variable to store valid player input as an integer
	cout << "Player " << player << ": Enter 24 integers one at a time from 10 to 40 with no duplicates.\n";
	for (int i = 0; i < BOARD_SIZE; i++) // Loop to store valid input from player one
	{
		bool isValid = false;	// The number input by the player is invalid by default until tested
		do       // Loop to check if player input is within the range specified and not a duplicate of input already stored
		{
			cout << "Enter number " << i + 1 << ": ";
			getline(cin, input);
			while (!isInteger(input))	// Checks the condition that the input is an integer
			{
				cout << "Your input is not an integer.\n"
					<< "Please enter an integer from 10 to 40 with no duplicates.\n"
					<< "Enter number " << i + 1 << ": ";
				getline(cin, input);
			}
			temp = stoi(input);
			if (temp >= MIN_RANDOM_VALUE && temp <= MAX_RANDOM_VALUE && !checkInputDuplicate(temp, playerInput, BOARD_SIZE))
			{
				playerInput[i] = temp;
				isValid = true;
			}
			else
			{
				cout << "The integer you entered is not valid.\n"
					<< "Please enter an integer from 10 to 40 with no duplicates.\n";
			}
		} while (!isValid);
	}
	cout << endl;
}

//**********************************************************//
// isInteger is a function that checks if the input from the
// player contains only digits that can be checked for
// validity.
//**********************************************************//
bool isInteger(const string& str)
{
	if (str.length() == 0)
		return false;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

//**********************************************************//
// checkInputDuplicate is a function that checks the
// validity of player input on the basis of whether it is
// a duplicate of previously input data.
//**********************************************************//
bool checkInputDuplicate(int num, int playerInput[], const int size)
{
	bool isDuplicate = false;
	for (int i = 0; i < size; i++)
		if (num == playerInput[i])
			return true;
	return isDuplicate;
}

// wordNumberGame.cpp 
// Program will ask for an expression (the puzzle) represented by a words and operators
// The letters of the words are mapped to digits (0-9) such that the expression is valid
//     For instance, a puzzle:  pot + pan = bib
//     will yield a solution: p=0, o=3, t=4,  a=8,  n=7,  b=1,  i=2;  34 + 87 = 121
//     
// Currently program works with two operands and addition.
// Input is a string of the form pot+pan=bib
// This is input as an argument to the command line
//
// Key Objects:
//    Puzzle represents a word puzzle where by op1 + op2 = sum
//    Mapping is a "guess" at a mapping of numbers to letters
//    Puzzles can apply mappings
//

#include "stdafx.h"
#include "Mapping.h"
#include "Puzzle.h"
#include <iostream>
using namespace std;

const string DEFAULT_PUZZLE = "pot+pan=bib";
bool nextLetter(Puzzle &thePuzzle, Mapping &currentGuess, int slot);

int main(int argc, char *argv[])
{
	// Get the puzzle to solve as a string and create Puzzle
	string puzzleString;
	if (argc == 1)
	{
		puzzleString = DEFAULT_PUZZLE;
	}
	else if (argc == 2)
	{
		puzzleString = string(argv[1]);
	}
	else
	{
		cerr << "Usage:  wordNumberGame op1+op2=sum" << endl;
		return -1;
	}
	Puzzle myPuzzle(puzzleString);
	Mapping guess;

	//populate guess with letters of the puzzle
	guess.addLetters(puzzleString);
	
	cout << "Puzzle: " << myPuzzle.getPuzzle() << endl;

	bool solved = nextLetter(myPuzzle, guess, 0);
	if (solved)
	{
		cout << guess << endl;
		cout << myPuzzle.getValuesFromMapping(guess) << endl;
	}
	else
	{
		cout << "No Solution" << endl;
	}
    return 0;
}

// This is the recursive function which solves the puzzle.  
// If all slots have been filled then puzzle solved.
bool nextLetter(Puzzle &thePuzzle, Mapping &currentGuess, int slot)
{
	//NEED TO FIX THIS... 
	//if (slot == currentGuess.getSize())
	//{
	//	return true;
	//}
	
	for (int value = 0; value <= 9; value++)
	{
		currentGuess.setPosition(slot, value);
		if (! currentGuess.isValid())
		{
			continue;
		}
		
		if (slot < currentGuess.getSize() - 1)
		{
			if (nextLetter(thePuzzle, currentGuess, slot + 1))
			{
				return true;
			}
			else
			{
				continue;
			}
		}
		if (thePuzzle.SolvedWithMapping(currentGuess))
		{
			return true;
		}
	}
	currentGuess.setPosition(slot, NOT_SET);
	return false;
}

/*Possible Puzzles
string op1 = "rob";
string op2 = "rbo";
string sum = "btt";

string op1 = "pot";
string op2 = "pan";
string sum = "bib";

string op1 = "dog";
string op2 = "cat";
string sum = "pig";

string op1 = "boy";
string op2 = "girl";
string sum = "baby";
*/

// wordNumberGame.cpp 
// Program will ask for an expression (the puzzle) represented by a words and operators
// The letters of the words are mapped to digits (0-9) such that the expression is valid
//     For instance, a puzzle:  pot + pan = bib
//     will yield a solution: p=0, o=3, t=4,  a=8,  n=7,  b=1,  i=2;  34 + 87 = 121
//     
// Currently program workds with two operands and addition.
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
	/*
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

	//populate guess
	guess.addLetters(puzzleString);
	
	cout << "Puzzle: " << myPuzzle.getPuzzle() << endl;
	cout << guess << endl;
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


	/*
	Puzzle myPuzzle("rob", "rbo", "btt");
	Mapping guess;
	guess.addLetter('r', 1);
	guess.addLetter('o', 3);
	guess.addLetter('b', 2);
	guess.addLetter('t', 5);

	cout << myPuzzle.getPuzzle() << endl;
	cout << guess << endl;
	cout << myPuzzle.getValuesFromMapping(guess) << endl;;
	cout << "Solved: " << myPuzzle.SolvedWithMapping(guess) << endl;
	*/

	//Tests for guess
	/*
	Mapping guess;
	guess.addLetter('r');
	guess.addLetter('o');
	guess.addLetter('r');
	guess.addLetter('b');
	guess.addLetter('e');
	guess.addLetter('o');
	cout << guess << endl;
	guess.setPosition(2, 7);
	guess.setPosition(3, 7);
	cout << guess << endl;
	cout << guess.isValid() << endl;
	*/
    return 0;
}

bool nextLetter(Puzzle &thePuzzle, Mapping &currentGuess, int slot)
{
	// if all slots have been filled then puzzle solved.
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
	currentGuess.setPosition(slot, -1);
	return false;
}

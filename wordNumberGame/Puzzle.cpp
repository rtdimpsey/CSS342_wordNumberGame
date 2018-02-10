#include "stdafx.h"
#include "Puzzle.h"


Puzzle::Puzzle()
{
}

Puzzle::Puzzle(string op1, string op2, string sum) : opWord1(op1), opWord2(op2), sumWord(sum), 
	opVal1(-1), opVal2(-1), sumVal(0)
{
}

//exression contains the full puzzle in a string
//assuming no spaces in the string pot+pan=bib
Puzzle::Puzzle(string expression) : opVal1(-1), opVal2(-1), sumVal(0)
{
	size_t position;
	position = expression.find("+");
	this->opWord1 = expression.substr(0, position);
	expression.erase(0, position+1);
	position = expression.find("=");
	this->opWord2 = expression.substr(0, position);
	expression.erase(0, position + 1);
	this->sumWord = expression;
}

Puzzle::~Puzzle()
{
}

string Puzzle::getPuzzle() const
{
	return string(opWord1 + " + " + opWord2 + " = " + sumWord);
}

string Puzzle::getValuesFromMapping(Mapping guess)
{
	if (applyMapping(guess))
	{
		return string(to_string(opVal1) + " + " + to_string(opVal2) + " = " + to_string(sumVal));
	}
	else
	{
		return string("Mapping did not apply correctly");
	}
}

bool Puzzle::SolvedWithMapping(Mapping guess)
{
	if (! applyMapping(guess))
	{
		return false;
	}
	if (opVal1 + opVal2 == sumVal)
	{
		return true;
	}
	else
	{
		return false;
	} 
}

//Apply the mapping of values to the letters in the puzzle.
//If a letter value of the puzzle is not set to a value then return false
//This could be either because mapping does not have the letter or the letter does not have a value
//map may be partially applied
bool Puzzle::applyMapping(Mapping theMap)
{
	//TODO:: Either apply full map or no map
	int tempVal = 0;
	for (int i = 0; i < opWord1.length(); i++)
	{
		int val = theMap.getValue(opWord1[i]);
		if ((val == -1) || (val == -2))
		{
			return false;
		}
		tempVal += (val * pow(10, opWord1.length() - i - 1));
	}
	opVal1 = tempVal;

	tempVal = 0;
	for (int i = 0; i < opWord2.length(); i++)
	{
		int val = theMap.getValue(opWord2[i]);
		if ((val == -1) || (val == -2))
		{
			return false;
		}
		tempVal += (val * pow(10, opWord2.length() - i - 1));
	}
	opVal2 = tempVal;

	tempVal = 0;
	for (int i = 0; i < sumWord.length(); i++)
	{
		int val = theMap.getValue(sumWord[i]);
		if ((val == -1) || (val == -2))
		{
			return false;
		}
		tempVal += (val * pow(10, sumWord.length() - i - 1));
	}
	sumVal = tempVal;

	return true;
}

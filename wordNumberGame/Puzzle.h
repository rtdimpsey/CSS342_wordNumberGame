#pragma once
#include <iostream>
#include <string>
#include "Mapping.h"
using namespace std;

// Puzzle represents a word puzzle where by op1 + op2 = sum
// The operands and sum are words where the letters get mapped to digits
// The puzzle applies Mappings() to the ops to see if the puzzle is solved
class Puzzle
{
public:
	Puzzle();
	Puzzle(string op1, string op2, string sum);
	Puzzle(string expression);
	~Puzzle();

	string getPuzzle() const;
	string getValuesFromMapping(Mapping guess);
	bool SolvedWithMapping(Mapping guess);

private:
	string opWord1;
	string opWord2;
	string sumWord;
	int opVal1;
	int opVal2;
	int sumVal;
	bool applyMapping(Mapping guess);
};

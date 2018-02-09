#pragma once
#include "Match.h"
#include <iostream>
#include <vector>
using namespace std;
class Mapping
{
	friend ostream& operator<<(ostream &outStream, const Mapping& rhs);

public:
	Mapping();
	~Mapping();

	int getSize() const;
	int getValue(char letter) const;
	bool isComplete() const;

	bool addLetter(char letter);
	bool addLetters(string word);
	bool addLetters(const vector<string>& words);
	bool addLetter(char letter, int value);
	bool setPosition(int index, int value);
	bool containsLetter(char letter);
	bool containsValue(int value);
	bool isValid() const;

private:
	vector<Match> theMap;
};


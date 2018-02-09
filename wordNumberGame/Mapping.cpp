#include "stdafx.h"
#include "Mapping.h"


Mapping::Mapping()
{
}

Mapping::~Mapping()
{
}

int Mapping::getValue(char letter) const
{
	//TODO GET RID OF -2 hardcoding
	for (int i = 0; i < theMap.size(); i++)
	{
		if (theMap[i].getLetter() == letter)
		{
			return theMap[i].getValue();
		}
	}
	return -2;
}

//If all letters are assigned then the mapping is complete
//NOTE THAT THIS REQUIRES ALL LETTERS NOT JUST THOSE IN THE PUZZLE
bool Mapping::isComplete() const
{
	for (int i = 0; i < theMap.size(); i++)
	{
		if (theMap[i].getValue() == -1)
		{
			return false;
		}
	}
	return true;
}

bool Mapping::addLetter(char letter)
{
	if (containsLetter(letter))
	{
		return false;
	}
	else
	{
		Match newMatch = Match(letter, -1);
		theMap.push_back(newMatch);
	}
}

//Add all letters in the word. 
//If any new letters added return true
bool Mapping::addLetters(string word)
{
	bool newLetterAdded = false;
	for (int i = 0; i < word.length(); i++)
	{
		if (addLetter(word[i]))
		{
			newLetterAdded = true;
		}
	}
	return newLetterAdded;
}

// Only valid letter-value pairs are allowed
bool Mapping::addLetter(char letter, int value)
{
	if (containsLetter(letter) || (value < -1) || (value > 9) || containsValue(value))
	{
		return false;
	}
	else
	{
		Match newMatch = Match(letter, value);
		theMap.push_back(newMatch);
	}
}


bool Mapping::setPosition(int index, int value)
{
	if ((index < 0) || (index >= theMap.size()))
	{
		return false;
	}
	if ((value < -1) || (value > 9))
	{
		return false;
	}
	theMap[index].setValue(value);
	return true;
}

int Mapping::getSize() const
{
	return theMap.size();
}

bool Mapping::containsLetter(char letter)
{
	for (int i = 0; i < theMap.size(); i++)
	{
		if (theMap[i].getLetter() == letter)
		{
			return true;
		}
	}
	return false;
}

bool Mapping::containsValue(int value)
{
	//TODO:  Throw exception if value is not valid
	for (int i = 0; i < theMap.size(); i++)
	{
		if (theMap[i].getValue() == value)
		{
			return true;
		}
	}
	return false;
}

// All matches must have either a -1 (not set) or a unique number 0-9 for the map to be valid
// We'll use an unsigned bit array to keep track
bool Mapping::isValid() const
{
	unsigned bitArray = 0;
	for (int i = 0; i < theMap.size(); i++)
	{
		int val = theMap[i].getValue();
		if (val != -1)
		{
			unsigned bitMask = (1 << val);
			if (bitMask & bitArray)
			{
				return false;
			}
			else
			{
				bitArray |= bitMask;
			}
		}
	}
	return true;
}

ostream& operator<<(ostream &outStream, const Mapping& rhs)
{
	for (int i = 0; i < rhs.theMap.size(); i++)
	{
		if (rhs.theMap[i].getValue() == -1)
		{
			outStream << rhs.theMap[i].getLetter() << ",*  ";
		}
		else
		{
			outStream << rhs.theMap[i].getLetter() << "," << rhs.theMap[i].getValue() << "  ";
		}
		
	}
	return outStream;
}
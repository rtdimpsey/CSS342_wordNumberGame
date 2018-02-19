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
//Note:  There can be letters in the mapping which are not needed for the puzzle
bool Mapping::isComplete() const
{
	for (int i = 0; i < theMap.size(); i++)
	{
		if (theMap[i].getValue() == NOT_SET)
		{
			return false;
		}
	}
	return true;
}

// Letters added must be lower case
// No other symbols but a-z accepted
bool Mapping::addLetter(char letter)
{
	if (containsLetter(letter))
	{
		return false;
	}
	else if ((letter < 'a') || (letter >= 'z'))
	{
		return false;
	}
	else
	{
		Match newMatch = Match(letter, NOT_SET);
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
	if (containsLetter(letter) || containsValue(value))
	{
		return false;
	}
	else if ( ((value >= 0) && (value <= 9)) || (value == NOT_SET))
	{ 
		Match newMatch = Match(letter, value);
		theMap.push_back(newMatch);
	}
	else
	{
		return false;
	}
}


bool Mapping::setPosition(int index, int value)
{
	if ((index < 0) || (index >= theMap.size()))
	{
		return false;
	}
	else if (((value >= 0) && (value <= 9)) || (value == NOT_SET))
	{
		theMap[index].setValue(value);
		return true;
	}
	else
	{
		return false;
	}
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

// All matches must have either a NOT_SET or a unique number 0-9 for the map to be valid
// We'll use an unsigned bit array to keep track
bool Mapping::isValid() const
{
	unsigned bitArray = 0;
	for (int i = 0; i < theMap.size(); i++)
	{
		int val = theMap[i].getValue();
		if (val != NOT_SET)
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
		if (rhs.theMap[i].getValue() == NOT_SET)
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
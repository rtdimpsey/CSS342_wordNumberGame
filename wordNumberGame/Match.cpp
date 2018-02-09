#include "stdafx.h"
#include "Match.h"


Match::Match() : letter(' '), value(-1)
{
}

Match::Match(char l, int num) : letter(l), value(num)
{
	if ((value < -1) || (value > 9))
	{
		value = -1;
	}
}

Match::~Match()
{
}

char Match::getLetter() const
{
	return letter;
}

int Match::getValue() const
{
	return value;
}

bool Match::setValue(int num)
{
	if ((num < -1) || (num > 9))
	{
		return false;
	}
	else
	{
		value = num;
		return true;
	}
}

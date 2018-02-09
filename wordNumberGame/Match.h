#pragma once
class Match
{
public:
	Match();
	Match(char l, int num);
	~Match();

	char getLetter() const;
	int getValue() const;
	bool setValue(int num);

private:
	char letter;
	int value;
};


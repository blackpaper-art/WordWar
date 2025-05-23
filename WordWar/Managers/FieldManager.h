#pragma once

class FieldManager
{
public:
	FieldManager();
	~FieldManager();

	char GetField(int x, int y);
	void SetField(int x, int y, char intern);
private:
	static const int fieldWidth = 16 * 3;
	static const int fieldHeight = 9 * 3;
	char field[fieldHeight][fieldWidth];
};

#pragma once
#include <iostream>
#include <string>
#include "Methods.h"


class UserInput {
private:
	int KeyType;
	int KeyCode;
	int Index;

	bool FireOnPress;

	bool Active;
	bool Pressed;

public:
	UserInput();
	UserInput(int KeyType, int KeyCode, int Index, bool FireOnPress);
	UserInput(std::string Input, bool FireOnPress);

	bool IsActive();

	void CheckState();

	~UserInput();
	std::string ToString() const;

	bool operator == (const UserInput &Other);
};
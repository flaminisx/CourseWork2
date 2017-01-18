#pragma once

#include <string>

using namespace std;
class Panel
{
protected:
	int number;
	string name;
	HWND parent;
	HINSTANCE hInstance;
public:
	Panel(int, string, HWND, HINSTANCE);
	~Panel();

	virtual void show() = 0;
	virtual pair<string, string> collectData() = 0;
};


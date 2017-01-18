#pragma once
#include "Panel.h"

class LabeledEditText : public Panel
{
private:
	HWND myhwnd;
public:
	LabeledEditText(int, string, HWND, HINSTANCE);
	~LabeledEditText();
	void show();
	pair<string, string> collectData();
};


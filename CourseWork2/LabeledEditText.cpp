#include "stdafx.h"
#include "LabeledEditText.h"


LabeledEditText::LabeledEditText(int num, string name, HWND h, HINSTANCE hInstance) : Panel(num, name, h, hInstance)
{
}


LabeledEditText::~LabeledEditText()
{
}
void LabeledEditText::show() 
{
	LPCSTR sw = name.c_str();
	CreateWindow("STATIC", sw, 
				WS_CHILD | WS_VISIBLE | SS_LEFT, 
				10, 20 + (number * 60), 350, 30, parent,
				NULL, NULL, NULL);

	myhwnd = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("edit"), "",
				WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE,
				10, 40 + (number * 60), 350, 30, parent,
				(HMENU)10000 + number, hInstance, NULL);
	
}
pair<string, string> LabeledEditText::collectData()
{
	TCHAR str[255];
	GetWindowText(myhwnd, str, 255);
	return pair<string, string>(name, string(str));
}
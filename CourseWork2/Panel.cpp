#include "stdafx.h"
#include "Panel.h"

Panel::Panel(int num, string name, HWND h, HINSTANCE hInstance)
{
	this->name = name;
	this->number = num;
	this->parent = h;
	this->hInstance = hInstance;
}

Panel::~Panel()
{
}

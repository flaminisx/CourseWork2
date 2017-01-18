#include "stdafx.h"
#include "Loader.h"
#include "Dialog.h"

using namespace std;
using namespace course;

Loader::Loader(vector<vector<string>> conf, HWND hWND, void(*f)(vector<map<string, string>>*))
{
	config = conf;
	hWnd = hWND;
	step = 0;
	data = vector<map<string, string>>();
	callback = f;
}


Loader::~Loader()
{
}

void Loader::start()
{
	step = 0;
	next();
}

void Loader::save(map<string, string> result)
{
	data.push_back(result);
	if (++step < config.size())
	{
		next();
	}
	else end();
}
void Loader::previous()
{
	step--;
	data.erase(data.begin() + data.size() - 1);
	currentDialog = new Dialog(this, config[step], hWnd, step == 0, step == (config.size() - 1));
	currentDialog->show();
}
void Loader::next()
{
	currentDialog = new Dialog(this, config[step], hWnd, step==0, step==(config.size()-1));
	currentDialog->show();
}

void Loader::end()
{
	callback(&data);
}

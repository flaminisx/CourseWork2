#include "stdafx.h"
#include "Loader.h"
#include "Dialog.h"

using namespace std;
using namespace course;

Loader::Loader(vector<vector<string>> conf, HWND hWND)
{
	config = conf;
	hWnd = hWND;
	step = 0;
	data = vector<map<string, string>>();
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
	if (++step < config.size()) next();
	else end();
}
void course::Loader::previous()
{
}
void Loader::next()
{
	currentDialog = new Dialog(this, config[step], hWnd, step==0, step==(config.size()-1));
	currentDialog->show();
}

void Loader::end()
{
	vector<Json> arr = vector<Json>();
	for (int i = 0; i < data.size(); i++)
	{
		map<string, Json > panelData = map<string, Json >();
		for (pair<string, string> p : data[i])
		{
			panelData.insert({ p.first, Json(p.second) });
		}
		arr.push_back(Json(panelData));
	}
	string s = Json(arr).dump();
	std::string stemp = std::string(s.begin(), s.end());
	LPCSTR sw = stemp.c_str();
	MessageBox(nullptr, sw, "test", MB_OK);
}

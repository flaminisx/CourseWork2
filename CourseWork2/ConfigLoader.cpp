#include "stdafx.h"
#include "ConfigLoader.h"
#include "json11.hpp"
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace json11;


ConfigLoader::ConfigLoader(string filename)
{
	this->file = filename;
}


ConfigLoader::~ConfigLoader()
{
}

vector<vector<string>> ConfigLoader::getConfig()
{
	vector<vector<string>> arr;
	ifstream fin(file);

	if (!fin.is_open())
	{
		arr = vector<vector<string>>();
	}
	else
	{
		string str((std::istreambuf_iterator<char>(fin)),
			std::istreambuf_iterator<char>());
		string err;
		auto json = Json::parse(str, err);
		int objCount = json.array_items().size();
		arr = vector<vector<string>>(objCount);
		for (int i = 0; i < objCount; i++) 
		{
			int panelsCount = json[i].array_items().size();
			arr[i] = vector<string>(panelsCount);
			for (int j = 0; j < panelsCount; j++)
			{
				arr[i][j] = json[i][j].string_value();
			}
		}
		fin.close();
	}

	return arr;
}

#pragma once

#include <string>
#include <vector>
#include <map>
#include "Dialog.h"
#include "json11.hpp"

using namespace std;
using namespace json11;

namespace course {
	class Loader
	{
	private:
		vector<vector<string>> config;
		HWND hWnd;
		class Dialog *currentDialog;
		int step;
		vector<map<string, string>> data;
		void next();
		void end();
		void(*callback)(vector<map<string, string>>*);
	public:
		Loader(vector<vector<string>>, HWND, void(*f)(vector<map<string, string>>*));
		~Loader();
		void start();
		void save(map<string, string>);
		void previous();
	};

}
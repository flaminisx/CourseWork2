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
	public:
		Loader(vector<vector<string>>, HWND);
		~Loader();
		void start();
		void save(map<string, string>);
		void previous();
	};

}
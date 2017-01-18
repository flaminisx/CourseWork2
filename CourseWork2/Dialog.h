#pragma once

#include "Loader.h"
#include "Panel.h"
#include <vector>
#include <string>

using namespace std;
namespace course {
	class Dialog
	{
	private:
		class Loader *loader;
		vector<string> config;
		HWND hWnd;
		int order;
		bool first;
		bool last;
		LPSTR className;
		vector<Panel*> panels;
	public:
		Dialog(Loader*, vector<string>, HWND, bool, bool);
		~Dialog();
		void show();
		void createWindow();
		LRESULT CALLBACK actionHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	};

}
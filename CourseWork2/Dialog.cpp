#include "stdafx.h"
#include "Dialog.h"
#include "Windows.h"
#include "LabeledEditText.h"

#define IDB_PREVIOUS 1231
#define IDB_NEXT 1232
#define IDB_SAVE 1233
#define IDB_CANCEL 1234


using namespace course;
LRESULT CALLBACK handleWrapper(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Dialog *c = (Dialog *)GetWindowLong(hwnd, GWLP_USERDATA);

	if (c == NULL)
		return DefWindowProc(hwnd, msg, wParam, lParam);

	return c->actionHandler(hwnd, msg, wParam, lParam);
}
Dialog::Dialog(Loader *loadr, vector<string> conf, HWND hWnd, bool first, bool last)
{
	loader = loadr;
	config = conf;
	this->hWnd = hWnd;
	this->first = first;
	this->last = last;
	className = "window_with_panels";
}

Dialog::~Dialog()
{
}

void Dialog::show()
{
	/*string s = "";
	map<string, string> vals = map<string, string>();
	for (int j = 0; j < config.size(); j++)
	{
		vals.insert({ config[j], "data" });
		s += config[j];
	}
	std::wstring stemp = std::wstring(s.begin(), s.end());
	LPCWSTR sw = stemp.c_str();
	MessageBox(nullptr, sw, L"test", MB_OK);
	loader->save(vals);*/
	createWindow();
}
void Dialog::createWindow() 
{
	TCHAR str[255];
	int panelsCount = config.size();
	HINSTANCE hInstance = GetModuleHandle(NULL);
	HWND hPanel = GetDlgItem(hWnd, 1);
	if (hPanel)
	{
		DestroyWindow(hPanel);
		UnregisterClass(className, hInstance);
		//MessageBox(nullptr, "window creating error", "error", MB_OK);

	}
	WNDCLASSEX wc = { 0 };
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)handleWrapper;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = className;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	ATOM WNDClass = RegisterClassEx(&wc);
	if (!WNDClass)
	{
		MessageBox(nullptr, "wndclass wasnt registered", "error", MB_OK);

		return;
	}
	hPanel = CreateWindowEx(NULL,
		className,
		NULL,
		WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | DS_CENTER,
		400, 170, 400, 100 + (config.size()) * 60,
		hWnd,   // родительское окно
		NULL,
		hInstance, NULL);
	if (!hPanel) 
	{
		char szTest[20];
		sprintf_s(szTest, "%d", GetLastError());
		MessageBox(nullptr, szTest, "test", MB_OK);
		return;
	}
	SetWindowText(hPanel, "Dialog");
	ShowWindow(hPanel, SW_SHOWNORMAL);
	UpdateWindow(hPanel);
	SetFocus(hPanel);


	panels = vector<Panel*>();
	for (int i = 0; i < panelsCount; i++)
	{
		LabeledEditText* panel = new LabeledEditText(i, config[i], hPanel, hInstance);
		panel->show();
		panels.push_back(panel);
	}
	HWND hPanBut1 = NULL;
	HWND hPanBut2;
	HWND hPanBut3;
	if (!first)
	{
		hPanBut1 = CreateWindow(TEXT("button"), TEXT("Назад"),
								WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
								90, 30 + (panelsCount) * 60, 80, 23, hPanel,
								(HMENU)IDB_PREVIOUS, hInstance, NULL);
	}
	if (!last) {
		hPanBut2 = CreateWindow(TEXT("button"), TEXT("Далі"),
								WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
								180, 30 + (panelsCount) * 60, 90, 23, hPanel,
								(HMENU)IDB_NEXT, hInstance, NULL);
	}
	else {
		hPanBut2 = CreateWindow(TEXT("button"), TEXT("Завершити"),
								WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
								180, 30 + (panelsCount) * 60, 90, 23, hPanel,
								(HMENU)IDB_SAVE, hInstance, NULL);
	}
	hPanBut3 = CreateWindow(TEXT("button"), TEXT("Відмінити"),
							WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_CENTER,
							280, 30 + (panelsCount) * 60, 80, 23, hPanel,
							(HMENU)IDB_CANCEL, hInstance, NULL);
	SetWindowLong(hPanel, GWLP_USERDATA, (long)this);


}
LRESULT CALLBACK Dialog::actionHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int wmId = LOWORD(wParam);
	map<string, string> m;
	switch (msg)
	{
	case WM_COMMAND:
		switch (wmId)
		{
		case IDB_CANCEL:
			DestroyWindow(hwnd);
			UnregisterClass(className, GetModuleHandle(NULL));
			return 0;
			break;
		case IDB_NEXT:
			m = map<string, string>();
			for (int i = 0; i < config.size(); i++)
			{
				m.insert(panels.at(i)->collectData());
			}
			DestroyWindow(hwnd);
			UnregisterClass(className, GetModuleHandle(NULL));
			loader->save(m);
			break;
		case IDB_PREVIOUS:
			DestroyWindow(hwnd);
			UnregisterClass(className, GetModuleHandle(NULL));
			loader->previous();
			break;
		case IDB_SAVE:
			m = map<string, string>();
			for (int i = 0; i < config.size(); i++)
			{
				m.insert(panels.at(i)->collectData());
			}
			DestroyWindow(hwnd);
			loader->save(m);
			break;
		}
		break;
	case WM_DESTROY:
		DestroyWindow(hwnd);
		UnregisterClass(className, GetModuleHandle(NULL));
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}



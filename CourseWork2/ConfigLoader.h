#pragma once
#include <string>
#include <vector>

using namespace std;

class ConfigLoader
{
private:
	string file;
public:
	ConfigLoader(string);
	~ConfigLoader();
	std::vector<std::vector<string>> getConfig();
};


#pragma once
#include <iostream>
#include <string>
#include <regex>

using std::cin;
using std::cout;

using std::string;

class Util
{
public:
	Util();
	~Util();
	
	static string toLower(string string);
	static int getUserInteger(int min, int max, string errMsg);
};


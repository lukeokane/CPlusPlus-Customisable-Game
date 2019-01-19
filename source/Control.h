#pragma once
#include <regex>
#include <windows.h>

#include "Character.h"
#include "RoomStore.h"

using std::cin;

class Control
{

private:
	HANDLE cmdLine = GetStdHandle(STD_OUTPUT_HANDLE);
	Character character;
	RoomStore rooms;

	void mainMenu();
	void load();

	string goTo(string &roomName);
	string use(string &objXName, string &objYName);
	string examineObj(string &objName);
	string open(string &objName);

	void displayCMDS();
	void displayCurrentRoom();
	void displayPlot();
public:

	Control();

	void action();

	~Control();
};


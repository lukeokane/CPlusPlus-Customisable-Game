#pragma once
#include "Object.h"

#include "CircularHeader.h"

#include <list>
#include <iostream>
#include <iomanip>

using std::ostream;

using std::list;
using std::cout;

class Character
{

private:

	Room* currentRoom;
	list<Object*> *inventory;

public:
	Character();
	Character(Room* currentRoom, list<Object*> *inventory);

	Room* getCurrentRoom();
	list<Object*> *getInventory();
	Object* getInvObject(string objectName);

	friend ostream& operator<< (ostream &out, Character &c);

	void setCurrentRoom(Room *c);
	void setInventory(list<Object*> *i);

	void print();
	Object* pickUp(string &objName);
	Object* drop(string &objName);

	~Character();

};


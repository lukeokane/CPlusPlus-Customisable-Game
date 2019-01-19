#ifndef ROOM
#define ROOM
#include "Object.h"

#include "CircularHeader.h"

#include <iostream>
#include <string>
#include <list>
#include <set>
#include <iomanip>
#include <istream>

using std::string;
using std::cout;
using std::endl;
using std::list;
using std::set;
using std::istream;


class Room
{

private:
	int id;
	string name;
	string description;
	set<Door*> *exits;
	list<Object*> *objects;

public:
	Room();
	// Constructor without exits variable passed
	Room(int id, string name, string description, list<Object*> *objects);
	// Constructor with exits variable passed
	Room(int id, string name, string description, set<Door*> *exits, list<Object*> *objects);

	int getID();
	string getName();
	string getDescription();
	set<Door*> *getExits();
	list<Object*> *getObjects();
	Door* getDoor(string doorName);
	Object* getObject(string objectName);

	void setID(int i);
	void setName(string n);
	void setDescription(string d);
	void setExits(set<Door*> *e);
	void setObjects(list<Object*> *o);

	void print();

	friend istream& operator>> (istream &in, Room &r);

	~Room();

};

#endif
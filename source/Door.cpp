#include "Door.h"


Door::Door() : Object(), id(0), connectedRoom(0), isOpen(false) {};
Door::Door(string name, string description, bool visible, int id, Room *r, bool isOpen) : Object(name, description, visible), id(id), connectedRoom(r), isOpen(isOpen) {};

string Door::examine()
{
	if (isOpen)
	{
		return string("The door appears to be open...\nThis door leads to the " + connectedRoom->getName() + ".");
	}
	else
	{
		return string("The door appears to be closed...\nThis door leads to the " + connectedRoom->getName() + ".");
	}
}

string Door::open()
{
	if (isOpen)
	{
		return string("The door is already open...");
	}
	else
	{
		return string("The door doesn't move.");
	}
}

string Door::useWith(Object& object)
{
	return string("You can't use a door with anything...");
}

int Door::getId()
{
	return id;
}

Room* Door::getConnectedRoom()
{
	return connectedRoom;
}

void Door::setId(int i)
{
	if (i > 0)
	{
		id = 0;
	}
}
bool Door::getOpenStatus()
{
	return isOpen;
}

void Door::setConnectedRoom(Room* r)
{
	connectedRoom = r;
}

void Door::setOpenStatus(bool b)
{
	isOpen = b;
}

/*
Get object data from istream and set object data.
*/
istream& operator>> (istream &in, Door &d)
{
	// Delimeter between each argument
	char delim = '|';

	string name;
	string desc;
	bool visible;

	getline(in, name, delim);
	getline(in, desc, delim);
	in >> visible >> delim;
	in >> d.id >> delim;
	in >> d.isOpen;

	d.setName(name);
	d.setDescription(desc);
	d.setVisibility(visible);

	// Ignore rest of line.
	in.ignore();

	return in;
}


Door::~Door()
{
}

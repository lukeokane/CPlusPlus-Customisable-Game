#include "Key.h"

Key::Key() : Object(), doorId(0) {}

Key::Key(string name, string description, bool visible, int doorId) : Object(name, description, visible), doorId(doorId) {};

string Key::examine()
{
	return getDescription();
}

string Key::open()
{
	return string("Nothing happens...");
}

string Key::useWith(Object &object)
{

	Door *door = dynamic_cast<Door*>(&object);

	// object is not a door object.
	if (door == nullptr)
	{
		return string("Nothing happens.");
	}
	else if (door->getId() == doorId)
	{
		if (door->getOpenStatus() == true)
		{
			door->setOpenStatus(false);
			return string("You have locked the door.");
		}
		else
		{
			door->setOpenStatus(true);
			return string("You hear the door unlock.");
		}
	}
	else
	{
		return string("It won't seem to fit this door.");
	}

	return string("Error on Key::useWith()");
}

int Key::getDoorId()
{
	return doorId;
}

/*
Get object data from istream and set object data.
*/
istream& operator>>(istream & in, Key & k)
{
	// Delimeter between each argument
	char delim = '|';

	string name;
	string desc;
	bool visible;

	getline(in, name, delim);
	getline(in, desc, delim);
	in >> visible >> delim;
	in >> k.doorId;

	k.setName(name);
	k.setDescription(desc);
	k.setVisibility(visible);

	// Ignore rest of line.
	in.ignore();

	return in;
}


Key::~Key()
{
}

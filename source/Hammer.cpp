#include "Hammer.h"

Hammer::Hammer() : Object(), hammerId(0), broken(false) {}

Hammer::Hammer(string name, string description, bool visible, bool broken, int hammerId) : Object(name, description, visible), hammerId(hammerId), broken(broken){};

string Hammer::examine()
{
	return this->getDescription();
}

string Hammer::open()
{
	return string("Nothing happens...");
}

string Hammer::useWith(Object &object)
{

	Door *door = dynamic_cast<Door*>(&object);

	// object is not a Door object.
	if (door == nullptr)
	{
		return string("Nothing happens.");
	}
	else
	{
		if (!broken)
		{
			door->setOpenStatus(true);
			setBroken(true);
			setDescription("The hammer is broken... it isn't any good!");
			return string("You hear the door handle smash, the door opens.");
		}
		else
		{
			return string("The hammer is broken... it isn't any good!");
		}
	}
	return string("Error on Hammer::useWith()");

}

int Hammer::getHammerId()
{
	return hammerId;
}

bool Hammer::getBroken()
{
	return broken;
}

void Hammer::setHammerId(int s)
{
	hammerId = s;
}

void Hammer::setBroken(bool b)
{
	broken = b;
}

/*
Get object data from istream and set object data.
*/
istream& operator>> (istream &in, Hammer &k)
{
	// Delimeter between each argument
	char delim = '|';

	string name;
	string desc;
	bool visible;

	getline(in, name, delim);
	getline(in, desc, delim);
	in >> visible >> delim;
	in >> k.broken >> delim;
	in >> k.hammerId;

	k.setName(name);
	k.setDescription(desc);
	k.setVisibility(visible);

	// Ignore rest of line.
	in.ignore();

	return in;
}

Hammer::~Hammer()
{
}
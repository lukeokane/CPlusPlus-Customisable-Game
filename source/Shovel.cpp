#include "Shovel.h"


Shovel::Shovel() : Object(), shovelId(0) {}

Shovel::Shovel(string name, string description, bool visible, int shovelId) : Object(name, description, visible), shovelId(shovelId) {};


string Shovel::examine()
{
	//return string("This Shovel looks like the one on sale in Woodies DIY last month!");
	return this->getDescription();
}

string Shovel::open()
{
	return string("Nothing happens...");
}

string Shovel::useWith(Object &object)
{

	Soil *soil = dynamic_cast<Soil*>(&object);

	// object is not a Soil object.
	if (soil == nullptr)
	{
		return string("Nothing happens.");
	}
	else
	{
		if (!soil->getIsDug())
		{
			soil->setDescription("The soil is already been dug up.");
			return string("You dig up the soil...\n" + soil->getContents());
		}
		else
		{
			return "The soil has already been dug up...\n" + soil->getContents();
		}
	}

}

int Shovel::getShovelId()
{
	return shovelId;
}

void Shovel::setShovelId(int s)
{
	shovelId = s;
}

/*
Get object data from istream and set object data.
*/
istream& operator>> (istream &in, Shovel &k)
{
	// Delimeter between each argument
	char delim = '|';

	string name;
	string desc;
	bool visible;

	getline(in, name, delim);
	getline(in, desc, delim);
	in >> visible >> delim;
	in >> k.shovelId;

	k.setName(name);
	k.setDescription(desc);
	k.setVisibility(visible);

	// Ignore rest of line.
	in.ignore();

	return in;
}

Shovel::~Shovel()
{
}
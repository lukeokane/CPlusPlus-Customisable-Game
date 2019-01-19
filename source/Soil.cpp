#include "Soil.h"


Soil::Soil() : Object(), contents(""), isDug(false) {}

Soil::Soil(string name, string description, bool visible, string contents, bool dug) : Object(name, description, true), contents(contents), isDug(dug) {};

string Soil::examine()
{
	return getDescription() + " " + contents;
}

string Soil::open()
{
	return string("Nothing happens...") ;
}

string Soil::useWith(Object &object)
{
	return string("Nothing happens...");
}

bool Soil::getIsDug()
{
	return isDug;
}

string Soil::getContents()
{
	return contents;
}

void Soil::setContents(string f)
{
	contents = f;
}

void Soil::setIsDug(bool i)
{
	isDug = i;
}

/*
Get object data from istream and set object data.
*/
istream& operator>> (istream &in, Soil &k)
{
	// Delimeter between each argument
	char delim = '|';

	string name;
	string desc;
	bool visible;

	getline(in, name, delim);
	getline(in, desc, delim);
	in >> visible >> delim;
	getline(in, k.contents, delim);
	in >> k.isDug;

	k.setName(name);
	k.setDescription(desc);
	k.setVisibility(visible);

	// Ignore rest of line.
	in.ignore();

	return in;
}

Soil::~Soil()
{
}

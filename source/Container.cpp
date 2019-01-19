#include "Container.h"

Container::Container() : Object(), evidence("", "", true,  0 , "") {}

Container::Container(string name, string description, bool visible, Note &evidence) : Object(name, description, visible), evidence(evidence) {};

string Container::examine()
{
	return this->getDescription();
}

string Container::open()
{
	return evidence.getNoteContents();
}

string Container::useWith(Object &object)
{
	return string("Nothing happens.");
}

Note Container::getEvidence()
{
	return evidence;
}

void Container::setEvidence(Note e)
{
	evidence = e;
}

/*
Get object data from istream and set object data.
*/
istream& operator>> (istream &in, Container &k)
{
	// Delimeter between each argument
	char delim = '|';

	string name;
	string desc;
	bool visible;

	getline(in, name, delim);
	getline(in, desc, delim);
	in >> visible >> delim;

	k.setName(name);
	k.setDescription(desc);
	k.setVisibility(visible);

	Note *n = new Note();
	in >> *n;

	k.setEvidence(*n);

	delete n;

	return in;
}

Container::~Container()
{
	
}

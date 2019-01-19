#include "Room.h"

Room::Room()
{
	id = 0;
	name = "Default room";
	description = "Default desc.";

	exits = new set<Door*>;
	objects = new list<Object*>;
}

Room::Room(int i, string n, string d, list<Object*> *o)
{
	id = i;
	name = n;
	description = d;

	exits = new set<Door*>;
	objects = o;
}

Room::Room(int i, string n, string d, set<Door*> *e, list<Object*> *o)
{
	id = i;
	name = n;
	description = d;
	exits = e;
	objects = o;
}

int Room::getID()
{
	return id;
}

string Room::getName()
{
	return name;
}

string Room::getDescription()
{
	return description;
}

set<Door*>* Room::getExits()
{
	return exits;
}

list<Object*>* Room::getObjects()
{
	return objects;
}

/*
To be commented
*/
Door* Room::getDoor(string doorName)
{
	doorName = Util::toLower(doorName);

	for (Door* d : *exits)
	{
		if (Util::toLower(d->getName()) == doorName)
		{
			return d;
		}
	}
	return nullptr;
}

/*
To be commented
*/
Object* Room::getObject(string objectName)
{
	objectName = Util::toLower(objectName);

	for (Object* o : *objects)
	{
		if (Util::toLower(o->getName()) == objectName)
		{
			return o;
		}
	}
	return nullptr;
}

void Room::setID(int i)
{
	id = i;
}

void Room::setName(string n)
{
	name = n;
}

void Room::setDescription(string d)
{
	description = d;
}

void Room::setExits(set<Door*> *e)
{
	exits = e;
}

void Room::setObjects(list<Object*> *o)
{
	objects = o;
}

void Room::print() // just a quick print method for testing
{
	cout << "You are inside the " << name << "..." << endl
		<< description << endl << endl;
	
	list<Object>::size_type exitSize = exits->size();

	if (exitSize > 0)
	{
		if (exitSize == 1)
		{
			cout << "There is 1 exit..." << endl;
		}
		else
		{
			cout << "There are " << exitSize << " exits..." << endl;
		}

		cout << string(20, '-') << endl;

		for (Door *d : *exits)
		{
			cout << d->getDescription() << endl;
		}
		cout << endl;
	}

	set<Door>::size_type objectSize = objects->size();
	if (objectSize > 0)
	{
		if (objectSize == 1)
		{
			cout << "There is an item in the area..." << endl;
		}
		else
		{
		cout << "There are some items in the area..." << endl;
		}

		cout << string(20, '-') << endl;

		for (Object *obj : *objects)
		{
			if (obj->getVisibility())
			{
				cout << std::setw(25) << std::left << obj->getName() << obj->getDescription() << endl;
			}
		}
		cout << endl;
	}
	
}

/*
Get object data from istream and set object data.
*/
istream& operator>> (istream &in, Room &r)
{
	char delim = '|';

	in >> r.id >> delim;
	getline(in, r.name, delim);
	getline(in, r.description);
	return in;
}

Room::~Room()
{
	// Destroy pointers.
	if (objects != nullptr)
	{
			for (list<Object*>::iterator i = objects->begin(); i != objects->end(); i++)
			{
				delete *i;
			}
		delete objects;
	}

	if (exits != nullptr)
	{
			for (set<Door*>::iterator i = exits->begin(); i != exits->end(); i++)
			{
				delete *i;
			}
		delete exits;
	}
}

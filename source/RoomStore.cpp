#include "RoomStore.h"

void RoomStore::loadRoomStore()
{
	for (vector<Room*>::iterator i = rooms.begin(); i != rooms.end(); ++i)
	{
		delete *i;
	}
	rooms.clear();

	ifstream in;
	in.open("C:\\CPP\\rooms.txt");

	Room *r = nullptr;

	// Check if next line being passed in is a door, at this stage then rooms are fully made.
	bool doors = false;

	while (!in.eof())
	{

		// Delimeter of each data.
		char delim = '|';

		// Checks what datatype is being passed in
		string identifier;
		getline(in, identifier, delim);

		// Check if line is a Room object
		if (identifier == "R")
		{
			// New room and fill in details
			r = new Room();
			in >> *r;
		}
		// Check if line is an object
		else if (identifier == "O")
		{
			string type;
			getline(in, type, delim);

			if (type == "Container")
			{
				Container *c = new Container();
				in >> *c;
				r->getObjects()->push_back(c);
			}
			else if (type == "Hammer")
			{
				Hammer *h = new Hammer();
				in >> *h;
				r->getObjects()->push_back(h);
			}
			else if (
				type == "Key")
			{
				Key *k = new Key();
				in >> *k;
				r->getObjects()->push_back(k);
			}
			else if (type == "Note")
			{
				Note *n = new Note();
				in >> *n;
				r->getObjects()->push_back(n);
			}
			else if (type == "Soil")
			{
				Soil *s = new Soil();
				in >> *s;
				r->getObjects()->push_back(s);
			}
			else if (type == "Shovel")
			{
				Shovel *s = new Shovel();
				in >> *s;
				r->getObjects()->push_back(s);
			}
		}
		// Check if line is a Door object to connect it to an already made room.
		else if (identifier == "D")
		{
			int doorRoomId;
			int doorConnectedId;

			in >> doorRoomId >> delim;
			in >> doorConnectedId >> delim;

			// Get roomID of room the door is in.
			Room* doorRoom = getRoom(doorRoomId);
			// Get roomID of room it is connecting to.
			Room* doorConnectedRoom = getRoom(doorConnectedId);

			Door *d = new Door();
			in >> *d;
			d->setConnectedRoom(doorConnectedRoom);
			doorRoom->getExits()->insert(d);
		}

		if (!in.eof())
		{
			// Get current line.
			int currentLine = in.tellg();
			string nextIdentifier;

			// Check ahead what the next identifier will be.
			getline(in, nextIdentifier, delim);
			
			// Go back to currentLine position
			in.seekg(currentLine, std::ios_base::beg);

			// Push room when going onto next room or end of loading rooms and objects
			if (nextIdentifier == "R" || (nextIdentifier != "O" && doors == false))
			{
				rooms.push_back(r);
				r = new Room();

				// If next line is a door object, then all rooms and room objects have been loaded.
				if (nextIdentifier == "D")
				{
					doors = true;
				}
			}
		}
		else if (in.eof() && !doors)
		{

			rooms.push_back(r);

		}
	}

	in.close();
}

/*
Get room by room ID

@param - roomID

@return pointer to room that has the matching room ID, else a null pointer is returned.
*/
Room* RoomStore::getRoom(int roomID)
{
	for (Room* r : rooms)
	{
		if (r->getID() == roomID)
		{
			return r;
		}
	}
	return nullptr;
}


void RoomStore::printAll()
{
	for (Room *r : rooms)
	{
		r->print();
	}
}

RoomStore::RoomStore()
{
	vector<Room*> r;
	rooms = r;

}

RoomStore::RoomStore(vector<Room*> r) : rooms(r)
{
	rooms = r;
}

RoomStore::~RoomStore()
{
	// Destroy pointers.
	for (vector<Room*>::iterator i = rooms.begin(); i != rooms.end(); ++i)
	{
		delete *i;
	}
}


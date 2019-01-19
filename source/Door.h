#ifndef DOOR
#define DOOR


#include "CircularHeader.h"
#include "Object.h"

class Door :
	public Object
{

public:
	Door();
	Door(string name, string description, bool visible, int id, Room *r, bool isOpen);
	~Door();
	//implement interface Object
	string examine();
	string useWith(Object& object);
	string open();

	int getId();
	Room* getConnectedRoom();
	bool getOpenStatus();

	void setId(int i);
	void setConnectedRoom(Room* r);
	void setOpenStatus(bool b);

	friend istream& operator>> (istream &in, Door &d);

private:
	int id;
	Room *connectedRoom;
	bool isOpen;
};

#endif
#pragma once
#include "Object.h"
#include "CircularHeader.h"

class Key : public Object
{

public:
	Key();
	Key(string name, string description, bool visible, int doorId);
	~Key();
	//implement interface Object
	string examine();
	string open();
	string useWith(Object& object);

	int getDoorId();

	friend istream& operator>> (istream &in, Key &c);

private:
	int doorId;
};




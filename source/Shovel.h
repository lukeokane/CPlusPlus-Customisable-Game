#pragma once
#include "Object.h"
#include "Soil.h"

class Shovel :
	public Object
{


public:
	Shovel();
	Shovel(string name, string description, bool visible, int shovelId);
	~Shovel();

	//implement interface Object
	string examine();
	string open();
	string useWith(Object& object);

	void setShovelId(int shovelId);
	int getShovelId();

	friend istream& operator>> (istream &in, Shovel &s);

private:
	int shovelId;

};


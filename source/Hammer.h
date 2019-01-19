#pragma once
#include "Object.h"

#include "CircularHeader.h"

class Hammer : public Object
{

public:
	Hammer();
	Hammer(string name, string description, bool visible, bool broken, int hammerId);
	~Hammer();

	//implement interface Object
	string examine();
	string open();
	string useWith(Object& object);

	int getHammerId();
	bool getBroken();
	void setHammerId(int hammerId);
	void setBroken(bool b);

	friend istream& operator>> (istream &in, Hammer &h);

private:
	int hammerId;
	bool broken;

};


#pragma once
#include "Object.h"
class Soil : public Object
{

public:
	Soil();
	Soil(string name, string description, bool visible, string contents, bool isDug);
	~Soil();

	//implement interface Object
	string examine();
	string open();
	string useWith(Object& object);

	bool getIsDug();
	string getContents();
	void setContents(string f);
	void setIsDug(bool dug);

	friend istream& operator>> (istream &in, Soil &s);
private:
	bool isDug;
	string contents;

};


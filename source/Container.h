#pragma once
#include "list"

#include "Util.h"
#include "Object.h"
#include "Note.h"

using std::list;

class Container : public Object
{

public:
	Container();
	Container(string name, string description, bool visible, Note &evidence);
	~Container();

	//implement interface Object
	string examine();
	string open();
	string useWith(Object& object);
	
	void setEvidence(Note evidence);
	Note getEvidence();

	friend istream& operator>> (istream &in, Container &c);

private:
	Note evidence;

};


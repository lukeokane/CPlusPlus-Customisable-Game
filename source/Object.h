#pragma once

#include <iostream>
#include <string>
#include <istream>

using std::string;
using std::ostream; // For opertor << overloading in child classes
using std::istream; // For opertor >> overloading in child classes

class Object
{

public:
	virtual ~Object() {}
	Object();
	Object(string n, string d, bool visible);

	virtual string examine() = 0;
	virtual string open() = 0;
	virtual string useWith(Object& object) = 0;

	string getName();
	string getDescription();
	bool getVisibility();

	void setName(string n);
	void setDescription(string d);
	void setVisibility(bool v);

private:
	string name;
	string description;
	bool visible;
};


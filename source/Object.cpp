#include "Object.h"

Object::Object() : name("Default Object"), description("Default description"), visible(true) {};

Object::Object(string n, string d, bool v) : name(n), description(d), visible(v) {};

string Object::getName()
{
	return name;
}

string Object::getDescription()
{
	return description;
}

bool Object::getVisibility()
{
	return visible;
}

void Object::setName(string n)
{
	name = n;
}

void Object::setDescription(string d)
{
	description = d;
}

void Object::setVisibility(bool v)
{
	visible = v;
}
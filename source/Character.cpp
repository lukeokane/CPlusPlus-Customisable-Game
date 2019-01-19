#include "Character.h"

Character::Character()
{
	currentRoom = 0;
	inventory = 0;
};

Character::Character(Room* c, list<Object*> *i)
{
	currentRoom = c;
	inventory = i;
}

Room* Character::getCurrentRoom()
{
	return currentRoom;
}

list<Object*>* Character::getInventory()
{
	return inventory;
}

Object* Character::getInvObject(string objectName)
{
	objectName = Util::toLower(objectName);

	for (Object* o : *inventory)
	{
		if (Util::toLower(o->getName()) == objectName)
		{
			return o;
		}
	}
	return nullptr;
}

void Character::setCurrentRoom(Room *c)
{
	currentRoom = c;
}

void Character::setInventory(list<Object*> *i)
{
	inventory = i;
}

void Character::print()
{
	cout << "print";
}

/*
Return character's information.

@param out - ostream data object to return to.
@param c - character to get the information from.

@return - ostream with character's data.
*/
ostream & operator<<(ostream &out, Character &c)
{
	if (!c.getInventory()->empty())
	{
		for (Object* charObj : *c.getInventory())
		{
			out << std::setw(8) << std::left << charObj->getName() << "\t" << charObj->getDescription() << endl;
		}
	}
	else
	{
		out << "There is nothing in your inventory." << endl << endl;
	}

	out << endl;
	return out;
}

/*
Pick up object from the room and add it to user's inventory. Check if user's input matches an object name in the room.

@param objName - name of object to be picked up.

@return - Object point if such an object exists, else returns a nullptr
*/
Object* Character::pickUp(string &objName)
{
	string objectName = Util::toLower(objName);

	list<Object*> *roomObjects = getCurrentRoom()->getObjects();

	for (list<Object*>::iterator iter = roomObjects->begin(); iter != roomObjects->end(); iter++)
	{
		if (Util::toLower((*iter)->getName()) == objectName)
		{
			Object* obj = *iter;
			getInventory()->push_back(*iter);
			iter = roomObjects->erase(iter);
			return obj;
		}
	}

	return nullptr;
}

/*
Take in and validate user integer from keyboard, prompts user of error until valid integer is entered.

@param min (optional) - Minimum value of integer.
@param max (optional) - Maximum value of integer.
@param errMsg (optional) - Message displayed if integer is outside min-max range.

@return 'int' data type when integer passes all validation.
*/
Object* Character::drop(string &objName)
{

	string objectName = Util::toLower(objName);

	list<Object*> *charObjects = getInventory();

	for (list<Object*>::iterator iter = charObjects->begin(); iter != charObjects->end(); iter++)
	{
		if (Util::toLower((*iter)->getName()) == objectName)
		{
			Object* obj = *iter;
			getCurrentRoom()->getObjects()->push_back(*iter);
			iter = charObjects->erase(iter);
			return obj;
		}
	}
	
	return nullptr;
}

Character::~Character()
{
	// Destroy pointers, check if inventory is set
	if (inventory != 0)
	{
		for (list<Object*>::iterator i = inventory->begin(); i != inventory->end(); ++i)
		{
			delete *i;
		}
	}
}

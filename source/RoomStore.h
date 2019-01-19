#pragma once
class Room;
class Door;

#include <vector>
#include <iostream>
#include "CircularHeader.h"
#include "Key.h"

#include <fstream>
#include <list>
#include <set>

using std::vector;
using std::string;

using std::list;
using std::set;
using std::ifstream;

class RoomStore
{

private:

	vector<Room*> rooms;

public:

	void loadRoomStore();
	void printAll();

	Room* getRoom(int roomID);

	RoomStore();
	RoomStore(vector<Room*> r);
	~RoomStore();

};


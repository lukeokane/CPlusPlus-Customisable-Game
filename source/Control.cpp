#include "Control.h"

Control::Control()
{
	mainMenu();
	
	cout << "Exiting..." << endl;
}

/*
Take in user input and perform their request (e.g "go to hall", "examine sitting room")

@return - None.
*/
void Control::action()
{
	string action;

	while (action != "quit")
	{
		cout << "Type 'help' for commands" << endl << endl;

		// Get action in from user
		cout << "What would you like to do: ";
		getline(cin, action);

		system("CLS");

		if (action.substr(0, 6) == "go to ")
		{
			string roomName = action.substr(6, action.length());

			string goToResponse = goTo(roomName);

			displayCurrentRoom();

			cout << goToResponse << endl << endl;
		}
		else if (action == "help" || action == "commands" || action == "cmds")
		{
			displayCurrentRoom();
			displayCMDS();
		}
		else if (action == "inventory")
		{
			displayCurrentRoom();
			cout << character;
		}
		else if (action == "restart")
		{
			load();

			system("cls");
			displayPlot();

			displayCurrentRoom();

			cout << "Game Restarted" << endl << endl;
		}
		else if (action.substr(0, 4) == "use ")
		{
			string objectXName, objectYName;

			// Checking structure of the action to see if it in the format "use X with Y"...
			// ... "use" is already validated so remove.
			action.erase(0, 4);

			string::size_type pos;

			// Check if format is structured correctly
			if ((pos = action.find(" with ")) != string::npos)
			{
				objectXName = action.substr(0, pos);
				objectYName = action.substr(pos + 6, action.length());

				string useWith = use(objectXName, objectYName);
				displayCurrentRoom();
				cout << useWith << endl << endl;
			}
			else
			{
				displayCurrentRoom();
				cout << "Cannot understand what you are trying to use." << endl << endl;
			}
		}
		else if (action.substr(0, 8) == "examine ")
		{
			string objectToExamine = action.substr(8, action.length());

			displayCurrentRoom();
			cout << examineObj(objectToExamine) << endl << endl;
		}
		else if (action.substr(0, 8) == "pick up ")
		{
			string objectToPickUp = action.substr(8, action.length());

			Object* obj = character.pickUp(objectToPickUp);

			displayCurrentRoom();

			if (obj != nullptr)
			{
				cout << obj->getName() << " has been picked up" << endl << endl;
			}
			else
			{
				cout << "'" << objectToPickUp << "' is not in this area." << endl << endl;
			}
		}
		else if (action.substr(0, 5) == "drop ")
		{
			string objectToDrop = action.substr(5, action.length());

			Object* obj = character.drop(objectToDrop);

			displayCurrentRoom();
			if (obj != nullptr)
			{
				cout << obj->getName() << " has been dropped." << endl << endl;
			}
			else
			{
				cout << "'" << objectToDrop << "' is not in your bag." << endl << endl;
			}

		}
		else if (action.substr(0, 5) == "open ")
		{
			string openObject = action.substr(5, action.length());
			string openResponse = open(openObject);

			// Check if winning object is opened, if it is then they have one, else just display.
			if (character.getInvObject("old box") != nullptr && openObject == "old box")
			{
				for (int i = 1; i <= 10; i++)
				{
					cout << endl;
				}
				cout << openResponse << endl << endl;

				string congrats = " --- Congratulations, you found the evidence that will exonerate you! ---";

				cout << string(congrats.length(), '-') << endl;
				cout << " --- Congratulations, you found the evidence that will exonerate you! ---" << endl;
				cout << " --- Thank you for playing! ---" << endl << endl;

				action = "quit";
			}
			else
			{
				displayCurrentRoom();
				cout << openResponse << endl << endl;
			}

		}
		else if (action == "quit")
		{
			// Do nothing, loop will exit.
		}
		else
		{
			displayCurrentRoom();
			cout << "Unrecognized command " << endl << endl;
		}
	}
}

/*
Set up character and load in rooms + objects.

@return - None.
*/
void Control::load()
{
	// Load character items.
	list<Object*> *charInv = new list<Object*>;
	charInv->push_back(new Note("Note", "You entered the house with this note.", true, 1, "Under the ground, will you find what you seek...\nBut first you should get cooking."));
	character.setInventory(charInv);

	// Load rooms and objects.
	rooms.loadRoomStore();

	// Set character room to hall (room id is 1)
	character.setCurrentRoom(rooms.getRoom(1));
}

/*
Display main menu and react to user's request.

@return - None.
*/
void Control::mainMenu()
{
	int choice = 0;
	cout << "Welcome to our game..." << endl << endl;
	do
	{
		cout << "1. Start Game" << endl;
		cout << "2. Exit" << endl << endl;

		cout << "Select an option: ";
		choice = Util::getUserInteger(1, 2, "Invalid option...\nTry again.");

		switch (choice)
		{
		case 1:

			// Begin game
			load();
			system("cls");
			displayPlot();
			cout << "... you have a note in your backpack." << endl << endl;
			displayCurrentRoom();
			action();
			break;
		case 2:
			break;
		default:
			// Should not reach here with getUserInteger already checking that it is within range.
			cout << "An error has occurred..." << endl;
			break;
		}
	} while (choice != 2);


}

void Control::displayCurrentRoom()
{
	SetConsoleTextAttribute(cmdLine, 15);
	character.getCurrentRoom()->print();
	SetConsoleTextAttribute(cmdLine, 11);
}

string Control::goTo(string &rName)
{
	// Searched room name to lower.
	string roomName = Util::toLower(rName);
	// Get pointer to current character's room
	Room* currentRoom = character.getCurrentRoom();

	// Check all exits to see if a door has a Room object with that name.
	for (Door* d : *currentRoom->getExits())
	{
		// If Door::connectedRoom.name equals the searched room name
		if (d->getConnectedRoom()->getName() == roomName)
		{
			// Check if Door::isOpen is true, if it is then change character's room.
			if (d->getOpenStatus() == true)
			{
				character.setCurrentRoom(d->getConnectedRoom());
				return string("You are now in the " + character.getCurrentRoom()->getName() + ".");
			}
			else
			{
				return  string("The door appears to be locked.");
			}
		}
	}

	return string("There doesn't seem to be a door to the " + rName + " in here...");
}

/*
Use two Object objects on eachother, checks to see if the two items are in the inventory. ...
... displays relevant message (result of two objects being used on eachother, ...
... if the two objects are not valid).

@param objXName - An Object object in the user's inventory.
@param objYName - Object objects in current room.

@return - None.
*/
string Control::use(string &objXName, string &objYName)
{
	// Lower characters for comparison
	string objectXName = Util::toLower(objXName);
	string objectYName = Util::toLower(objYName);

	// Check if objectX is in inventory, will return pointer to object name that matches.
	Object* charObj = character.getInvObject(objectXName);

	// Return notification of objectX not in character inventory
	if (charObj == nullptr)
	{
		return string("'" + objectXName + "' is not in your inventory.");
	}

	// Check if objectY is a Door object, will return pointer to object name that matches.
	Door* doorObj = character.getCurrentRoom()->getDoor(objectYName);

	// If there is a match (valid pointer)...
	// ... return result of using objectX (charObj) with objectY (doorObj)
	if (doorObj != nullptr)
	{
		return charObj->useWith(*doorObj);
	}

	// Check if objectY is an Object object, will return pointer to object name that matches.
	Object* roomObj = character.getCurrentRoom()->getObject(objectYName);

	// If there is a match (valid pointer) ...
	// ... returns result of using objectX (charObj) with objectY (roomObj).
	if (roomObj != nullptr)
	{
		if (roomObj->getName() == "brown patch of soil" && charObj->getName() == "shovel")
		{
			roomObj->setDescription("The soil has already been dug up... there is an old box in here.");

			Object* winningObject = character.getCurrentRoom()->getObject("old box");

			if (winningObject != nullptr)
			{
				winningObject->setVisibility(true);
			}
		}

		if (charObj->getName() == "hammer")
		{
			dynamic_cast<Hammer*>(charObj)->setBroken(false);
		}
		return charObj->useWith(*roomObj);
	}

	// Return text saying objectY (a door or an object) is not found in the current room.
	return string("There is no such object called '" + objectYName + "' around here...");
}

/*
Display examine method of Object in the current room. ...
... Checks if the room has that object (including exits).

@param objName - An Object object in the user's inventory.

@return - None.
*/
string Control::examineObj(string &objName)
{
	// For matching
	string objectName = Util::toLower(objName);

	// Check if objectName is a name of an exit Door object, ...
	// ... will return pointer to object or 0 if not existant.
	Door *doorObj = character.getCurrentRoom()->getDoor(objName);

	// Runs examine method of object.
	if (doorObj != nullptr)
	{
		return doorObj->examine();
	}

	// Check if objectName is a name of an object in the room, ...
	// ... will return pointer to object or 0 if not existant.
	Object *charObj = character.getInvObject(objName);

	// Runs examine method of object.
	if (charObj != nullptr)
	{
		return charObj->examine();
	}

	// Display message if objectName does not exist in room.
	return string(objName + " is not examinable.");
}

/*
Call the open command of an object.

@param objName - object to be opened.

@return - None.
*/
string Control::open(string &objName)
{
	Object* obj = character.getInvObject(objName);

	if (obj != nullptr)
	{
			return obj->open();
	}
	else
	{
		return string(objName + " is not in your inventory.");
	}
}

/*
Display commands of the game for the user.

@return - None.
*/
void Control::displayCMDS()
{
	cout << "Commands" << endl;
	cout << string(8, '-') << endl << endl;
	cout << "quit - quit game" << endl;
	cout << "inventory - check what objects you have" << endl;
	cout << "examine 'object' - examine the object" << endl;
	cout << "go to 'room name' - enter a room" << endl;
	cout << "use 'object' with 'object' - use one object on another" << endl;
	cout << "pick up 'object' - put an object into your inventory" << endl;
	cout << "drop 'object' - drop an object on the ground'" << endl;
	cout << "open 'object' - open an object in your inventory" << endl << endl;
}

/*
Display the plot of the game.

@return - None.
*/
void Control::displayPlot()
{
	cout << "You have escaped from prison while being held for a murder that you did not commit, this has been the toughest year of your life, showering used to be your favourite thing in the world, but not anymore..." << endl;
	cout << "Your cell mate Timmy the tiddler had listened to your story and realised he actually knows the real killer and he was his old cell mate down in Guantanamo Bay before he got transferred here to Mountjoy..." << endl;
	cout << "Timmy the tiddler said the guy was bragging about how he didnt get caught but also was always worried about the gardai finding the gun used in the murder...." << endl;
	cout << "He said he hid the gun in an old abandoned house near DkIT where the murder took place, but before he realised he never cleaned his fingerprints off the gun, he was incarcerated again on an outstanding charge." << endl;
	cout << "Your only chance to clear your name is in that house and you are willing to try anything to get what you need." << endl;
	cout << "On your way to Dundalk circuit court from Mountjoy to answer to another charge, the prison bus crashed at the Xerox junction and you were the only one to survive, you run away down the road as fast as you can until you stumble upon the house that Timmy the tiddler told you about...." << endl;

	cout << "\nYou enter the murder house..." << endl;
}

Control::~Control()
{
}

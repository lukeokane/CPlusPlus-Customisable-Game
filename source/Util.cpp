#include "Util.h"


Util::Util()
{
}

string Util::toLower(string stringIn)
{
	transform(stringIn.begin(), stringIn.end(), stringIn.begin(), tolower);
	return stringIn;
}

/*
Take in and validate user integer from keyboard, prompts user of error until valid integer is entered.

@param min (optional) - Minimum value of integer.
@param max (optional) - Maximum value of integer.
@param errMsg (optional) - Message displayed if integer is outside min-max range.

@return 'int' data type when integer passes all validation.
*/
int Util::getUserInteger(int min, int max, string errMsg)
{
	int integer = 0;

	bool valid = true;

	do
	{
		cin >> integer;

		if (cin.fail())
		{
			valid = false;
			// Clearing error flags on cin.
			cin.clear();
			// Clearing buffer to the newline character at end of buffer.
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << "Invalid number, try again: ";
		}
		else if (min != INT_MAX && max != INT_MAX && (integer < min || integer > max))
		{
			valid = false;
			cout << errMsg;
		}
		else
		{
			// Clearing error flags on cin.
			cin.clear();
			// Clearing buffer to the newline character at end of buffer.
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			valid = true;
		}

	} while (valid == false);

	return integer;
}


Util::~Util()
{
}

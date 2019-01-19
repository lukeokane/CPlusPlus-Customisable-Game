#include "Note.h"

Note::Note() : Object(), noteId(0), contents("") {}

Note::Note(string name, string description, bool visible, int noteId, string contents) : Object(name, description, visible), noteId(noteId), contents(contents) {};

string Note::examine()
{
	return open();
}

string Note::open()
{
	return string("The note says: " + contents);
}

string Note::useWith(Object &object)
{
	return string("Nothing happens.");
}

int Note::getNoteId()
{
	return noteId;
}

void Note::setNoteId(int n)
{
	noteId = n;
}

string Note::getNoteContents()
{
	return contents;
}

void Note::setNoteContents(string c)
{
	contents = c;
}

/*
Get object data from istream.
*/
istream& operator>> (istream &in, Note &k)
{
	// Delimeter between each argument
	char delim = '|';

	string name;
	string desc;
	bool visible;

	getline(in, name, delim);
	getline(in, desc, delim);
	in >> visible >> delim;
	in >> k.noteId >> delim;
	getline(in, k.contents);

	k.setName(name);
	k.setDescription(desc);
	k.setVisibility(visible);

	return in;
}

Note::~Note()
{
}

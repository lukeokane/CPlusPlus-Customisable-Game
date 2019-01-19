#pragma once
#include "Object.h"
class Note : public Object
{

public:
	Note();
	Note(string name, string description, bool visible, int noteId, string contents);
	~Note();

	//implement interface Object
	string examine();
	string open();
	string useWith(Object& object);

	void setNoteId(int noteId);
	int getNoteId();
	void setNoteContents(string contents);
	string getNoteContents();

	friend istream& operator>> (istream &in, Note &n);
private:
	int noteId;
	string contents;

};


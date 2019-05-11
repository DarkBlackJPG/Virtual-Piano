#pragma once
#include "MusicSymbol.h"
#include <list>
#include <iostream>
class Measure
{
	std::pair<int, int> timeSignature;
	int measureID;
	std::list<MusicSymbol*> notes;

public:
	void changeTimeSignature(int, int);
	void changeTimeSignature(std::pair<int, int>);
	bool canAddSymbol(MusicSymbol& symbol);
	bool measureFull();
	std::list<MusicSymbol*> getNotes(){ return notes; };
	MusicSymbol * getSymbolAt(int index);
	int numberOfNotes() {
		return notes.size();
	}
	bool addSymbol(MusicSymbol& symbol);
	friend std::ostream& operator<< (std::ostream& stream, Measure& measure);
	Measure();
	~Measure() {
		for (auto a : notes)
			delete a;
	};
};


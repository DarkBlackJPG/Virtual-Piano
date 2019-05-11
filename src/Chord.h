#pragma once
#include "MusicSymbol.h"
#include "Note.h"
#include <list>
class Chord :
	public MusicSymbol
{
	std::list<Note*> notes;
	void abstracter() override {};
	bool split = false;
	Note* getNoteAt(int i);
public:
	bool addNote(Note* note) {
		notes.push_back(note);
		return true;
	}
	std::list<Note*> getNotesList() {
		return notes;
	}
	bool isSplit() override {
		return split;
	}
	bool isThisChord() override {
		return true;
	}
	bool isEmpty() {
		return notes.empty();
	}
	void shiftOctave(int octaveNumberShift) override;
	virtual int getMidiData() override;
	virtual std::ostream& write(std::ostream& stream) override;
	std::pair<MusicSymbol*, MusicSymbol*> splitSymbol() override;
	Chord(Duration::EDuration duration);
	virtual std::string generateMUSICXMLData(bool noteIsSplit = false, bool noteIsSecond = false) override;
	~Chord();
};


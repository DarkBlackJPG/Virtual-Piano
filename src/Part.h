#pragma once
#include "Measure.h"
#include <list>
#include <vector>

/// Part can be left or right depending on the octave
class Part
{
public:
	enum Type {
		RIGHTHAND,
		LEFTHAND
	};
	Part(Type type);
	~Part();
	std::pair<int, int> myTimeSignature;
	Measure* getMeasureAt(int index);
	int getNumberOfMeasures() {
		return measure.size();
	}
	static bool lastMeasureIsFull(Part* myPart);
	bool addNote(MusicSymbol* symbol);
	std::vector<MusicSymbol*> extractAllNotes();
	void importAllNotes(std::vector<MusicSymbol*>);
	void clear() {
		for (auto a : measure)
			delete a;
		measure.clear();
	}
	bool lastMeasureHasNotes();
	bool lastMeasureFull();
	std::list<Measure*> getMeasures() { return measure; }
	void killBack() { measure.pop_back(); }
private:
	std::list<Measure*> measure;
	Type handType;
};


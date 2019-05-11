#include "Part.h"
#include "Pause.h"
Part::Part(Part::Type type) : handType(type)
{
}

Measure * Part::getMeasureAt(int index)
{
	if ((unsigned)index < 0 || (unsigned)index >= measure.size())
		throw "Index out of range";
	std::list<Measure*>::iterator it = measure.begin();
	std::advance(it, index);
	return *it;
}

bool Part::lastMeasureIsFull(Part * myPart)
{
	return myPart->measure.back()->measureFull();
}

bool Part::addNote(MusicSymbol * symbol)
{
	if (measure.size() == 0) {
		Measure* newMeasure = new Measure();
		newMeasure->addSymbol(*symbol);
		newMeasure->changeTimeSignature(myTimeSignature);
		measure.push_back(newMeasure);
		return true;
	}
	else {
		if (measure.back()->canAddSymbol(*symbol)) {
			measure.back()->addSymbol(*symbol);
		}
		else if (measure.back()->measureFull()) {
			Measure* newMeasure = new Measure();
			newMeasure->addSymbol(*symbol);
			newMeasure->changeTimeSignature(myTimeSignature);
			measure.push_back(newMeasure);
		}
		else{
			std::pair<MusicSymbol*, MusicSymbol*> split = symbol->splitSymbol();
			if (measure.back()->canAddSymbol(*split.first)) {
				measure.back()->addSymbol(*split.first);
				Measure* newMeasure = new Measure();
				newMeasure->addSymbol(*split.second);
				newMeasure->changeTimeSignature(myTimeSignature);
				measure.push_back(newMeasure);
			}
			else
				std::cout << "Linija 36, Part.cpp";
		}
	}
	return false;
}

std::vector<MusicSymbol*> Part::extractAllNotes()
{
	std::vector<MusicSymbol*> symbols;
	for (auto a : measure) {
		for (int i = 0; i < a->numberOfNotes(); i++) {
			symbols.push_back(a->getSymbolAt(i));
		}
	}
	return symbols;
}

void Part::importAllNotes(std::vector<MusicSymbol*> symbols)
{
	if (measure.size() > 0)
		measure.clear();
	for (auto a : symbols) {
		addNote(a);
	}
}

bool Part::lastMeasureHasNotes()
{
	Measure* last = measure.back();
	bool hasNotes = false;
	for (auto var : last->getNotes()) {
		if (dynamic_cast<Pause*>(var) == nullptr)
		{
			hasNotes = true;
			break;
		}
	}
	return hasNotes;
}

bool Part::lastMeasureFull()
{
	double count = 0;
	return measure.back()->measureFull();
}

#include "Measure.h"

void Measure::changeTimeSignature(int a, int b)
{
	changeTimeSignature(std::pair<int, int>(a, b));
}

void Measure::changeTimeSignature(std::pair<int, int> pair)
{
	if (pair.second != 4 && pair.second != 8)
		throw "Incompatible time signature. The dividor can only be 4 or 8";
	timeSignature = pair;
}

bool Measure::canAddSymbol(MusicSymbol& symbol)
{
	double counter = 0;
	Duration newDuration = symbol.noteDuration();
	for (MusicSymbol* x : notes) {
			Duration temp = x->noteDuration();
			switch (temp.getDuration())
			{
			case Duration::QUARTER:
				counter += (timeSignature.second == 4) ? 1 : 2;
				break;
			case Duration::EIGHT:
				counter += (timeSignature.second == 4) ? 0.5 : 1;
				break;
			default:
				throw "Unhandled Exception!";
				break;
			
		}
	}
		switch (newDuration.getDuration())
		{
		case Duration::QUARTER:
			counter += (timeSignature.second == 4) ? 1 : 2;
			break;
		case Duration::EIGHT:
			counter += (timeSignature.second == 4) ? 0.5 : 1;
			break;
		default:
			throw "Unhandled Exception!";
			break;
		}

	if (counter <= timeSignature.first) {
		return true;
	}
	else {
		return false;
	}
}
bool Measure::measureFull()
{
	double counter = 0;
	for (MusicSymbol* x : notes) {
		Duration temp = x->noteDuration();
			switch (temp.getDuration())
			{
			case Duration::QUARTER:
				counter += (timeSignature.second == 4) ? 1 : 2;
				break;
			case Duration::EIGHT:
				counter += (timeSignature.second == 4) ? 0.5 : 1;
				break;
			default:
				throw "Unhandled Exception!";
				break;
			
		}
	}

	if (counter == timeSignature.first) return true;
	return false;
}
MusicSymbol * Measure::getSymbolAt(int index)
{
	if (index >= 0 && index < notes.size()) {
		std::list<MusicSymbol*>::iterator iterator = notes.begin();
		std::advance(iterator, index);
		return *iterator;
	}
	else {
		throw "Index out of range";
	}
}
/// If cant add, make new Measure, push Measure to list
bool Measure::addSymbol(MusicSymbol & symbol)
{
	if (canAddSymbol(symbol)) {
		notes.push_back(&symbol);
		return true;
	}
	return false;
}

Measure::Measure()
{
	timeSignature = std::pair<int, int>(4, 4);
}

std::ostream & operator<<(std::ostream & stream, Measure & measure)
{
	for (auto v : measure.notes) {
		stream << *v;
	}
	return stream;
}

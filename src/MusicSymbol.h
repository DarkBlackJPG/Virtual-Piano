#pragma once
#include "Duration.h"
#include <iostream>
#include <string>
class MusicSymbol
{
public:
	MusicSymbol(Duration duration);
	MusicSymbol(Duration::EDuration duration);
	virtual std::pair<MusicSymbol*, MusicSymbol*> splitSymbol() = 0;
	virtual ~MusicSymbol();
	Duration noteDuration() const {
		return *duration;
	}
	virtual bool isThisChord() {
		return false;
	}
	virtual int getMidiData() = 0;
	Duration* modifyDuration() {
		return duration;
	}
	virtual std::string generateMUSICXMLData(bool noteIsSplit = false, bool noteIsSecond = false) = 0;
	virtual std::string getName() { return ""; }
	virtual void shiftOctave(int octaveNumberShift) = 0;
	virtual std::ostream& write(std::ostream& stream) = 0;
	friend std::ostream& operator<<(std::ostream& stream, MusicSymbol& symbol) {
		return symbol.write(stream);
	}
	virtual bool isSplit() { return false; }
protected:
	Duration* duration;
	virtual void abstracter() = 0;
};


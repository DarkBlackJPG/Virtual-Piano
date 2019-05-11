#pragma once
#include "MusicSymbol.h"
class Pause :
	public MusicSymbol
{
	void abstracter() {};
	bool split;
public:
	/// Pause returns -1 for midiData because you don't have a midi code for a pause
	int getMidiData() override;
	void shiftOctave(int octaveNumberShift) override {};
	std::pair<MusicSymbol*, MusicSymbol*> splitSymbol() override;
	virtual std::ostream& write(std::ostream& stream) override {
		if (duration->getDuration() == Duration::QUARTER) {
			return stream << "(1/4)";
		}
		else {
			return stream << "(1/8)";
		}
	};
	bool isSplit() override {
		return split;
	}
	virtual std::string generateMUSICXMLData(bool noteIsSplit = false, bool noteIsSecond = false) override;
	Pause(Duration::EDuration duration);
	~Pause();
};


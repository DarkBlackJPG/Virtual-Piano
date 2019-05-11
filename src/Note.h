#pragma once
#include "MusicSymbol.h"
#include <string>
#include <locale>
#include <map>
class Note :
	public MusicSymbol
{
	void abstracter() {};
	std::string name;
	bool increased, split;
	int midiValue;
	bool isChord;
public:
	static std::map<char, std::pair<std::string, int>> notesMap;
	static std::map<std::string, int> octaveChangeMap;
	static std::map<int, std::string> midiMap;

	bool isSplit() override {
		return split;
	}
	int getMidiData() override;
	std::string getName() override { return name; }
	std::pair<MusicSymbol*, MusicSymbol*> splitSymbol() override;
	void shiftOctave(int octaveNumberShift) override;
	int getOctave();
	std::string getStep();
	Note(std::string name, int midiValue, Duration::EDuration duration);
	~Note();
	virtual std::string generateMUSICXMLData(bool noteIsSplit = false, bool noteIsSecond = false) override;
	void increaseOctave();
	bool isIncreased() {
		return increased;
	}
	void increasedNote(bool decrementIfIncreased = false);
	void changeNoteLetter(std::string);
	std::ostream& write(std::ostream& stream) {
		std::locale loc;
		if (duration->getDuration() == Duration::QUARTER) {
			name[0] = std::toupper(name[0], loc);
		}
		else {
			name[0] = std::tolower(name[0], loc);
		}
		return stream << "("+name+")";
	}
};


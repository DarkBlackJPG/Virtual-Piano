#include "Note.h"
#include <regex>
#include <iostream>
#include <sstream>
void toUpper(std::string&);
void toLower(std::string&);
std::map<char, std::pair<std::string, int>> Note::notesMap;
std::map<std::string, int> Note::octaveChangeMap;
std::map<int, std::string> Note::midiMap;




int Note::getMidiData()
{
	return midiValue;
}

std::pair<MusicSymbol*, MusicSymbol*> Note::splitSymbol()
{
	Note* leftPart, *rightPart;
	leftPart = new Note(this->name, this->midiValue, Duration::EIGHT);
	rightPart = new Note(this->name, this->midiValue, Duration::EIGHT);
	leftPart->split = true;
	rightPart->split = true;
	return std::pair<MusicSymbol*, MusicSymbol*>(leftPart, rightPart);
}

void Note::shiftOctave(int octaveNumberShift)
{

	std::regex pattern("([A-Za-z])([#])?([0-9])");
	std::smatch result;
	if (std::regex_match(name, result, pattern))
	{
		int octave = 0;
		octave = std::stoi(result.str(3).data()) + octaveNumberShift;
		if (octave < 2) {
			octave = 2;
		}
		if (octave > 6) {
			octave = 6;
		}
		name = result.str(1) + (result.str(2) != "" ? "#" : "") + std::to_string(octave);
		midiValue = octaveChangeMap[name];
	}
	
}

int Note::getOctave()
{
	std::regex pattern("[A-Za-z][#]?([0-9])");
	std::smatch result;
	if (std::regex_match(name, result,pattern))
	{
		return stoi(result.str(1));
	} 
	else {
		throw "Unhandled exception";
	}
}

std::string Note::getStep()
{
	std::regex pattern("([A-Za-z])[#]?[0-9]");
	std::smatch result;
	if (std::regex_match(name, result, pattern))
	{
		return result.str(1);
	}
	else {
		throw "Unhandled exception";
	}
}

Note::Note(std::string name, int midiValue, Duration::EDuration duration) : MusicSymbol(duration)
{
	std::regex pattern("([#])");
	std::smatch match;
	if (std::regex_search(name, match, pattern)) {
		increased = true;
	}
	else
		increased = false;
	this->name = name;
	this->midiValue = midiValue;
	this->split = false;
}

Note::~Note()
{
}

std::string Note::generateMUSICXMLData(bool noteIsSplit, bool noteIsSecond)
{
	std::string t = getStep();
	toUpper(t);
	std::string data =
		"<note>\n"
		"<pitch>\n"
		"<step>"+t+"</step>\n"
		"<octave>"+std::to_string(getOctave())+"</octave>\n" 
		+ ((increased == true) ? "<alter>1</alter>\n" : "")+
		"</pitch>\n<duration>"+((duration->getDuration() == Duration::QUARTER)? "2":"1")+"</duration>\n"
		+ std::string(noteIsSplit == true ? ((noteIsSecond == false) ? "<tie type=\"start\"/>\n" : "<tie type=\"end\"/>\n") : "") +
		"</note>\n";
	return data;
}

void Note::increaseOctave()
{
	try {
		std::regex pattern("([A-Za-z])+([0-9])?");
		std::smatch match;
		if (std::regex_search(name, match, pattern)) {
			int temp = atoi(match.str(2).data());
			if (temp == 6)
				throw "Ne moze da se poveca";
			
			std::stringstream ss;
			ss << temp + 1;
			name = match.str(1) + ss.str();
			midiValue = octaveChangeMap[name];
		}
	}
	catch (std::string ex) {
		std::cout << ex << std::endl;
	}
}

void Note::increasedNote(bool decrementIfIncreased)
{
	if (!increased) {
		std::regex pattern("([A-Za-z])([0-9])");
		std::smatch result;
		if (std::regex_match(name, result, pattern) && result.str(1) != "E" && result.str(1) != "B") {
			name = result.str(1) + "#" +result.str(2);
			increased = true;
		}

	}
	else {
		if (decrementIfIncreased) {
			std::regex pattern("([A-Za-z])#([0-9])");
			std::smatch result;
			if (std::regex_match(name, result, pattern)) {
				name = result.str(1) + result.str(2);
				increased = false;
			}
		}
	}
}

void Note::changeNoteLetter(std::string newNote)
{
	std::regex pattern("([ABCDEFGabcdefg])(#)?([2-6])");
	std::smatch result;
	if (std::regex_match(newNote, result, pattern)) {
		if (result.str(1) != "") {
			bool hasSharp = false;
			if (result.str(2) != "") {
				hasSharp = true;
			}
			if (result.str(3) != "") {
				std::string str = result.str(1);
				toUpper(str);
				name = str + ((hasSharp) ? "#" : "") + result.str(3);
				midiValue = octaveChangeMap[name];
				increased = hasSharp;
			} else {
				throw "Neadekvatna nota";
			}
		}
		else
			throw "Neadekvatna nota";
	}
	else {
		throw "Unhandled Exception";
	}
}


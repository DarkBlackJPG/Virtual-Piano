#include "Composition.h"
#include "Note.h"
#include "Pause.h"
#include "Chord.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <iterator>

/**  (\w+)?(\[[^\]]+\])?( )?
*
*	1. First group finds data like djasdisaj_dsajidsajis
*	2. Group parses [...]
*	3. 
*
*
**/

std::string Composition::filePath;
std::string Composition::fileName;


std::string Composition::getFilePath(std::string setFilePath)
{
	if (setFilePath != "") {
		Composition::filePath = setFilePath;
		std::regex regex("([a-zA-Z0-9-_]{2,30})\\.(txt)+$");
		std::smatch smatch;
		if (std::regex_search(filePath, smatch, regex)) {
			Composition::fileName = smatch.str(1);
		}
		 
	}
	return Composition::filePath;
}

bool Composition::initializeFile()
{
	if (Composition::filePath == "") {
		throw "File not defined!";
	}
	std::ifstream file;
	file.open(filePath);
	if (!file) {
		std::cout << "File not loaded!" << std::endl;
		return false;
	}
	std::cout << "File loaded!" << std::endl;
	std::string fileData;
	if (filePath != "") {
		std::string temporary;
		while (getline(file, temporary)) {
			temporary.erase(std::remove(temporary.begin(), temporary.end(), '\n'));
			fileData += temporary;
		}
		file.close();

		parseData(fileData);
	}
}

void Composition::setTimeSignature(std::pair<int, int> time)
{
	if (time.second != 4 && time.second != 8)
		throw "Incompatible time signature. The divisor can only be 4 or 8";
	myTimeSignature.first = time.first;
	myTimeSignature.second = time.second;
	rightHand->myTimeSignature = this->myTimeSignature;
	leftHand->myTimeSignature = this->myTimeSignature;
}

void Composition::parseData(std::string & data)
{
	std::regex pattern("([\\w]+)?(\\[[^\\]]+\\])?([ ][|][ ])?( )?");
	std::smatch regexMatch;
	std::sregex_iterator dataIterator(data.begin(), data.end(), pattern);
	std::sregex_iterator dataIteratorEnd;
	if (rightHand->getNumberOfMeasures() != 0) {
		rightHand->clear();
	}
	if (leftHand->getNumberOfMeasures() != 0) {
		leftHand->clear();
	}
	while (dataIterator != dataIteratorEnd) {
		regexMatch = *dataIterator;
		// Pojedinacne cetvrtine
		if (regexMatch.str(1) != "") {
			for (unsigned i = 0; i < regexMatch.str(1).length(); i++) {
					Note* newNote = new Note(Note::notesMap[regexMatch.str(1)[i]].first, Note::notesMap[regexMatch.str(1)[i]].second, Duration::QUARTER);
					if (newNote->getOctave() <= 3) {
						leftHand->addNote(newNote);
						rightHand->addNote(new Pause(Duration::QUARTER));
					}
					else {
						rightHand->addNote(newNote);
						leftHand->addNote(new Pause(Duration::QUARTER));
					}
			}
		}
		// Sve u zagradi, dodatna obrada
		if (regexMatch.str(2) != "") {
			std::regex spacePattern("([ ])");
			std::smatch match;
			std::string a = regexMatch.str(2);
			if (std::regex_search(a, match, spacePattern) || a.length() == 3) {
				for (int i = 1; i < a.length(); i += 2) {
					Note* newNote = new Note(Note::notesMap[regexMatch.str(2)[i]].first, Note::notesMap[regexMatch.str(2)[i]].second, Duration::EIGHT);
					if (newNote->getOctave() <= 3) {
						leftHand->addNote(newNote);
						rightHand->addNote(new Pause(Duration::EIGHT));
					}
					else {
						rightHand->addNote(newNote);
						leftHand->addNote(new Pause(Duration::EIGHT));
					}
				}
			}
			else {
				Chord* rightHandChord = new Chord(Duration::QUARTER), *leftHandChord = new Chord(Duration::QUARTER);
				for (int i = 1; i < a.length() - 1; i ++) {
					Note* newNote = new Note(Note::notesMap[regexMatch.str(2)[i]].first, Note::notesMap[regexMatch.str(2)[i]].second, Duration::QUARTER);
					if (newNote->getOctave() <= 3) {
						leftHandChord->addNote(newNote);
					}
					else {
						rightHandChord->addNote(newNote);
					}
				}
				if (!leftHandChord->isEmpty() && !rightHandChord->isEmpty()) {
					leftHand->addNote(leftHandChord);
					rightHand->addNote(rightHandChord);
				}
				else {
					if (rightHandChord->isEmpty()) {
						rightHand->addNote(new Pause(Duration::QUARTER));
					}
					if (leftHandChord->isEmpty()) {
						leftHand->addNote(new Pause(Duration::QUARTER));
					}
					if (!rightHandChord->isEmpty()) {
						rightHand->addNote(rightHandChord);
					} 
					if (!leftHandChord->isEmpty()) {
						leftHand->addNote(leftHandChord);
					}
				}
			}
		}
		// Pauze
		if (regexMatch.str(3) != "") {
			leftHand->addNote(new Pause(Duration::QUARTER));
			rightHand->addNote(new Pause(Duration::QUARTER));
		}
		if (regexMatch.str(4) != "") {
			leftHand->addNote(new Pause(Duration::EIGHT));
			rightHand->addNote(new Pause(Duration::EIGHT));
		}
		dataIterator++;
	}
	while (!Part::lastMeasureIsFull(leftHand))
		leftHand->addNote(new Pause(Duration::EIGHT));
	while (!Part::lastMeasureIsFull(rightHand))
		rightHand->addNote(new Pause(Duration::EIGHT));
	isLoaded = true;
}

Composition::Composition() : currentNumberOfMeasures(0)
{
	leftHand = new Part(Part::LEFTHAND);
	rightHand = new Part(Part::RIGHTHAND);
}


Composition::~Composition()
{
}

std::ostream & operator<<(std::ostream & stream, Composition & composition)
{
	if (composition.leftHand->getNumberOfMeasures() != composition.rightHand->getNumberOfMeasures()) {
		throw "Fatal exception";
	}
	for (int i = 0; i < composition.leftHand->getNumberOfMeasures(); i+=4) {
		for (int j = 0; j < 4; j++) {
			if (i + j < composition.leftHand->getNumberOfMeasures()) {
				stream << *composition.rightHand->getMeasureAt(i + j) << " | ";
			}
		}
		std::cout << std::endl;
		for (int j = 0; j < 4; j++) {
			if (i + j < composition.leftHand->getNumberOfMeasures()) {
				stream << *composition.leftHand->getMeasureAt(i + j) << " | ";
			}
		}
		stream << std::endl << std::endl << std::endl;
	}
	return stream;
}

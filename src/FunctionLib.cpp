#include <fstream>
#include <iostream>
#include <algorithm>
#include <regex>
#include "Note.h"
#include "Chord.h"
#include "Pause.h"
#include "Composition.h"
#include "MIDIFormatter.h"
#include "BMPFormatter.h"
#include "MXMLFormatter.h"
#include <iomanip>
void calculateRGBValues() {
	RGBdat dat1(0xFF, 0x00, 0x00);
	RGBdat dat2(0xFF, 0x7F, 0x00);
	RGBdat dat3(0xFF, 0xFF, 0x00);
	RGBdat dat4(0x7F, 0xFF, 0x00);
	RGBdat dat5(0x00, 0xFF, 0x00);
	RGBdat dat6(0x00, 0xFF, 0x7F);
	RGBdat dat7(0x00, 0xFF, 0xFF);
	RGBdat dat8(0x00, 0x7F, 0xFF);
	RGBdat dat9(0x00, 0x00, 0xFF);
	RGBdat dat10(0x7F, 0x00, 0xFF);
	RGBdat dat11(0xFF, 0x00, 0xFF);
	RGBdat dat12(0xFF, 0x00, 0x7F);
	std::string noteArray[] = {
		"C",
		"C#",
		"D",
		"D#",
		"E",
		"F",
		"F#",
		"G",
		"G#",
		"A",
		"A#",
		"B"
	};
	BMPFormatter::rgbDataMap["C4"] = dat1;
	BMPFormatter::rgbDataMap["C#4"] = dat2;
	BMPFormatter::rgbDataMap["D4"] = dat3;
	BMPFormatter::rgbDataMap["D#4"] = dat4;
	BMPFormatter::rgbDataMap["E4"] = dat5;
	BMPFormatter::rgbDataMap["F4"] = dat6;
	BMPFormatter::rgbDataMap["F#4"] = dat7;
	BMPFormatter::rgbDataMap["G4"] = dat8;
	BMPFormatter::rgbDataMap["G#4"] = dat9;
	BMPFormatter::rgbDataMap["A4"] = dat10;
	BMPFormatter::rgbDataMap["A#4"] = dat11;
	BMPFormatter::rgbDataMap["B4"] = dat12;
	for (int i = 2; i <= 6; i++) {
		if (i != 4) {
			for (int j = 0; j < 12; j++) {
				RGBdat temp(0, 0, 0);
				RGBdat Temp4 = BMPFormatter::rgbDataMap[noteArray[j] + "4"];
				switch (i)
				{
				case 2:
					temp.changeDat(Temp4.R - (Temp4.R / 8) * 6, Temp4.G - (Temp4.G / 8) * 6, Temp4.B - (Temp4.B / 8) * 6);
					BMPFormatter::rgbDataMap[noteArray[j] + std::to_string(i)] = temp;
					continue;
				case 3:
					temp.changeDat(Temp4.R - (Temp4.R / 8) * 3, Temp4.G - (Temp4.G / 8) * 3, Temp4.B - (Temp4.B / 8) * 3);
					BMPFormatter::rgbDataMap[noteArray[j] + std::to_string(i)] = temp;
					continue;
				case 5:
					temp.changeDat(Temp4.R + ((255 - Temp4.R) / 8) * 3, Temp4.G + ((255 - Temp4.G) / 8 )* 3, Temp4.B + ((255 - Temp4.B) / 8) * 3);
					BMPFormatter::rgbDataMap[noteArray[j] + std::to_string(i)] = temp;
					continue;
				case 6:
					temp.changeDat(Temp4.R + ((255 - Temp4.R) / 8) * 6, Temp4.G + ((255 - Temp4.G) / 8) * 6, Temp4.B + ((255 - Temp4.B) / 8) * 6);
					BMPFormatter::rgbDataMap[noteArray[j] + std::to_string(i)] = temp;
					continue;
				default:
					break;
				}
				
			}
		}
	}
	/*std::cout << std::setw(6) << "R" << std::setw(6) << "G" << std::setw(6) << "B" << std::endl;
	for (auto a : BMPFormatter::rgbDataMap) {
		std::cout << std::setw(6) << (int)a.second.R << std::setw(6) << (int)a.second.G << std::setw(6) <<(int) a.second.B << std::setw(6) << a.first << std::endl;
	}*/
}

void getNotes() {
	std::ifstream notes;
	notes.open("map.csv");
	if (!notes)
		exit(2);
	std::regex reg("([\\x00-\\x7f]),([A-Z][0-9]|[A-z][#][0-9]),([0-9]\\w)");
	std::string line;
	while (std::getline(notes, line))
	{
		std::smatch result;
		if (std::regex_search(line, result, reg)) {
			std::pair<std::string, int> pain;
			pain.first = result.str(2);
			pain.second = stoi(result.str(3));
			Note::octaveChangeMap[result.str(2)] = stoi(result.str(3));
			Note::notesMap[result.str(1)[0]] = pain;
			Note::midiMap[pain.second] = pain.first;
		}
	}
	calculateRGBValues();
}


void printMenu() {
	std::cout << "1. Ucitaj podatke" << std::endl << "2. Manipulisi kompozicijom" << std::endl <<  "3. Eksportuj kompoziciju" << std::endl <<  "4. Zavrsi"<< std::endl;
}
void printLoadDataMenu() {
	std::cout << "1. Upisi ime datoteke\n2. Ucitaj kompoziciju\n3. Izadji\n" << std::endl;
}
void printManipulationMenu() {
	std::cout << "1. Ispisi kompoziciju\n2. Iteriraj kroz kompoziciju po taktovima\n3. Izmeni vremenski potpis\n4. Povisi kompoziciju za zadat broj oktava\n5. Izdji" << std::endl;
}
void printMeasureIteratorMenu() {
	std::cout << "1. Sledeci takt\n2. Prethodni takt\n3. Iteriraj unutar takta\n4. Izadji"<<std::endl;
}
void printMeasureManipulationMenu() {
	std::cout << "1. Sledeca nota\n2. Prethodna nota\n3. Promeni oktavu note\n4. Promeni visinu note\n5. Dodaj povisilicu\n6. Skini povisilicu\n7. Izadji" << std::endl;
}
void printExportMenu() {
	std::cout << "1. BMP eksportovanje\n2. MusicXML eksportovanje\n3. MIDI eksportovanje\n4. Izadji" << std::endl;

}
void modifyMeasure(Composition* cc, int measure) {
	Measure* leftPartMeasure = cc->getLeftHand()->getMeasureAt(measure),
		*rightPartMeasure = cc->getRightHand()->getMeasureAt(measure);
	MusicSymbol* leftPartNote = nullptr;
	MusicSymbol* righrPartNote = nullptr;
	int currentNote = -1, choice = 0;
	while (choice != 7) {
		printMeasureManipulationMenu();
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			if (currentNote < leftPartMeasure->numberOfNotes() - 1) {
				currentNote++;
				leftPartNote = leftPartMeasure->getSymbolAt(currentNote);
				righrPartNote = rightPartMeasure->getSymbolAt(currentNote);
				std::cout << *righrPartNote << std::endl;
				std::cout << *leftPartNote;
			}
			else {
				std::cout << "Ne postoji vise nota";
			}
			break;
		case 2:
			if (currentNote > 0) {
				currentNote--;
				leftPartNote = leftPartMeasure->getSymbolAt(currentNote);
				righrPartNote = rightPartMeasure->getSymbolAt(currentNote);
				std::cout << *righrPartNote << std::endl;
				std::cout << *leftPartNote;
			}
			else {
				std::cout << "Ne postoji vise nota";
			}
			break;
		case 3:
			if (leftPartNote != nullptr && righrPartNote != nullptr) {
				if (leftPartNote->isThisChord()) {
					Chord* chord = dynamic_cast<Chord*>(leftPartNote);
					if (!chord)
						throw "Fatal Exception";
					for (auto n : chord->getNotesList()) {
						n->increaseOctave();
					}
				}
				else if (dynamic_cast<Note*>(leftPartNote) != nullptr) {
					Note* note = dynamic_cast<Note*>(leftPartNote);
					if (!note)
						throw "Fatal Exception";
					note->increaseOctave();
				}
				if (righrPartNote->isThisChord()) {
					Chord* chord = dynamic_cast<Chord*>(righrPartNote);
					if (!chord)
						throw "Fatal Exception";
					for (auto n : chord->getNotesList()) {
						n->increaseOctave();
					}
				}
				else if (dynamic_cast<Note*>(righrPartNote)) {
					Note* note = dynamic_cast<Note*>(righrPartNote);
					if (!note)
						throw "Fatal Exception";
					note->increaseOctave();
				}
			}
			else {
				std::cout << "Note nisu inicijalizovane, inicijalizuj aktivacijom opcije 1";
			}
			std::cout << *righrPartNote << std::endl;
			std::cout << *leftPartNote;
			break;
		case 4:
			//promeni visinu note A->B
			if (leftPartNote != nullptr && righrPartNote != nullptr) {
				std::string newNote = "";
				while (true) {
					std::cout << std::endl << "Unesi naziv note" << std::endl;
					std::cin >> newNote;
					try {
						if (leftPartNote->isThisChord()) {
							Chord* chord = dynamic_cast<Chord*>(leftPartNote);
							if (!chord)
								throw "Fatal Exception";
							for (auto n : chord->getNotesList()) {
								n->changeNoteLetter(newNote);
							}
						}
						else if (dynamic_cast<Note*>(leftPartNote) != nullptr) {
							Note* note = dynamic_cast<Note*>(leftPartNote);
							if (!note)
								throw "Fatal Exception";
							note->changeNoteLetter(newNote);
						}
						if (righrPartNote->isThisChord()) {
							Chord* chord = dynamic_cast<Chord*>(righrPartNote);
							if (!chord)
								throw "Fatal Exception";
							for (auto n : chord->getNotesList()) {
								n->changeNoteLetter(newNote);
							}
						}
						else if (dynamic_cast<Note*>(righrPartNote)) {
							Note* note = dynamic_cast<Note*>(righrPartNote);
							if (!note)
								throw "Fatal Exception";
							note->changeNoteLetter(newNote);
						}

						break;
					}
					catch (std::string ex) {
						std::cout << ex << std::endl;
					}
				}
			}
			else {
				std::cout << "Note nisu inicijalizovane, inicijalizuj aktivacijom opcije 1";
			}
			std::cout << *righrPartNote << std::endl;
			std::cout << *leftPartNote;
			break;
		case 5:
			if (leftPartNote != nullptr && righrPartNote != nullptr) {
				if (leftPartNote->isThisChord()) {
					Chord* chord = dynamic_cast<Chord*>(leftPartNote);
					if (!chord)
						throw "Fatal Exception";
					for (auto n : chord->getNotesList()) {
						n->increasedNote();
					}
				}
				else if (dynamic_cast<Note*>(leftPartNote) != nullptr) {
					Note* note = dynamic_cast<Note*>(leftPartNote);
					if (!note)
						throw "Fatal Exception";
					note->increasedNote();
				}
				if (righrPartNote->isThisChord()) {
					Chord* chord = dynamic_cast<Chord*>(righrPartNote);
					if (!chord)
						throw "Fatal Exception";
					for (auto n : chord->getNotesList()) {
						n->increasedNote();
					}
				}
				else if (dynamic_cast<Note*>(righrPartNote)) {
					Note* note = dynamic_cast<Note*>(righrPartNote);
					if (!note)
						throw "Fatal Exception";
					note->increasedNote();
				}
			}
			else {
				std::cout << "Note nisu inicijalizovane, inicijalizuj aktivacijom opcije 1";
			}
			std::cout << *righrPartNote << std::endl;
			std::cout << *leftPartNote;
			break;
		case 6:
			if (leftPartNote != nullptr && righrPartNote != nullptr) {
				if (leftPartNote->isThisChord()) {
					Chord* chord = dynamic_cast<Chord*>(leftPartNote);
					if (!chord)
						throw "Fatal Exception";
					for (auto n : chord->getNotesList()) {
						n->increasedNote(true);
					}
				}
				else if (dynamic_cast<Note*>(leftPartNote) != nullptr) {
					Note* note = dynamic_cast<Note*>(leftPartNote);
					if (!note)
						throw "Fatal Exception";
					note->increasedNote(true);
				}
				if (righrPartNote->isThisChord()) {
					Chord* chord = dynamic_cast<Chord*>(righrPartNote);
					if (!chord)
						throw "Fatal Exception";
					for (auto n : chord->getNotesList()) {
						n->increasedNote(true);
					}
				}
				else if (dynamic_cast<Note*>(righrPartNote)) {
					Note* note = dynamic_cast<Note*>(righrPartNote);
					if (!note)
						throw "Fatal Exception";
					note->increasedNote(true);
				}
			}
			else {
				std::cout << "Note nisu inicijalizovane, inicijalizuj aktivacijom opcije 1";
			}
			std::cout << *righrPartNote << std::endl;
			std::cout << *leftPartNote;
			break;
		case 7:
			break;
		default:
			std::cout << "Ne postoji opcija";
			break;
		}
		std::cout << std::endl;
	}
	
}
void changeTimeSignature(Composition* cc) {
	std::pair<int, int> timeSignature;
	std::vector<MusicSymbol*> rightHandSymbols;
	std::vector<MusicSymbol*> leftHandSymbols;
	leftHandSymbols = cc->getLeftHand()->extractAllNotes();
	rightHandSymbols = cc->getRightHand()->extractAllNotes();
	do {
		std::cout << "Unesi vremenski potpis (a b)" << std::endl;
		std::cin >> timeSignature.first;
		std::cin >> timeSignature.second;
		try {
			cc->setTimeSignature(timeSignature);
			break;
		}
		catch (const char* e) {
			std::cout << e << std::endl;
		}
	} while (true);
	std::cout << "Uspesno zamenjen potpis" << std::endl;
	cc->getLeftHand()->importAllNotes(leftHandSymbols);
	cc->getRightHand()->importAllNotes(rightHandSymbols);
}
void shiftOctave(Composition* cc) {
	std::vector<MusicSymbol*> rightHandSymbols;
	std::vector<MusicSymbol*> leftHandSymbols;
	leftHandSymbols = cc->getLeftHand()->extractAllNotes();
	rightHandSymbols = cc->getRightHand()->extractAllNotes();
	std::cout << "Unesi broj pomeraja [moze i negativno]: ";
	int shift = 0;
	std::cin >> shift;
	std::cout << std::endl;
	for (auto a : leftHandSymbols)
		a->shiftOctave(shift);
	for (auto a : rightHandSymbols)
		a->shiftOctave(shift);

	std::cout << "Uspesno odradjen pomeraj" << std::endl;
}
void manipulator(Composition* cc) {
	int choice = 0;
	int currentMeasure = -1;
	do {
		printMeasureIteratorMenu();
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			if (currentMeasure < cc->getLeftHand()->getNumberOfMeasures() - 1) {
				currentMeasure++;
				std::cout << *cc->getRightHand()->getMeasureAt(currentMeasure) << std::endl;
				std::cout << *cc->getLeftHand()->getMeasureAt(currentMeasure);
				
			}
			else {
				std::cout << "Nema vise taktova";
			}
			break;
		case 2:
			if (currentMeasure > 0) {
				currentMeasure--;
				std::cout << *cc->getRightHand()->getMeasureAt(currentMeasure) << std::endl;
				std::cout << *cc->getLeftHand()->getMeasureAt(currentMeasure);

			}
			else {
				std::cout << "Nema vise taktova";
			}
			break;
		case 3:
			if (currentMeasure >= 0 && currentMeasure < cc->getLeftHand()->getNumberOfMeasures()) {
				modifyMeasure(cc, currentMeasure);
			}
			else {
				std::cout << "Nije zapoceta iteracija. Zapocnite iteraciju pritiskom na opciju 1." << std::endl;
			}
			break;
		case 4:
			break;
		default:
			std::cout << "Nepostojeca opcija";
			break;
		}
		std::cout << std::endl;
	} while (choice != 4);
}

void compositionManipulationFunction(Composition* cc) {
	int option = 0;
	while (option != 5) {
		printManipulationMenu();
		std::cin >> option;
		switch (option)
		{
		case 1:
			std::cout << *cc;
			break;
		case 2:
			manipulator(cc);
			break;
		case 3:
			changeTimeSignature(cc);
			break;
		case 4:
			shiftOctave(cc);
			break;
		case 5:
			break;
		default:
			std::cout << "Nepostojeca opcija";
			break;
		}
	}
}

void importDataFunction(Composition* cc) {
	printLoadDataMenu();
	int choice;
	std::pair<int, int> timeSignature;
	std::string file;
	std::regex regex("([a-zA-Z0-9-_]{2,30})\\.(txt)+$");
	std::smatch smatch;
	std::cin >> choice;
	do {

		switch (choice)
		{
		case 1:
			std::cout << "Unesi ime: ";
			std::cin >> file;
			while (true)
			{
				if (!std::regex_search(file, smatch, regex))
				{
					std::cout << "Nije dobar naziv fajla!\n";
					std::cout << "Unesi ime: ";
					std::cin >> file;
					continue;
				}
				break;
			}
			Composition::getFilePath(file);
			break;
		case 2:
			if (Composition::getFilePath() != "") {
				do {
					std::cout << "Unesi vremenski potpis (a b)" << std::endl;
					std::cin >> timeSignature.first;
					std::cin >> timeSignature.second;
					try {
						cc->setTimeSignature(timeSignature);
						break;
					}
					catch (const char* e) {
						std::cout << e << std::endl;
					}
				} while (true);
				cc->initializeFile();
			}
			else {
				std::cout << "Nije unet naziv datoteke";
			}
		default:
			break;
		}

		printLoadDataMenu();
		std::cin >> choice;
	} while (choice != 3);
}
void toUpper(std::string& string) {
	std::transform(string.begin(), string.end(), string.begin(), ::toupper);
}
void toLower(std::string& string) {
	std::transform(string.begin(), string.end(), string.begin(), ::tolower);
}


void exportFunction(Composition* composition) {
	int choice = 0;
	do {
		printExportMenu();
		std::cin >> choice;
		MIDIFormatter midiFormat(composition);
		BMPFormatter bmpFormat(composition);
		MXMLFormatter musixml(composition);
		switch (choice)
		{
		case 1:
			bmpFormat.format();
			break;

		case 2:
			musixml.format();
			break;

		case 3:
			midiFormat.format();
			break;
		case 4:
			break;
		default:
			std::cout << "Ne postoji funkcija sa ovim rednim brojem";
			break;
		}
	} while (choice != 4);
}
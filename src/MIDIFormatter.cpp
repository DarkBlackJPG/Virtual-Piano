#include "MIDIFormatter.h"
#include "MidiFile.h"
#include "Chord.h"
#include "Note.h"
#include "Pause.h"
#include <regex>
void MIDIFormatter::format()
{
	smf::MidiFile outputfile;
	outputfile.absoluteTicks();
	std::vector<unsigned char> midiEvent;
	midiEvent.resize(3);
	int tpq = 48;
	outputfile.setTicksPerQuarterNote(tpq);
	outputfile.addTrack(1);

	std::vector<MusicSymbol*> rightHandNotes = myComposition->getRightHand()->extractAllNotes();
	std::vector<MusicSymbol*> leftHandNotes = myComposition->getLeftHand()->extractAllNotes();
	midiEvent[2] = 64;
	int actionTime = 0;
	bool prevIsSplit = false;
	for (auto a : leftHandNotes){
		if (dynamic_cast<Chord*>(a) != nullptr) {
			if (!prevIsSplit) {
				Chord* temp = dynamic_cast<Chord*>(a);
				int time = (temp->noteDuration().getDuration() == Duration::QUARTER) ? 2 : 1;
				if (a->isSplit()) {
					time = 2;
					prevIsSplit = true;
				}
				for (auto var : temp->getNotesList()) {
					midiEvent[0] = 0x90;
					midiEvent[1] = var->getMidiData();
					outputfile.addEvent(0, actionTime, midiEvent);
					actionTime += tpq / 2 * time;
					midiEvent[0] = 0x80;
					outputfile.addEvent(0, actionTime, midiEvent);
					actionTime -= tpq / 2 * time;
				}
				actionTime += tpq / 2 * time;
			}
			else {
				prevIsSplit = false;
			}
		}
		else if (dynamic_cast<Note*>(a) != nullptr) {
			if (prevIsSplit == false) {
				int time = (a->noteDuration().getDuration() == Duration::QUARTER) ? 2 : 1;
				if (a->isSplit()) {
					time = 2;
					prevIsSplit = true;
				}
				midiEvent[0] = 0x90;
				midiEvent[1] = a->getMidiData();
				outputfile.addEvent(0, actionTime, midiEvent);
				actionTime += tpq / 2 * time;
				midiEvent[0] = 0x80;
				outputfile.addEvent(0, actionTime, midiEvent);
			}
			else {
				prevIsSplit = false;
			}
		}
		else if (dynamic_cast<Pause*>(a) != nullptr) {
			if (prevIsSplit == false) {
				int time = (a->noteDuration().getDuration() == Duration::QUARTER) ? 2 : 1;
				if (a->isSplit()) {
					time = 2;
					prevIsSplit = true;
				}
				actionTime += tpq / 2 * time;
			}
			else {
				prevIsSplit = false;
			}
		}
	}
	actionTime = 0;
	for (auto a : rightHandNotes) {
		if (dynamic_cast<Chord*>(a) != nullptr) {
			if (!prevIsSplit) {
				Chord* temp = dynamic_cast<Chord*>(a);
				int time = (temp->noteDuration().getDuration() == Duration::QUARTER) ? 2 : 1;
				if (a->isSplit()) {
					time = 2;
					prevIsSplit = true;
				}
				for (auto var : temp->getNotesList()) {
					midiEvent[0] = 0x90;
					midiEvent[1] = var->getMidiData();
					outputfile.addEvent(1, actionTime, midiEvent);
					actionTime += tpq / 2 * time;
					midiEvent[0] = 0x80;
					outputfile.addEvent(1, actionTime, midiEvent);
					actionTime -= tpq / 2 * time;
				}
				actionTime += tpq / 2 * time;
			}
			else {
				prevIsSplit = false;
			}
		}
		else if (dynamic_cast<Note*>(a) != nullptr) {
			if (prevIsSplit == false) {
				int time = (a->noteDuration().getDuration() == Duration::QUARTER) ? 2 : 1;
				if (a->isSplit()) {
					time = 2;
					prevIsSplit = true;
				}
				midiEvent[0] = 0x90; 
				midiEvent[1] = a->getMidiData();
				outputfile.addEvent(1, actionTime, midiEvent);
				actionTime += tpq / 2 * time;
				midiEvent[0] = 0x80;
				outputfile.addEvent(1, actionTime, midiEvent);
			}
			else {
				prevIsSplit = false;
			}
		}
		else if (dynamic_cast<Pause*>(a) != nullptr) {
			if (prevIsSplit == false) {
				int time = (a->noteDuration().getDuration() == Duration::QUARTER) ? 2 : 1;
				if (a->isSplit()) {
					time = 2;
					prevIsSplit = true;
				}
				actionTime += tpq / 2 * time;
			}
			else {
				prevIsSplit = false;
			}
		}
	}
	outputfile.sortTracks();
	std::regex pattern("([a-zA-Z0-9-_]{2,30})\\.(txt)+$");
	std::smatch result;
	std::string naz = myComposition->getFilePath();
	std::string temp = "default";
	if (std::regex_match(naz, result, pattern)) {
		temp = result.str(1);
	}
	outputfile.write(temp+".mid");
	std::cout << "Uspesno odradjeno sa nazivom " + temp + ".mid\n";
}

MIDIFormatter::~MIDIFormatter()
{
}

#include "Chord.h"
#include <vector>


Note * Chord::getNoteAt(int i)
{
	if ((unsigned)i >= notes.size())
		return nullptr;
	std::list<Note*>::iterator iterator = notes.begin();
	std::advance(iterator, i);
	return *iterator;
}

void Chord::shiftOctave(int octaveNumberShift)
{
	for (auto var : notes)
		var->shiftOctave(octaveNumberShift);
}

int Chord::getMidiData()
{
	return -1;
}

std::ostream& Chord::write(std::ostream& stream)
{
	stream << "[";
	for (auto a : notes) {
		stream << " " << *a << " ";
	}
	return stream << "]";
}

std::pair<MusicSymbol*, MusicSymbol*> Chord::splitSymbol()
{
	Chord* leftPart = new Chord(Duration::EDuration::EIGHT), *rightPart = new Chord(Duration::EDuration::EIGHT);
	for (auto var : notes) {
		leftPart->addNote(new Note(var->getName(), var->getMidiData(), Duration::EDuration::EIGHT));
		rightPart->addNote(new Note(var->getName(), var->getMidiData(), Duration::EDuration::EIGHT));
	}
	leftPart->split = true;
	rightPart->split = true;
	return std::pair<MusicSymbol*, MusicSymbol*>(leftPart, rightPart);
}

Chord::Chord(Duration::EDuration duration) : MusicSymbol(duration)
{
}

std::string Chord::generateMUSICXMLData(bool noteIsSplit, bool noteIsSecond)
{
	std::string data = "";
	for (unsigned int i = 0;
		i < notes.size();
		i++) {
		
		data +=
			"<note>" + std::string(i != 0 ? "\n<chord/>" : "") + "\n"
			"<pitch>\n"
			"<step>" + getNoteAt(i)->getStep() + "</step>\n"
			"<octave>" + std::to_string(getNoteAt(i)->getOctave()) + "</octave>\n"
			+ ((getNoteAt(i)->isIncreased() == true) ? "<alter>1</alter>\n" : "") +
			"</pitch>\n"
			"<duration>" + 
			((getNoteAt(i)->noteDuration().getDuration() == Duration::QUARTER) ? "2" : "1") +
			"</duration>\n" + std::string(noteIsSplit == true ? ((noteIsSecond == false) ? "<tie type=\"start\"/>\n" : "<tie type=\"end\"/>\n") : "") +
			"</note>\n";

	}
	return data;
}


Chord::~Chord()
{
}

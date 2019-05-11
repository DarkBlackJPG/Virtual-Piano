#include "Pause.h"



int Pause::getMidiData()
{
	return -1;
}

std::pair<MusicSymbol*, MusicSymbol*> Pause::splitSymbol()
{
	Pause* leftPart, *rightPart;
	leftPart = new Pause(Duration::EIGHT);
	rightPart = new Pause(Duration::EIGHT);
	leftPart->split = true;
	rightPart->split = true;
	return std::pair<MusicSymbol*, MusicSymbol*>(leftPart, rightPart);
}

std::string Pause::generateMUSICXMLData(bool noteIsSplit, bool noteIsSecond)
{
	std::string data =
		"<note>\n"
		"<rest/>\n"
		"<duration>"
		+ std::string((noteDuration().getDuration() == Duration::QUARTER) ? "2" : "1") +
		"</duration>\n"
		+ std::string(noteIsSplit == true ? ((noteIsSecond == false) ? "<tie type=\"start\"/>\n" : "<tie type=\"end\"/>\n") : "") +
		"</note>\n";

	return data;
}

Pause::Pause(Duration::EDuration duration) : MusicSymbol(duration)
{
}


Pause::~Pause()
{
}

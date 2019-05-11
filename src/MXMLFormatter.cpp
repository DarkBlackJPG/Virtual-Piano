#include "MXMLFormatter.h"
#include <list>
#include <fstream>






void MXMLFormatter::format() {
	std::string header =
		"<?xml version = \"1.0\" encoding = \"UTF-8\" standalone = \"no\"?>\n"
		"<!DOCTYPE score-partwise PUBLIC\n"
		"\"-//Recordare//DTD MusicXML 3.1 Partwise//EN\"\n"
		"\"http://www.musicxml.org/dtds/partwise.dtd\">\n"
		"<score-partwise version = \"3.1\">\n<part-list>\n"
		"<score-part id = \"Right\">\n"
		"</score-part>\n"
		"<score-part id=\"Left\">\n"
		"</score-part>\n"
		"</part-list>\n";
	std::string footer = "</score-partwise>\n";
	std::string rightPartXMLStart =
		"<part id=\"Right\">\n"
		"<measure>\n"
		"<attributes>\n"
		"<divisions>2</divisions>\n<time>\n"
		"<beats>" + std::to_string(myComposition->getMyTimeSignature().first) + "</beats>\n"
		"<beat-type>" + std::to_string(myComposition->getMyTimeSignature().second) + "</beat-type>\n"
		"</time>\n"
		"<clef>\n"
		"<sign>G</sign>\n"
		"<line>2</line>\n"
		"</clef>\n"
		"</attributes>\n";
	std::string rightPartElementString = "";
	std::string rightPartXMLEnd = 
		"</part>\n";

	std::list<Measure*> rightHandComp = myComposition->getRightHand()->getMeasures();
	std::list<Measure*> leftHandComp = myComposition->getLeftHand()->getMeasures();
	int noteCounter = 0;
	bool wasSplit = false;
	for (auto a : rightHandComp) {
		std::list<MusicSymbol*> myNotes = a->getNotes();
		rightPartElementString += (noteCounter++ != 0) ? "<measure>\n": "";
		for (auto n : myNotes) {
			rightPartElementString += n->generateMUSICXMLData(n->isSplit(), wasSplit);
			if (wasSplit)
				wasSplit = false;
			if (n->isSplit())
				wasSplit = true;
		}
		rightPartElementString += "</measure>\n";
	}
	noteCounter = 0;
	std::string leftPartXMLStart = 
		"<part id=\"Left\">\n"
		"<measure>\n"
		"<attributes>\n"
		"<divisions>2</divisions>\n<time>\n"
		"<beats>" + std::to_string(myComposition->getMyTimeSignature().first) + "</beats>\n"
		"<beat-type>" + std::to_string(myComposition->getMyTimeSignature().second) + "</beat-type>\n"
		"</time>\n"
		"<clef>\n"
		"<sign>F</sign>\n"
		"<line>4</line>\n"
		"</clef>\n"
		"</attributes>\n";
	std::string leftPartElementString = "";
	std::string leftPartXMLEnd = 
		"</part>\n";

	noteCounter = 0;
	wasSplit = false;
	for (auto a : leftHandComp) {
		std::list<MusicSymbol*> myNotes = a->getNotes();
		
		leftPartElementString += (noteCounter++ != 0) ? "<measure>\n" : "";
		for (auto n : myNotes) {
			leftPartElementString += n->generateMUSICXMLData(n->isSplit(), wasSplit);
			if (wasSplit)
				wasSplit = false;
			if (n->isSplit())
				wasSplit = true;
		
		}
		leftPartElementString += "</measure>\n";
	}

	std::ofstream myfile;
	myfile.open(myComposition->getFileName()+".musicxml");
	myfile <<
		header +

		rightPartXMLStart +
		rightPartElementString +
		rightPartXMLEnd +

		leftPartXMLStart +
		leftPartElementString + 
		leftPartXMLEnd + 

		footer;

	myfile.close();
}

MXMLFormatter::~MXMLFormatter()
{
}

#include "BMPFormatter.h"
#include "bitmap_image.hpp"
#include "Chord.h"
#include "Note.h"
#include "Pause.h"
#include <algorithm>
std::map<std::string, RGBdat> BMPFormatter::rgbDataMap;
void BMPFormatter::format()
{
	std::cout << "Unesi sirinu u pikselima" << std::endl;
	int width = 0;
	std::cin >> width;
	std::vector<MusicSymbol*> leftHandNotes = myComposition->getLeftHand()->extractAllNotes();
	std::vector<MusicSymbol*> rightHandNotes = myComposition->getRightHand()->extractAllNotes();
	int numberOfPixels = 0;
	std::for_each(leftHandNotes.begin(), leftHandNotes.end(), [&numberOfPixels](MusicSymbol* temp) {
		numberOfPixels += (temp->noteDuration().getDuration() == Duration::QUARTER) ? 2 : 1;
	});
	int height = (int)std::ceil((double)numberOfPixels / width);
	bitmap_image image(width, height);
	int counter = 0;
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			if ((unsigned)counter < leftHandNotes.size()) {
				RGBdat rgbDat(0,0,0);
				Duration::EDuration dur = Duration::EIGHT;

				bool isChord = false;
				int numOfNotes = 0;
				int rINT = 0, gINT = 0, bINT = 0;
				// 1 1 we_wich_you_a_merry_christmas.txt 2 4 4 3 3 1 20
				if (dynamic_cast<Chord*>(leftHandNotes[counter]) != nullptr) {
					dur = leftHandNotes[counter]->noteDuration().getDuration();
					Chord* temp = dynamic_cast<Chord*>(leftHandNotes[counter]);
					std::list<Note*> notes = temp->getNotesList();
					for(auto var : notes) {
						RGBdat dd = BMPFormatter::rgbDataMap[var->getName()];
						rINT += (int)dd.R;
						gINT += (int)dd.G;
						bINT += (int)dd.B;
						numOfNotes++;
					};
					isChord = true;
				}
				else if (dynamic_cast<Note*>(leftHandNotes[counter]) != nullptr) {
					dur = leftHandNotes[counter]->noteDuration().getDuration();
					rgbDat = BMPFormatter::rgbDataMap[leftHandNotes[counter]->getName()];
				}
				if (dynamic_cast<Chord*>(rightHandNotes[counter]) != nullptr) {
					dur = rightHandNotes[counter]->noteDuration().getDuration();
					Chord* temp = dynamic_cast<Chord*>(rightHandNotes[counter]);
					std::list<Note*> notes = temp->getNotesList();
					for (auto var : notes) {
						RGBdat dd = BMPFormatter::rgbDataMap[var->getName()];
						rINT += (int)dd.R;
						gINT += (int)dd.G;
						bINT += (int)dd.B;
						numOfNotes++;
					};
					isChord = true;
				}
				else if (dynamic_cast<Note*>(rightHandNotes[counter]) != nullptr) {
					dur = rightHandNotes[counter]->noteDuration().getDuration();
					rgbDat = BMPFormatter::rgbDataMap[rightHandNotes[counter]->getName()];
				}
				if (isChord) {
					rINT /= numOfNotes;
					bINT /= numOfNotes;
					gINT /= numOfNotes;
					rgbDat.changeDat((unsigned char)rINT, (unsigned char)gINT, (unsigned char)bINT);
				}
				if (dur == Duration::QUARTER) {
					image.set_pixel(y, x, rgbDat.R, rgbDat.G, rgbDat.B);
					if (y >= width) {
						x++;
						y = 0;
					}
					else { y++; }
					image.set_pixel(y, x, rgbDat.R, rgbDat.G, rgbDat.B);
				}
				else {
					image.set_pixel(y, x, rgbDat.R, rgbDat.G, rgbDat.B);
				}
				counter++;
			}
		}
	}
	image.save_image(myComposition->getFileName()+".bmp");
	std::cout << std::endl << "====Fajl eksportovan====" << std::endl;
}

BMPFormatter::~BMPFormatter()
{
}

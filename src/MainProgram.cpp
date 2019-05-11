#include "BMPFormatter.h"
#include "Composition.h"
#include "Note.h"
#include "Pause.h"
#include "MIDIFormatter.h"
#include "MXMLFormatter.h"


void getNotes();
void printMenu();
void importDataFunction(Composition* cc);
void compositionManipulationFunction(Composition*);
void exportFunction(Composition* composition);


void main(int argc, char *argv[]) {
	getNotes();
	Composition* myComposition = new Composition();
	std::cout << "Uspesno ucitane note" << std::endl << std::endl;
	int choice;
	do {
		printMenu();
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			importDataFunction(myComposition);
			break;
		case 2:
			if (myComposition->fileIsReadyForUse()) {
				compositionManipulationFunction(myComposition);
			} else {
				std::cout << "Nije ucitan fajl" << std::endl;
			}
			break;
		case 3:
			if (myComposition->fileIsReadyForUse()) {
				exportFunction(myComposition);
			}
			else {
				std::cout << "Nije ucitan fajl" << std::endl;
			}
			break;
		default:
			choice = 0; 
			break;
		}
	} while (choice);

	system("pause");
}

#pragma once
#include "Part.h"
#include <string>

class Composition
{
	static std::string filePath;
	static std::string fileName;
	Part *leftHand;
	Part *rightHand;
	int currentNumberOfMeasures;
	bool isLoaded = false;
	std::pair<int, int> myTimeSignature;
public:
	bool fileIsReadyForUse() {
		return isLoaded;
	}
	std::pair<int, int> getMyTimeSignature() {
		return myTimeSignature;
	};
	static std::string getFilePath(std::string setFilePath = "");
	static std::string getFileName() {
		return fileName;
	};
	bool initializeFile();
	void setTimeSignature(std::pair<int, int>);
	void parseData(std::string& data);
	Part * getLeftHand() {
		return leftHand;
	}
	Part * getRightHand() {
		return rightHand;
	}
	friend std::ostream& operator<< (std::ostream& stream, Composition& composition);
	Composition();
	~Composition();
};


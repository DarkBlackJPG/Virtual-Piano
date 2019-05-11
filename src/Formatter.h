#pragma once
#include "Composition.h"
struct RGBdat {
	unsigned char R;
	unsigned char G;
	unsigned char B;
	RGBdat() {};
	RGBdat(char R, char G, char B) {
		this->R = R;
		this->G = G;
		this->B = B;
	}
	void changeDat(char R, char G, char B) {
		this->R = R;
		this->G = G;
		this->B = B;
	}
};
class Formatter
{
protected:
	Composition* myComposition;
public:
	virtual void format() = 0;
	Formatter(Composition* composition) : myComposition(composition) {};
	virtual ~Formatter();
};


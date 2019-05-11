#pragma once
#include "Formatter.h"
class MIDIFormatter :
	public Formatter
{
public:
	void format() override;
	MIDIFormatter(Composition* cmp) : Formatter(cmp) {};
	~MIDIFormatter();
};


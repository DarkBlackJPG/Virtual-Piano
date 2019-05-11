#pragma once
#include "Formatter.h"
#include "Chord.h"
#include "Note.h"
#include "Pause.h"
class MXMLFormatter :
	public Formatter
{
public:
	void format() override;
	MXMLFormatter(Composition* cmp) : Formatter(cmp) {};
	~MXMLFormatter();
};


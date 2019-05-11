#include "MusicSymbol.h"



MusicSymbol::MusicSymbol(Duration duration)
{
	this->duration = new Duration(duration);
}

MusicSymbol::MusicSymbol(Duration::EDuration duration)
{
	this->duration = new Duration(duration);
}


MusicSymbol::~MusicSymbol()
{
}

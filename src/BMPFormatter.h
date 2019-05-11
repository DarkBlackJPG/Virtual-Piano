#pragma once
#include "Formatter.h"
#include <map>
class BMPFormatter :
	public Formatter
{
public:

	void format() override;
	static std::map<std::string, RGBdat> rgbDataMap;
	BMPFormatter(Composition* cmp) : Formatter(cmp) {};
	~BMPFormatter();
};


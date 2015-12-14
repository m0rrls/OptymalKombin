#pragma once
#include "Generator.h"
class Readytime :
	public Generator
{
public:
	using Generator::Generator;
	void rdm(int start, int end);
	~Readytime();
};


#pragma once
#include "Generator.h"

class Timeline :
	public Generator
{
public:
	using Generator::Generator;
	void maintenance(int N, float kN, int maxL);
	~Timeline();
};


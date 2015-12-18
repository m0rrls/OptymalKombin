#pragma once
#include "Generator.h"
#include <map>

class Timeline :
	public Generator
{
public:
	using Generator::Generator;
	//metoda maintenance generuje readytime'y tak by prawdopodob ich istnienia malalo wraz z odlegloscia od poczatku timeline'u
	void maintenance(int i, int maxL); //generowanie i przerw o maksymalnej dl maxL
	void randomMaint(int i, int maxL); // generator nieuwzgledniajacy odleglosci
	//obliczanie parametrow wygen. maint
	void CntMt();
	//³adowanie wygenerowanych wczesniej przerw
	void SetMt(int when, int howL);
	std::map<int, int> getMp();
	~Timeline();
private:
	std::map<int, int> mp;
};


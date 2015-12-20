#pragma once
#include "Generator.h"
#include "PrintableResult.h"
#include "stdafx.h"

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
	//tworzenie rozwiazania losowego ze zbioru zadan
	std::pair<Timeline,Timeline> Instancja(std::vector<Task> zadania, int N);
	//tworzenie ciagu do pliku wynikowego
	PrintableResult resOut(std::vector<Task> zadania, int machine);
	~Timeline();
private:
	std::map<int, int> mp;
};


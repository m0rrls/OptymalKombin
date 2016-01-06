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
	//�adowanie wygenerowanych wczesniej przerw
	void SetMt(int when, int howL);
	std::map<int, int> getMp();

	//tworzenie rozwiazania losowego ze zbioru zadan
	std::pair<Timeline, Timeline> Instancja(std::vector<Task> zadania, int N);

	//drugie podejscie
	std::pair<Timeline, Timeline> Timeline::Instancja123(std::vector<Task> zad);


	//sprawdzenie czy rozwiazanie jest dopuszczalne na tej maszynie: true jezeli jest dopuszczalne
	bool checkMach(std::vector<Task> zadania, int mach);

	//naprawianie eventualnego timeline'u dla konkretnej maszyny od konkretnego pkt na lini czasu
	void napraw(int pkt, std::vector<Task> zadania, int mach);

	//tworzenie ciagu do pliku wynikowego
	PrintableResult resOut(std::vector<Task> zadania, int machine);
	~Timeline();

	//tworzenie tablicy ju� uzytych N operacji
	std::vector<int> getUsdTasks(int N);

	//kopiowanie rozwi�zania do pewnego momentu dla m1
	std::vector<Timeline> copyTimeline(int dokiedy);

	//kopiowanie rozwi�zania od pewnego momentu dla m1
	std::vector<Timeline> copyTimelineend(int odkiedy);

	//kopiowanie rozwi�zania do pewnego momentu dla m2
	std::vector<Timeline> copyTimelineM2(int dokiedy);

	//kopiowanie rozwi�zania od pewnego momentu dla m2
	std::vector<Timeline> copyTimelineendM2(int odkiedy);

	//wyswietl
	void wyswietl(int od, int dok);

	//zwraca numer zadania kt�re jest N-te od pocz�tku
	int get_nr_zad(int N);

	//zwraca czas zako�czenia zadania pod miejscem zamiany(mutacja)
	int getTime_on_M2(int N);

	//uzyskanie indeksu gdzie juz zrobiono N operacji
	int getIAftrNTsks(int N);

	//uzyskanie czasu zakonczenia operacji zadania N na tym timeline'ie
	int whenDone(int N);

	//czy zadanie/przerwa s� w tych samych miejscach
	bool compareTsks(Timeline solution, int N);

	//zebranie zakonczen op1
	std::vector<Task> Timeline::getOp1Ends(std::vector<Task> z1, int mach);

	//sprawdzanie zgodnosci z druga maszyna dla tych samych zadan
	bool FirstIsFirst(Timeline otherOne, std::vector<Task> zadania, int mach);

	int TargetFnctn1(std::pair<Timeline, Timeline> rozw);
	int TargetFnctn2(std::pair<Timeline, Timeline> rozw);
	int TargetFnctn(std::pair<Timeline, Timeline> rozw);

	int fCelu();

private:
	std::map<int, int> mp;
};


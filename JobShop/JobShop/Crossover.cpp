#include "Crossover.h"
#include "stdafx.h"
#include <algorithm>

std::vector<std::pair<Timeline, Timeline>> crossing(std::vector<std::pair<Timeline, Timeline>> pop, int perc, std::vector<Task> z1)
{
	std::vector<Task> zadania = z1;
	int N = zadania.size();
	std::vector<std::pair<Timeline, Timeline>> res;
	res.clear();
	std::vector<std::pair<Timeline, Timeline>> tmp = pop;
	std::vector<int> usedSol;
	std::vector<int> usedTasks;
	usedSol.resize(pop.size());
	for (auto &i : usedSol)
	{
		i = 0;
	}
	int i1, i2, id;
	std::vector<int> Tsks;
	std::list<int> kol;
	std::pair<Timeline, Timeline> child1, child2;


	i1 = rand() % tmp.size();
	i2 = rand() % tmp.size();
	while (i1 == i2) i2 = rand() % tmp.size();
	//int nrOfTsks = (rand()%(std::ceil(0.8*N))) + (N - std::ceil(0.8*N));
	int nrOfTsks = 4;//rand() % N;
	//while(tmp[i1].first.cmp(tmp[i2].first)) i2 = rand() % tmp.size(); //jezeli wylosowano to samo zadanie losuj raz jeszcze

	child1 = tmp[i1];
	child2 = tmp[i2];

	//tworzenie rozwiazania dla M1 na podstawie zadan rodzica 2------------------------------------------------------------
	Tsks.resize(N);
	usedTasks = child1.first.getUsdTasks(nrOfTsks);
	for (auto &i : zadania)  //potrzeba "rt" dla op2 jezeli sa na M1
	{
		if (i.get_mach() == 2)
		{
			i.set_done_op1(child1.first.whenDone(i.get_nr()));
		}
	}

	std::cout <<"N: "<< N << std::endl;

	for (int i = 0; i < N; i++)Tsks[i] = (i+1);
	for (auto &i : usedTasks)
	{
		Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), i), Tsks.end()); //usuwanie wszystkich zadan kt juz wykonano
		std::cout << i << std::endl;
	}
	
	std::cout << "Po ilu ciac M1: " << nrOfTsks << std::endl << std::endl;
	for (auto &i : Tsks)
	{
		std::cout << i << std::endl;
	}

	child1.first.del(child1.first.getIAftrNTsks(nrOfTsks));
	//kolejkowanie dodawania zadan na podstawie drugiego parenta
	kol.clear();
	for (int i = 0; i < child2.first.getSoT(); i++)
	{
		if (std::find(Tsks.begin(), Tsks.end(), child2.first.getN(i)) != Tsks.end()) //jezeli aktualna wartos jest to dodaj js do kolejki i usunie ze zbioru wolnych zadan
		{
			kol.push_back(child2.first.getN(i));
			Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), child2.first.getN(i)), Tsks.end());
		}
	}

	id = zadania[kol.front()-1].get_rt();

	//umieszczanie zadan w kolejnosci
	while (!kol.empty()) 
	{
		int i = kol.front();
		kol.pop_front();
		i--;
		//if (id < zadania[i].get_rt()) id = zadania[i].get_rt(); //jezeli jest to op1
		if (zadania[i].get_mach() == 1)
		{
			if (id < zadania[i].get_rt()) id = zadania[i].get_rt(); //jezeli jest to op1
			int k = id;
			int empt = 0;
			while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
			{

				int c = 0;
				while (child1.first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
				if (zadania[i].get_op1() > 1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
				{
					while ((child1.first.getN(id + zadania[i].get_op1() - 1) != 0))id += zadania[i].get_op1(); // przeszukiwany koniec jest pusty
					for (c = id + 1; (c < id + zadania[i].get_op1() - 1) && child1.first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
					if ((c - (id + 1)) == zadania[i].get_op1() - 2) // jezeli same zera
					{
						empt = 1;
					}
					else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
					{
						id = c;
					}
				}
				else empt = 1;
			}
			int c = id;
			while (c < (id + zadania[i].get_op1()))
			{
				child1.first.set(c, i+1);
				c++;
			}
			zadania[i].set_done_op1(id + zadania[i].get_op1()); //ustaw op1 na done

		}
		else //jezeli op1 jest na DRUGIEJ maszynie, czyli wstawiamy tutaj op2
		{
			if (id < tmp[i1].second.whenDone(i+1)) id = tmp[i1].second.whenDone(i+1);
			int k = id;
			int empt = 0;
			while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
			{

				int c = 0;
				while (child1.first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
				if (zadania[i].get_op2()>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
				{
					while ((child1.first.getN(id + zadania[i].get_op2() - 1) != 0))id += zadania[i].get_op2(); // przeszukiwany koniec jest pusty
					for (c = id + 1; (c < id + zadania[i].get_op2() - 1) && child1.first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
					if ((c - (id + 1)) == zadania[i].get_op2() - 2) // jezeli same zera
					{
						empt = 1;
					}
					else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
					{
						id = c;
					}
				}
				else empt = 1;
			}
			int c = id;
			while (c < (id + zadania[i].get_op2())) //umiesc zadanie na osi czasu
			{
				child1.first.set(c, i + 1);
				c++;
			}
		}
	
	}
	//---------------------------------------------------------------------------------------------------------------
	//tworzenia rozw dla drugiej czesci M2
	Tsks.resize(N);
	usedTasks = child1.second.getUsdTasks(nrOfTsks);
	for (auto &i : zadania) //resetowanie zadan
	{
		i.reset();
	}

	for (int i = 0; i < N; i++)Tsks[i] = (i + 1);
	for (auto &i : usedTasks)
	{
		Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), i), Tsks.end()); //usuwanie wszystkich zadan kt juz wykonano
		std::cout << i << std::endl;
	}
	std::cout << "\nPo ilu ciac M2: " << nrOfTsks << std::endl << std::endl;
	for (auto &i : Tsks)
	{
		std::cout << i << std::endl;
	}
	child1.second.del(child1.first.getIAftrNTsks(nrOfTsks));
	
	//----------------------------------------------------------------------------------------------------------------
	std::cout << "Parent1 M1: \n";
	tmp[i1].first.test();
	std::cout << "Parent2 M1: \n";
	child2.first.test();
	std::cout << "Child1 M1: \n";
	child1.first.test();
	

	return tmp;
}


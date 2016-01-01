#include "Crossover.h"
#include "stdafx.h"
#include <algorithm>

std::vector<std::pair<Timeline, Timeline>> crossing(std::vector<std::pair<Timeline, Timeline>> pop, int perc, std::vector<Task> z1)
{
	std::vector<Task> zadania = z1;
	int N = zadania.size();
	std::vector<std::pair<Timeline, Timeline>> tmp = pop;
	std::vector<std::pair<Timeline, Timeline>> res;
	res.clear();
	std::vector<int> usedSol;
	std::vector<int> usedTasks;
	usedSol.resize(tmp.size());
	for (auto &i : usedSol)
	{
		i = 0;
	}
	int i1, i2, id;
	std::vector<int> Tsks;
	std::list<int> kol;
	std::vector<std::pair<Timeline, Timeline>> child;
	child.resize(2);

	i1 = rand() % tmp.size();
	i2 = rand() % tmp.size();
	while (i1 == i2) i2 = rand() % tmp.size();
	//int nrOfTsks = (rand()%(std::ceil(0.8*N))) + (N - std::ceil(0.8*N));
	int nrOfTsks = 2;//rand() %(N-2) + 1; //uciecie wszystkich zadan nie ma sensu tak samo uciecie wszystkich lub oprócz jednego, wiec ucinamy przynajmniej 2
	while(tmp[i1].first.cmp(tmp[i2].first)) i2 = rand() % tmp.size(); //jezeli wylosowano to samo zadanie losuj raz jeszcze
	int ren = 0;
	child[0] = tmp[i1];
	child[1] = tmp[i2];


	std::cout << i1 << "\tParent1 M1: \n";
	tmp[i1].first.test();
	std::cout << i1 << "\tParent1 M2: \n";
	tmp[i1].second.test();
	std::cout << i2 << "\tParent2 M1: \n";
	tmp[i2].first.test();
	std::cout << i2 << "\tParent2 M2: \n";
	tmp[i2].second.test();


	//tworzenie rozwiazania------------------------------------------------------------
	while (ren < child.size())
	{
		//pierwsza czesc z jednego rodzica + reszta na podstawie kolejnosci zadan w drugim rodzicu
		Tsks.resize(N);
		usedTasks = child[ren].first.getUsdTasks(nrOfTsks);
		for (auto &i : zadania)  //potrzeba "rt" dla op2 jezeli sa na M1
		{
			if (i.get_mach() == 2)
			{
				i.set_done_op1(child[ren].first.whenDone(i.get_nr()));
			}
		}

		std::cout << "N: " << N << std::endl;

		for (int i = 0; i < N; i++)Tsks[i] = (i + 1);
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

		child[ren].first.del(child[ren].first.getIAftrNTsks(nrOfTsks));
		//kolejkowanie dodawania zadan na podstawie drugiego parenta
		kol.clear();
		for (int i = 0; i < child[1 - ren].first.getSoT(); i++)
		{
			if (std::find(Tsks.begin(), Tsks.end(), child[1 - ren].first.getN(i)) != Tsks.end()) //jezeli aktualna wartos jest to dodaj ja do kolejki i usunie ze zbioru wolnych zadan
			{
				kol.push_back(child[1 - ren].first.getN(i));
				Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), child[1 - ren].first.getN(i)), Tsks.end());
			}
		}

		id = zadania[kol.front() - 1].get_rt();

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
					while (child[ren].first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
					if (zadania[i].get_op1() > 1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((child[ren].first.getN(id + zadania[i].get_op1() - 1) != 0))id += zadania[i].get_op1(); // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + zadania[i].get_op1() - 1) && child[ren].first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
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
					child[ren].first.set(c, i + 1);
					c++;
				}
				zadania[i].set_done_op1(id + zadania[i].get_op1()); //ustaw op1 na done

			}
			else //jezeli op1 jest na DRUGIEJ maszynie, czyli wstawiamy tutaj op2
			{
				if (id < tmp[i1].second.whenDone(i + 1)) id = tmp[i1].second.whenDone(i + 1);
				int k = id;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (child[ren].first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
					if (zadania[i].get_op2()>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((child[ren].first.getN(id + zadania[i].get_op2() - 1) != 0))id += zadania[i].get_op2(); // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + zadania[i].get_op2() - 1) && child[ren].first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
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
					child[ren].first.set(c, i + 1);
					c++;
				}
			}

		}
		//---------------------------------------------------------------------------------------------------------------
		//tworzenia rozw1 dla drugiej czesci M2
		Tsks.resize(N);
		usedTasks = child[ren].second.getUsdTasks(nrOfTsks);
		for (auto &i : zadania) //resetowanie zadan
		{
			i.reset();
		}

		for (int i = 0; i < N; i++)Tsks[i] = (i + 1);
		std::cout << std::endl;
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
		child[ren].second.del(child[ren].second.getIAftrNTsks(nrOfTsks));
		child[ren].second.napraw(child[ren].second.getIAftrNTsks(nrOfTsks), zadania, 2);
		//----------------------------------------------------------------------------------------------------------------
		std::cout << "Child" << ren + 1 << " M1: \n";
		child[ren].first.test();
		std::cout << "Child" << ren + 1 << " M2: \n";
		child[ren].second.test();
		
		ren++;
	}

	if (child[0].first.checkMach(zadania, 1) &&
		child[0].second.checkMach(zadania, 2) &&
		child[0].first.FirstIsFirst(child[0].second, zadania, 1) &&
		child[1].first.checkMach(zadania, 1) &&
		child[1].second.checkMach(zadania, 2) &&
		child[1].first.FirstIsFirst(child[1].second, zadania, 1)) //warunek sprawdzajacy poprawnosc rozwiazan
	{
		std::cout << "\tdobre rozw\n\n";
		res.insert(res.end(), child[0]);
		res.insert(res.end(), child[1]);
	}
	else
		std::cout << "\tno nie wyszlo\n\n\n";
	return res;
}


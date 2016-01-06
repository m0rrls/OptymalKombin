#include "Crossover.h"
#include "stdafx.h"
#include <algorithm>

std::vector<std::pair<Timeline, Timeline>> crossing(std::vector<std::pair<Timeline, Timeline>> pop, int perc, std::vector<Task> z1, int rozmiar)
{
	std::vector<Task> zadania = z1;
	int N = zadania.size();
	std::vector<std::pair<Timeline, Timeline>> tmp = pop;

	int wantedSize = std::ceil(pop.size() * perc / 100);

	while (tmp.size() > wantedSize) //wybieramy zadania kt zostana uzyte do krzyzowania
	{
		int los = rand() % tmp.size();
		tmp.erase(tmp.begin() + los); //poprzez usuwanie losowych az nie bedzie tyle ile ich chcemy
	}

	std::vector<std::pair<Timeline, Timeline>> res;
	res.clear();
	std::vector<std::vector<int>> usedSol;
	std::vector<int> usedTasks;
	usedSol.resize(tmp.size());
	for (auto &i : usedSol)
	{
		i.resize(tmp.size());
		for (auto &j : i)
		{
			j = 0;
		}
	}
	//usedSol[0][0] = 0;


	int i1, i2, id;
	std::vector<int> Tsks;
	std::list<int> kol;
	std::vector<std::pair<Timeline, Timeline>> child;
	child.resize(2);
	

	int licz = 0; //postep
	while (licz < rozmiar)
	{
		
		int nrOfTsks = rand() % (N - 2) + 1; //uciecie wszystkich zadan nie ma sensu tak samo uciecie wszystkich lub oprócz jednego, wiec ucinamy przynajmniej 2
		
		i1 = rand() % tmp.size();
		i2 = rand() % tmp.size();
		while (i1 == i2 || usedSol[i1][i2] == 1 || tmp[i1].first.cmp(tmp[i2].first)) //jezeli wylosowano te same liczby 
		{																			//lub wylosowano pare kt byla juz wczesniej krzyzowana 
			i1 = rand() % tmp.size();												//lub para ma tak samo uszeregowana M1
			i2 = rand() % tmp.size();
		}
		int ren = 0;
		child[0] = tmp[i1];
		child[1] = tmp[i2];

		/*
		std::cout << i1 << "\tParent1 M1: \n";
		tmp[i1].first.test();
		std::cout << i1 << "\tParent1 M2: \n";
		tmp[i1].second.test();
		std::cout << i2 << "\tParent2 M1: \n";
		tmp[i2].first.test();
		std::cout << i2 << "\tParent2 M2: \n";
		tmp[i2].second.test();
		*/

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
				if (i.get_mach() == 1)
				{
					i.set_done_op1(child[ren].second.whenDone(i.get_nr()));
				}
			}

			//std::cout << "N: " << N << std::endl;

			int usT = 0;
			for (int i = 0; i < N; i++)Tsks[i] = (i + 1);
			for (auto &i : usedTasks)
			{
				Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), i), Tsks.end()); //usuwanie wszystkich zadan kt juz wykonano
			//	std::cout << i << std::endl;
			}

			//std::cout << "Po ilu ciac M1: " << nrOfTsks << std::endl << std::endl;
			for (auto &i : Tsks)
			{
				usT++;
			//	std::cout << i << std::endl;
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
			//std::cout << std::endl;
			for (auto &i : usedTasks)
			{
				Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), i), Tsks.end()); //usuwanie wszystkich zadan kt juz wykonano
			//	std::cout << i << std::endl;
			}
			//std::cout << "\nPo ilu ciac M2: " << nrOfTsks << std::endl << std::endl;

			for (auto &i : Tsks)
			{
			//	std::cout << i << std::endl;
			}
			if (Tsks.size() == usT)
			{
				zadania = child[ren].first.getOp1Ends(zadania, 1);
				child[ren].second.del(child[ren].second.getIAftrNTsks(nrOfTsks));
				child[ren].second.napraw(child[ren].second.getIAftrNTsks(nrOfTsks), zadania, 2);
			}

			//----------------------------------------------------------------------------------------------------------------
			/*
			std::cout << "Child" << ren + 1 << " M1: \n";
			child[ren].first.test();
			std::cout << "Child" << ren + 1 << " M2: \n";
			child[ren].second.test();
			*/
			
			if (child[ren].first.checkMach(zadania, 1) &&
				child[ren].second.checkMach(zadania, 2) &&
				child[ren].first.FirstIsFirst(child[ren].second, zadania, 1))
			{
				ren++;
			}
			else //
			{
				bool ch1 = child[ren].first.checkMach(zadania, 1);
				bool ch2 = child[ren].second.checkMach(zadania, 2);
				bool ch3 = child[ren].first.FirstIsFirst(child[ren].second, zadania, 1);
				ren = 0;
				nrOfTsks = rand() % (N - 2) + 1;
				child[0] = tmp[i1];
				child[1] = tmp[i2];
			}

		}

		if (child[0].first.checkMach(zadania, 1) &&
			child[0].second.checkMach(zadania, 2) &&
			child[0].first.FirstIsFirst(child[0].second, zadania, 1) &&
			child[1].first.checkMach(zadania, 1) &&
			child[1].second.checkMach(zadania, 2) &&
			child[1].first.FirstIsFirst(child[1].second, zadania, 1)) //warunek sprawdzajacy poprawnosc rozwiazan
		{
			licz++;
			//std::cout << "\tdobre rozw nr "<< licz << std::endl;
			licz++;
			//std::cout << "\tdobre rozw nr " << licz << std::endl;
			res.insert(res.end(), child[0]);
			res.insert(res.end(), child[1]);

			//if (i1 > i2)
			//{
				//tmp.erase(tmp.begin() + i1);
				//tmp.erase(tmp.begin() + i2);
			//}
			//else
			//{
				//tmp.erase(tmp.begin() + i2);
				//tmp.erase(tmp.begin() + i1);
			//}

			usedSol[i1][i2] = 1; //
			usedSol[i2][i1] = 1; //uzyto juz ten pary
		}
		else
			std::cout << "\t\tno nie wyszlo\n\n\n";
	}
	return res;
}


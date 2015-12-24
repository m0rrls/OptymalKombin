#include "stdafx.h"
#include "Timeline.h"





void Timeline::maintenance(int i, int maxL) //dodaje przerwy techniczne dla N zadan w stosunku kN do liczby zadan
{													//gdzie  podana jest maksymalna dlugosc przerwy, jezeli jest
	//srand(time(0));								//skonfigurowane by wiêcej przer by³o na poczatku a szansa na przerwe malala
	//int i = ceil(N * kN);							//wraz z numerem pozycji przerwy w tablicy
	int j = 0;
	while (j < i)
	{
		int start = rand() % tab.size();
		int len = rand() % maxL + 1;
		int alrdyTkn = 0;
		int k = start - 1;
		if (start == 0) k = start;
		int l = start + len;
		if (l >= tab.size()) l = tab.size() - 1;
		int pom = k;

		while (!alrdyTkn && k < l+1)
		{
			if (tab[k] == -1)
			{
				alrdyTkn = 1;
			}
			k++;
		}
		int h = rand()%100 + 1;
		int g = std::ceil(100*start / (double)(tab.size()));
		if (!alrdyTkn && h < (100 - g))
		{
			for (pom; pom < l; pom++)
				tab[pom] = -1;
			j++;
		}
	}
}

void Timeline::randomMaint(int i, int maxL)
{
	int j = 0;
	while (j < i)
	{
		int start = rand() % tab.size();
		int len = rand() % maxL + 1;
		int alrdyTkn = 0;
		int k = start - 1;
		if (start == 0) k = start;
		int l = start + len;
		if (l >= tab.size()) l = tab.size() - 1;
		int pom = k;

		while (!alrdyTkn && k < l + 1)
		{
			if (tab[k] == -1)
			{
				alrdyTkn = 1;
			}
			k++;
		}

		for (pom; pom < l; pom++)
			tab[pom] = -1;
		j++;

	}
}

void Timeline::CntMt()
{
	int i = 0;
	while (i < tab.size())
	{
		int j = 0;
		if (tab[i] == -1)
		{
			int k = i;
			while (tab[i++] == -1)
			{
				j++;
			}
			mp.insert(std::pair<int, int>(k, j));
		}
		else
			i++;
	}
}

void Timeline::SetMt(int when, int howL)
{
	int tmp = when;
	for (int i=when; i < (when + howL); i++)
	{
		tab[i] = -1;
	}
}

std::map<int, int> Timeline::getMp()
{
	return mp;
}

std::pair<Timeline, Timeline> Timeline::Instancja(std::vector<Task> z1, int N)
{
	std::vector<Task> zadania = z1;
	std::pair<Timeline, Timeline> rozw;
	std::vector<int> alrdyUsd;
	alrdyUsd.resize(2*N);
	for (int i = 0; i < (2*N); i++)alrdyUsd[i] = 0;
	int done = 0;
	rozw.first.tab = tab;
	rozw.second.tab.resize(tab.size());
	for (int i = 0; i < tab.size(); i++)rozw.second.tab[i] = 0;
	while (!done)
	{
		int zad = rand() % N;
		if (!alrdyUsd[zad]) //jezeli op1 nie zostala uzyta
		{
			if (zadania[zad].get_mach() == 1) //jezeli op1 jest na PIERWSZEJ maszynie
			{
				int id = zadania[zad].get_rt();
				int k = id;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (rozw.first.tab[id] != 0)id++; //przeszukiwany poczatek jest pusty
					if (zadania[zad].get_op1()>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((rozw.first.tab[id + zadania[zad].get_op1() - 1] != 0))id += zadania[zad].get_op1(); // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + zadania[zad].get_op1() - 1) && rozw.first.tab[c] == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == zadania[zad].get_op1() - 2) // jezeli same zera
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
				while (c < (id + zadania[zad].get_op1()))
				{
					rozw.first.tab[c] = zadania[zad].get_nr();
					c++;
				}
				zadania[zad].set_done_op1(id + zadania[zad].get_op1()); //ustaw op1 na done
			}
			else //jezeli op1 jest na DRUGIEJ
			{
				int id = zadania[zad].get_rt();
				int k = id;
				int empt=0;
				while (empt==0) //szukaj miejsca gdzie mozna umiescic zadanie
				{
					
					int c = 0;
					while (rozw.second.tab[id] != 0)id++; //przeszukiwany poczatek jest pusty
					if (zadania[zad].get_op1()>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((rozw.second.tab[id + zadania[zad].get_op1() - 1]) != 0)id += zadania[zad].get_op1(); // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + zadania[zad].get_op1() - 1) && rozw.second.tab[c] == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == zadania[zad].get_op1() - 2) // jezeli same zera
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
				while (c < (id + zadania[zad].get_op1()))
				{
					rozw.second.tab[c] = zadania[zad].get_nr();
					c++;
				}
				zadania[zad].set_done_op1(id+zadania[zad].get_op1()); //ustaw op1 na done
			}
			alrdyUsd[zad] = 1;
		}
		else if (!alrdyUsd[zad + N] && zadania[zad].get_done_op1()>0) //jezeli op1 zostala zrobiona a op2 nie
		{
			if (zadania[zad].get_mach() == 1) //jezeli op2 jest na DRUGIEJ maszynie (op1 jest na PIERWSZEJ)
			{
				int id = zadania[zad].get_done_op1();
				int k = id;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (rozw.second.tab[id] != 0)id++; //przeszukiwany poczatek jest pusty
					if (zadania[zad].get_op2()>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((rozw.second.tab[id + zadania[zad].get_op2() - 1] != 0))id += zadania[zad].get_op2(); // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + zadania[zad].get_op2() - 1) && rozw.second.tab[c] == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == zadania[zad].get_op2() - 2) // jezeli same zera
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
				while (c < (id + zadania[zad].get_op2())) //umiesc zadanie na osi czasu
				{
					rozw.second.tab[c] = zadania[zad].get_nr();
					c++;
				}
			}
			else //jezeli op2 jest na PIERWSZEJ maszynie (op1 jest na DRUGIEJ)
			{
				int id = zadania[zad].get_done_op1();
				int k = id;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (rozw.first.tab[id] != 0)id++; //przeszukiwany poczatek jest pusty
					if (zadania[zad].get_op2()>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((rozw.first.tab[id + zadania[zad].get_op2() - 1] != 0))id += zadania[zad].get_op2(); // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + zadania[zad].get_op2() - 1) && rozw.first.tab[c] == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == zadania[zad].get_op2() - 2) // jezeli same zera
						{
							empt = 1;
						}
						else
						{
							id = c;
						}
					}
					else empt = 1;
				}
				int c = id;
				while (c < (id + zadania[zad].get_op2()))
				{
					rozw.first.tab[c] = zadania[zad].get_nr();
					c++;
				}
			}
			alrdyUsd[zad + N] = 1; //ustaw op2 na done
		}
		//spr czy uzyto juz wszystkich zadan
		int check = 0;
		for each (int i in alrdyUsd)
		{
			check += i;
		}
		if (check == 2*N)
		{
			done = 1;
		}

	}
	return rozw;
}


PrintableResult Timeline::resOut(std::vector<Task> zadania, int machine)
{
	std::string res = "";
	int i = 0;
	int sumM = 0;
	int sumI = 0;
	int idM = 1;
	int idI = 1;
	while (i < tab.size())
	{
		if (tab[i] == -1) //jezeli przerwa tech.
		{
			res += ("maint" + std::to_string(idM++) + "_M" + std::to_string(machine) + ", ");
			res += (std::to_string(i) + ", ");
			int j = 0;
			while (i < tab.size() && tab[i] == -1)
			{
				j++;
				i++;
			}
			sumM += j;
			res += (std::to_string(j) + "; ");
		}
		else if (tab[i] == 0) //jezeli nic nie jest robione
		{
			res += ("idle" + std::to_string(idI++) + "_M" + std::to_string(machine) + ", ");
			res += (std::to_string(i) + ", ");
			int j = 0;
			while (i < tab.size() && tab[i] == 0)
			{
				j++;
				i++;
			}
			sumI += j;
			res += (std::to_string(j) + "; ");
		}
		else
		{
			res += "op";
			if (zadania[tab[i] - 1].get_mach() == machine) //jezeli jest to maszyna na kt jest wykonywana op1
			{
				res += "1_";
			}
			else
			{
				res += "2_";
			}
			res += (std::to_string(tab[i]) + ", " + std::to_string(i) + ", ");
			int j = 0;
			int pom = tab[i];
			while (i < tab.size() && tab[i] == pom)
			{
				j++;
				i++;
			}
			res += (std::to_string(j) + "; ");
		}
	}
	PrintableResult* out = new PrintableResult();

	out->setALL(idM-1, sumM, idI-1, sumI);
	out->res(res);
	return *out;
}

Timeline::~Timeline()
{
}

std::vector<int> Timeline::getUsdTasks(int N)
{
	int i = 0;
	int j = 0;
	std::vector<int> vec;
	vec.clear();
	while (j < N && i < tab.size())
	{
		if (tab[i] > 0)
		{
			vec.insert(vec.end(), tab[i]);
			j++;
			int pom = tab[i];
			while (tab[i] == pom)i++;
		}
		else i++;
	}
	return vec;
}

int Timeline::getIAftrNTsks(int N)
{
	int i = 0;
	int j = 0;
	while (j < N && i < tab.size())
	{
		if (tab[i] > 0)
		{
			j++;
			int pom = tab[i];
			while (tab[i] == pom)i++;
		}
		else i++;
	}
	return i;
}

int Timeline::whenDone(int N)
{
	for (int i = 0; i < tab.size(); i++) 
	{
		if (tab[i] == N)
		{
			while (tab[i]==N)
			{
				i++;
			}
			return i;
		}
	}
	return -1;
}


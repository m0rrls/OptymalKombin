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

Timeline::~Timeline()
{
}

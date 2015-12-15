#include "stdafx.h"
#include "Readytime.h"


void Readytime::rdm()
{
	srand(time(0));
	int i = 0;
	for (i; i <= (tab.size()-1)/3.0; i++)
	{
		tab[i] = rand() % ((tab.size() - 1) /3);
	}
	for (i; i <= 2* (tab.size() - 1) / 3.0; i++)
	{
		tab[i] = rand() % ((tab.size() - 1) /3) + ceil(tab.size() /3.0);
	}
	for (i; i <= (tab.size() - 1); i++)
	{
		tab[i] = rand() % ((tab.size() - 1) /3) + ceil(2* tab.size() /3.0);
	}
}


Readytime::~Readytime()
{
}

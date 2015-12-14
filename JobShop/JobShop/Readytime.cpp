#include "stdafx.h"
#include "Readytime.h"


void Readytime::rdm(int start, int end)
{
	srand(time(0));
	int i = start;
	for (i; i <= end/3; i++)
	{
		tab[i] = rand() % (end/3);
	}
	for (i; i <= 2*end/3; i++)
	{
		tab[i] = rand() % (end/3) + ceil(end/3);
	}
	for (i; i <= end; i++)
	{
		tab[i] = rand() % (end/3) + ceil(2*end/3);
	}
}


Readytime::~Readytime()
{
}

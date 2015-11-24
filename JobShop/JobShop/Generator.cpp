#include "stdafx.h"
#include "Generator.h"
#include <time.h>



Generator::Generator(int l)
{
	len = l;
	tab.resize(l);
}


Generator::~Generator()
{
}

void Generator::rdm(int start, int end, int k) 
{
	srand(time(0));
	int i = start;
	for (i; i < end; i++) 
	{
		tab[i] = rand() % k + 1;
	}
}
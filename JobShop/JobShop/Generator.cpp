#include "stdafx.h"
#include "Generator.h"
#include <time.h>

using namespace std;

Generator::Generator(int l)
{
	tab.resize(l);
}


Generator::~Generator()
{
}

void Generator::rdm(int start, int end, int k) 
{
	srand(time(0));
	int i = start;
	for (i; i <= end; i++) 
	{
		tab[i] = rand() % k + 1;
	}
}

void Generator::test()
{
	for (int j = 0; j < (int)tab.size(); j++) 
	{
		cout << tab[j] << " ";
	}
	cout << endl;
}

int Generator::getN(int a)
{
	int j;
	j = this->tab[a];
	return j;
}

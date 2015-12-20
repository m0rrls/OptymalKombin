#include "stdafx.h"
#include "Generator.h"
#include <time.h>

using namespace std;

Generator::Generator()
{
	//tab.resize(0);
}

Generator::Generator(int l)
{
	tab.resize(l);
}


Generator::~Generator()
{
}

void Generator::rdm(int start, int end, int k, int j) 
{
	//srand(time(0));
	int i = start;
	for (i; i <= end; i++) 
	{
		tab[i] = rand() % (j-k) + 1 + k;
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
	return tab[a];
}

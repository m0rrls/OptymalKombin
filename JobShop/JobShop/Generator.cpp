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

int Generator::getSoT()
{
	return tab.size();
}

bool Generator::cmp(Generator a)
{
	int i = 0;
	while (i < this->getSoT())
	{
		if (getN(i) != a.getN(i)) return false;
		else i++;
	}
	return true;
}

void Generator::del(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		if (tab[i] > 0) tab[i] = 0;
	}
}

void Generator::del(int start)
{
	for (int i = start; i < tab.size(); i++)
	{
		if (tab[i] > 0) tab[i] = 0;
	}
}

void Generator::
add(int val)
{
	tab.insert(tab.end(), val);
}

void Generator::add(std::vector<int> vec)
{
	tab.insert(tab.end(), vec.begin(), vec.end());
}

void Generator::set(int it, int val)
{
	tab[it] = val;
}

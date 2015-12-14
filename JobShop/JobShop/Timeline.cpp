#include "stdafx.h"
#include "Timeline.h"




void Timeline::maintenance(int N, float kN, int maxL) //dodaje przerwy techniczne dla N zadan w stosunku kN do liczby zadan
{													//gdzie  podana jest maksymalna dlugosc przerwy, jezeli jest
	srand(time(0));									
	int i = ceil(N * kN);
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
		if (!alrdyTkn)
		{
			for (pom; pom < l; pom++)
				tab[pom] = -1;
			j++;
		}
	}
}

Timeline::~Timeline()
{
}

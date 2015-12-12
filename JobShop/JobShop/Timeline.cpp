#include "stdafx.h"
#include "Timeline.h"




void Timeline::maintenance(int N, float kN, int maxL) //dodaje przerwy techniczne dla N zadan w stosunku kN do liczby zadan
{													//gdzie  podana jest maksymalna dlugosc przerwy
	srand(time(0));									//generowane przerwy mog¹ siê nak³adaæ, ale narazie nie wiem czy to cos zmienia
	int i = ceil(N * kN);
	int j = 0;
	for (j; j < i; j++)
	{
		int start = rand() % tab.size();
		int len = rand() % maxL + 1;
		if(start + len < tab.size())
			for (int k = start; k < start + len; k++)
				tab[k] = -1;
	
	}

}

Timeline::~Timeline()
{
}

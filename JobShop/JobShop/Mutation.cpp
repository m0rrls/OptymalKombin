#include "stdafx.h"
#include "Mutation.h"
#include <vector>

std::pair<Timeline, Timeline> Mutacja(std::pair<Timeline, Timeline> rozw, std::vector<Task> zadania1, int N, int mutChance)
{
	srand(time(0));

	if (rand() % 101 <= mutChance) {

		std::vector <int> Tsks;
		std::pair<Timeline, Timeline> rozw1 = rozw;
		std::vector<Task> zadania = zadania1;

		int x = 0, y = 0;

		x = rand() % N;
		y = rand() % N;
		while(x==y)y = rand() % N;








		return rozw1;
	}
	return rozw;
}
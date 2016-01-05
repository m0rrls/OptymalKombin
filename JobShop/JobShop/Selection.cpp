#include "stdafx.h"
#include <vector>
#include "Selection.h"
/*
template <class T>
std::vector<std::pair<typename T, typename T>> Selekcja(std::vector<std::pair<typename T, typename T>> instancje, int N, std::vector<int> wart)
{
	std::vector<std::pair<typename T, typename T>> wybrane;
	int i = 0;
	int max;
	int cel = 0;
	while (i < Selekcja.size() - 1) {
		max = wart[i];
		cel = i;
		for (int j = 1; j < 4;j++) {
			if (wart[i + j] > max) {
				max = wart[i + j];
				cel = i + j;
			}
		}
		wybrane.push_back(Selekcja[i]);

		i = i + 4;
	}





	return wybrane;
}
*/
std::vector<std::pair<Timeline, Timeline>> wybierz(std::vector<std::pair<Timeline, Timeline>> populacja, int k)
{
	std::vector<std::pair<Timeline, Timeline>> wybrane;
	wybrane.clear();

	int groupSize = std::ceil(populacja.size() / k);

	std::vector<std::pair<Timeline, Timeline>> pozostalo = populacja;
	while (!pozostalo.empty())
	{
		int los = rand() % pozostalo.size();
		std::pair<Timeline, Timeline> bestSol = pozostalo[los];
		pozostalo.erase(pozostalo.begin() + los);
		int min = bestSol.first.TargetFnctn(bestSol);
		for (int i = 0; i < (groupSize - 1) && !pozostalo.empty(); i++)
		{
			los = rand() % pozostalo.size();
			std::pair<Timeline, Timeline> tmp = pozostalo[los];
			pozostalo.erase(pozostalo.begin() + los);
			int pom = tmp.first.TargetFnctn(tmp);
			if (min > pom)
			{
				min = pom;
				bestSol = tmp;
			}
		}
		wybrane.insert(wybrane.end(), bestSol);
	}
	

	return wybrane;
}

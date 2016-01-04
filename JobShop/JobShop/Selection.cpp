#include "stdafx.h"
#include <vector>
#include "Selection.h"

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

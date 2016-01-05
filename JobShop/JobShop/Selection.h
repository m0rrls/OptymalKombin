#pragma once
#include<vector>

//selekcja; arg: populacja, liczba rozw kt pozostana
std::vector<std::pair<Timeline, Timeline>> wybierz(std::vector <std::pair<Timeline, Timeline>> populacja, int k);
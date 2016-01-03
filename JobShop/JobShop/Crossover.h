#pragma once
#include "stdafx.h"


//krzyzowanie jedno punktowe; arg: stara populacja, ile procent ma byc krzyzowane, zadania, rozmiar nowej populacji
std::vector<std::pair<Timeline, Timeline>> crossing(std::vector<std::pair<Timeline, Timeline>> pop, int perc, std::vector<Task> zadania, int rozmiar);
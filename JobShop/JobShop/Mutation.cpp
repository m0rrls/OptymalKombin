#include "stdafx.h"
#include "Mutation.h"
#include <algorithm>

std::pair<Timeline, Timeline> Mutacja(std::pair<Timeline, Timeline> rozw, std::vector<Task> zadania1, int N, int mutChance)
{
	srand(time(0));

	if (rand() % 101 <= mutChance) {

		//DEKLARACJE

		std::vector <int> Tsks;
		Tsks.resize(N);
		std::vector <int> usedTasks;
		std::pair<Timeline, Timeline> rozw1 = rozw;
		std::vector<Task> zadania = zadania1;
		std::pair<Timeline, Timeline> tmpbegin;
		std::pair<Timeline, Timeline> tmp;
		//		std::pair<Timeline, Timeline> tmpend;		//TO NIE MA SENSU
		std::list<int> kol_po_M1;			//kolejka zadañ po zamianie
		std::list<int> kol_po_M2;			//kolejka zadañ po zamianie
		std::list<int> kol_M1;				//kolejka zadañ w obszarze zamian
		std::list<int>::iterator itM1 = kol_M1.begin();
		std::list<int> kol_M2;				//kolejka zadañ w obszarze zamian
		std::list<int>::iterator itM2 = kol_M2.begin();

		int x = 0, y = 0, pom = 0;
		int xmach = 0, ymach = 0;
		int xzad = 0, yzad = 0;		//numery zadañ

									//LOSOWANIE ZADAÑ
		x = rand() % N + 1;				//które zadanie od pocz¹tku
		y = rand() % N + 1;				//które zadanie od pocz¹tku
		while (x == y)y = rand() % N;

		if (x > y) { pom = x; x = y; y = pom; }

		//NR ZADAN
		xzad = rozw1.first.get_nr_zad(x);
		yzad = rozw1.first.get_nr_zad(y);

		xmach = zadania[xzad].get_mach();		//na której maszynie
		ymach = zadania[yzad].get_mach();		//na której maszynie

												//CZASY ZADAN
		int tx_m1 = rozw1.first.whenDone(xzad);			//czas skoñczenia zadania przed x
		int ty_m1 = rozw1.first.whenDone(yzad);			//czas skoñczenia zadania y 
		int tx_m2 = rozw1.second.getTime_on_M2(tx_m1);
		int ty_m2 = rozw1.second.getTime_on_M2(ty_m1);

		if (xmach == 1) tx_m1 = tx_m1 - zadania[xzad].get_op1();	//czas skoñczenia zadania przed x
		else
			tx_m1 = tx_m1 - zadania[xzad].get_op2();

		//ZADANIA KTORE BYLY UZYTE	I VECTOR NIE UZYTYCH ZADAN	
		for (int i = 0; i < N; i++)Tsks[i] = (i + 1);

		usedTasks = rozw1.first.getUsdTasks(x);			//zadania które by³y u¿yte

		for (auto &i : usedTasks)
		{
			Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), i), Tsks.end()); //usuwanie wszystkich zadan kt juz wykonano
		}

		// KOPIOWANIE ROZW PRZED MIEJSCEM ZAMIANY
		//tmpbegin.first.copyTimeline(tx_m1);				//kopiowanie przodu rozw M1
		//tmpbegin.second.copyTimelineM2(tx_m1);			//kopiowanie przodu rozw M2


														// BEZ SENSU, BO ZADANIA MOGA SIE PRZESUNAC														
														//		tmpend.first.copyTimelineend(ty_m1 + 1);		//kopiowanie ty³u rozwi¹zania M1
														//		tmpend.second.copyTimelineendM2(ty_m1 + 1);		//kopiowanie tylu rozw M2

		tmpbegin.first.wyswietl(0, tx_m1);

		//TWORZENIE KOLEJKI ZADAN W OBSZARZE ZAMIANY
		kol_M1.clear();
		for (int i = tx_m1 + 1; i < ty_m1; i++)
		{
			if (std::find(Tsks.begin(), Tsks.end(), rozw1.first.getN(i)) != Tsks.end()) //jezeli aktualna wartos jest to dodaj ja do kolejki i usunie ze zbioru wolnych zadan
			{
				kol_M1.push_back(rozw1.first.getN(i));
				Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), rozw1.first.getN(i)), Tsks.end());
			}
		}
		kol_M2.clear();
		for (int i = tx_m2 + 1; i < ty_m2; i++)
		{
			if (std::find(Tsks.begin(), Tsks.end(), rozw1.second.getN(i)) != Tsks.end()) //jezeli aktualna wartos jest to dodaj ja do kolejki i usunie ze zbioru wolnych zadan
			{
				kol_M2.push_back(rozw1.second.getN(i));
				Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), rozw1.second.getN(i)), Tsks.end());
			}
		}
		//TWORZENIE KOLEJKI ZADAN PO OBSZARZE ZAMIANY
		kol_po_M1.clear();
		for (int i = ty_m1 + 1; i < rozw1.first.getSoT(); i++)
		{
			if (std::find(Tsks.begin(), Tsks.end(), rozw1.first.getN(i)) != Tsks.end()) //jezeli aktualna wartos jest to dodaj ja do kolejki i usunie ze zbioru wolnych zadan
			{
				kol_po_M1.push_back(rozw1.first.getN(i));
				Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), rozw1.first.getN(i)), Tsks.end());
			}
		}
		kol_po_M2.clear();
		for (int i = ty_m2 + 1; i < rozw1.second.getSoT(); i++)
		{
			if (std::find(Tsks.begin(), Tsks.end(), rozw1.second.getN(i)) != Tsks.end()) //jezeli aktualna wartos jest to dodaj ja do kolejki i usunie ze zbioru wolnych zadan
			{
				kol_po_M2.push_back(rozw1.second.getN(i));
				Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), rozw1.second.getN(i)), Tsks.end());
			}
		}

		//KOPIOWANIE NA TMP POCZATKU BEZ ZMIAN

		for (int i = 0;i < tx_m1 + 1;i++) {
			tmp.first.set(i, tmpbegin.first.getN(i));
		}
		for (int i = 0;i < tx_m2 + 1;i++) {
			tmp.second.set(i, tmpbegin.second.getN(i));
		}

		//MODYFIKOWANIE KOLEJKI, TAK ABY GDY SA OBIE OPERACJE W OBSZARZE ZAMIANY, TO op1 BYLO PIERWSZE
		//kol_M1
		//kol_M2

		int zadx = 0, zady = 0, zadpom = 0;
		zadx = kol_M1.back();
		kol_M1.pop_back();
		zady = kol_M1.front();
		kol_M1.pop_front();
		kol_M1.push_back(zady);
		kol_M1.push_front(zadx);
		if (zadania[zadx].get_mach() == 2) {
			for (auto itM2 = kol_M2.begin(); itM2 != kol_M2.end(); itM2++) {
				if (*itM2 == zadx) {

				}
			}
		}





		return rozw1;
	}
	return rozw;
}
#include "stdafx.h"
#include "Mutation.h"
#include <algorithm>

std::pair<Timeline, Timeline> Mutacja(std::pair<Timeline, Timeline> rozw, std::vector<Task> zadania1, int N, int mutChance)
{
	srand(time(0));

	if (rand() % 101 <= mutChance) {

		//DEKLARACJE

		std::vector <int> Tsks_M1;
		std::vector <int> Tsks_M2;
		Tsks_M1.resize(N); Tsks_M2.resize(N);
		std::vector <int> usedTasks_M1;
		std::vector <int> usedTasks_M2;
		std::pair<Timeline, Timeline> rozw1 = rozw;
		std::vector<Task> zadania = zadania1;
		Timeline *newTimeline = new Timeline(N*N);
		std::pair<Timeline, Timeline> tmpbegin;
		tmpbegin.first = *newTimeline;
		tmpbegin.second = *newTimeline;
		std::pair<Timeline, Timeline> tmp;
		tmp.first = *newTimeline;
		tmp.second = *newTimeline;
		//		std::pair<Timeline, Timeline> tmpend;		//TO NIE MA SENSU
		std::list<int> kol_po_M1;			//kolejka zada� po zamianie
		std::list<int> kol_po_M2;			//kolejka zada� po zamianie
		std::list<int>::iterator itM2_po = kol_po_M2.begin();	
		std::list<int> kol_M1;				//kolejka zada� w obszarze zamian
		std::list<int>::iterator itM1 = kol_M1.begin();
		std::list<int> kol_M2;				//kolejka zada� w obszarze zamian
		std::list<int>::iterator itM2 = kol_M2.begin();

		int x = 0, y = 0, pom = 0;
		int xmach = 0, ymach = 0;
		int xzad = 0, yzad = 0;		//numery zada�

									//LOSOWANIE ZADA�
		x = rand() % (N-1) + 2;				//kt�re zadanie od pocz�tku
		y = rand() % (N-1) + 2;				//kt�re zadanie od pocz�tku
		while (x == y)y = rand() % (N-1)+2;

		if (x > y) { pom = x; x = y; y = pom; }

		//NR ZADAN
		xzad = rozw1.first.get_nr_zad(x);
		yzad = rozw1.first.get_nr_zad(y);

		xmach = zadania[xzad-1].get_mach();		//na kt�rej maszynie
		ymach = zadania[yzad-1].get_mach();		//na kt�rej maszynie

												//CZASY ZADAN
		int tx_m1 = rozw1.first.whenDone(xzad);			//czas sko�czenia zadania przed x
		int ty_m1 = rozw1.first.whenDone(yzad);			//czas rozpoczecia zadania po zadaniu y 
		
		if (xmach == 1) tx_m1 = tx_m1 - zadania[xzad - 1].get_op1()-1;	//czas sko�czenia zadania przed x
		else
			tx_m1 = tx_m1 - zadania[xzad - 1].get_op2();

		int tx_m2 = rozw1.second.getTime_on_M2(tx_m1);	//czas sko�czenia zadania na M2 kt�re jest pod M1
		int ty_m2 = rozw1.second.getTime_on_M2(ty_m1);
		//ZADANIA KTORE BYLY UZYTE	I VECTOR NIE UZYTYCH ZADAN	
		for (int i = 0; i < N; i++) { Tsks_M1[i] = (i + 1);Tsks_M2[i] = (i + 1);
		}

		usedTasks_M1 = rozw1.first.getUsdTasks(x-1);			//zadania kt�re by�y u�yte
		usedTasks_M2 = rozw1.second.getUsdTasks(x - 1);			//zadania kt�re by�y u�yte
		
		for (auto &i : usedTasks_M1)
		{
			Tsks_M1.erase(std::remove(Tsks_M1.begin(), Tsks_M1.end(), i), Tsks_M1.end()); //usuwanie wszystkich zadan kt juz wykonano
		}
		for (auto &i : usedTasks_M2)
		{
			Tsks_M2.erase(std::remove(Tsks_M2.begin(), Tsks_M2.end(), i), Tsks_M2.end()); //usuwanie wszystkich zadan kt juz wykonano
		}
		// KOPIOWANIE ROZW PRZED MIEJSCEM ZAMIANY

		for (int i = 0;i < tx_m1 +1;i++) {
			tmp.first.set(i, rozw1.first.getN(i));
		}
		for (int i = 0;i < tx_m2 + 1;i++) {
			tmp.second.set(i, rozw1.second.getN(i));
		}
		
//NIEPOTRZEBNE I NIE DO KONCA DZIALA		
//		tmpbegin.first.copyTimeline(tx_m1);				//kopiowanie przodu rozw M1
//		tmpbegin.second.copyTimelineM2(tx_m2);			//kopiowanie przodu rozw M2


														// BEZ SENSU, BO ZADANIA MOGA SIE PRZESUNAC														
														//		tmpend.first.copyTimelineend(ty_m1 + 1);		//kopiowanie ty�u rozwi�zania M1
														//		tmpend.second.copyTimelineendM2(ty_m1 + 1);		//kopiowanie tylu rozw M2

		tmp.first.test();
		std::cout<<std::endl;
		tmp.second.test();

		//TWORZENIE KOLEJKI ZADAN W OBSZARZE ZAMIANY
		kol_M1.clear();
		for (int i = tx_m1 + 1; i < ty_m1; i++)
		{
			if (std::find(Tsks_M1.begin(), Tsks_M1.end(), rozw1.first.getN(i)) != Tsks_M1.end()) //jezeli aktualna wartos jest to dodaj ja do kolejki i usunie ze zbioru wolnych zadan
			{
				kol_M1.push_back(rozw1.first.getN(i));
				Tsks_M1.erase(std::remove(Tsks_M1.begin(), Tsks_M1.end(), rozw1.first.getN(i)), Tsks_M1.end());
			}
		}
		kol_M2.clear();
		for (int i = tx_m2 + 1; i < ty_m2; i++)
		{
			if (std::find(Tsks_M2.begin(), Tsks_M2.end(), rozw1.second.getN(i)) != Tsks_M2.end()) //jezeli aktualna wartos jest to dodaj ja do kolejki i usunie ze zbioru wolnych zadan
			{
				kol_M2.push_back(rozw1.second.getN(i));
				Tsks_M2.erase(std::remove(Tsks_M2.begin(), Tsks_M2.end(), rozw1.second.getN(i)), Tsks_M2.end());
			}
		}
		//TWORZENIE KOLEJKI ZADAN PO OBSZARZE ZAMIANY
		kol_po_M1.clear();
		for (int i = ty_m1 + 1; i < rozw1.first.getSoT(); i++)
		{
			if (std::find(Tsks_M1.begin(), Tsks_M1.end(), rozw1.first.getN(i)) != Tsks_M1.end()) //jezeli aktualna wartos jest to dodaj ja do kolejki i usunie ze zbioru wolnych zadan
			{
				kol_po_M1.push_back(rozw1.first.getN(i));
				Tsks_M1.erase(std::remove(Tsks_M1.begin(), Tsks_M1.end(), rozw1.first.getN(i)), Tsks_M1.end());
			}
		}
		kol_po_M2.clear();
		for (int i = ty_m2 + 1; i < rozw1.second.getSoT(); i++)
		{
			if (std::find(Tsks_M2.begin(), Tsks_M2.end(), rozw1.second.getN(i)) != Tsks_M2.end()) //jezeli aktualna wartos jest to dodaj ja do kolejki i usunie ze zbioru wolnych zadan
			{
				kol_po_M2.push_back(rozw1.second.getN(i));
				Tsks_M2.erase(std::remove(Tsks_M2.begin(), Tsks_M2.end(), rozw1.second.getN(i)), Tsks_M2.end());
			}
		}

		//MODYFIKOWANIE KOLEJKI, TAK ABY GDY SA OBIE OPERACJE W OBSZARZE ZAMIANY, TO op1 BYLO PIERWSZE
		//kol_M1
		//kol_M2

		int zadx = 0, zady = 0, zadpom = 0;
		zadx = kol_M1.back();		//za zadx podstawione jest zady
		kol_M1.pop_back();
		zady = kol_M1.front();		//za zady podstawione jest zadx
		kol_M1.pop_front();
		kol_M1.push_back(zady);		//zady wrzucone na koniec (czyli by�e zadx)
		kol_M1.push_front(zadx);	//zadx wrzucone na pocz�tek (czyli by�e zady)
		if (zadania[zadx-1].get_mach() == 2) {
			for (itM2 = kol_M2.begin(); itM2 != kol_M2.end(); itM2++) {
				//std::cout << *itM2 << "   ";
				if (*itM2 == zadx) {
					std::cout << std::endl << "YES_przerzucono op2 na pocz�tek "<<*itM2 << std::endl;
					for (int i = tx_m2 + 1;i < tx_m2 + zadania[zadx - 1].get_op1() + 1; i++) 
					{
						tmp.second.set(i, zadx);
					}
					tx_m1 = tx_m2 + zadania[zadx - 1].get_op1();
					if (tmp.first.getN(tx_m1) == -1)
					{
						while (tmp.first.getN(tx_m1 + 1) == -1) tx_m1++;
					}
					tx_m2 += zadania[zadx - 1].get_op1();
				}
			}
		}
		else
			std::cout << "Not this time1" << std::endl;

		if (zadania[zady - 1].get_mach() == 1) {
			for (itM2 = kol_M2.begin(); itM2 != kol_M2.end(); itM2++) 
			{
				//std::cout << *itM2 << "   ";
				if (*itM2 == zady) 
				{
					int pom;
					std::cout << std::endl << "YES_przerzucono op1 na koniec  " << *itM2<< std::endl;
					itM2_po = kol_po_M2.begin();
					pom = *itM2;
					kol_M2.erase(itM2);
					kol_po_M2.push_back(zady);
				}
			}
		}
		else
			std::cout << "Not this time2" << std::endl;

		std::cout << std::endl;
		tmp.first.test();
		std::cout << std::endl;
		std::cout << std::endl;
		tmp.second.test();


		return rozw1;
	}
	return rozw;
}
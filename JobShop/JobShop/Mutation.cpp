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
		Timeline *newTimeline = new Timeline(rozw.first.getSoT());
		std::pair<Timeline, Timeline> tmpbegin;
		tmpbegin.first = *newTimeline;
		tmpbegin.second = *newTimeline;
		std::pair<Timeline, Timeline> tmp;
		tmp.first = *newTimeline;
		tmp.second = *newTimeline;
		//		std::pair<Timeline, Timeline> tmpend;		//TO NIE MA SENSU
		std::list<int> kol_po_M1;			//kolejka zadañ po zamianie
		std::list<int> kol_po_M2;			//kolejka zadañ po zamianie
		std::list<int>::iterator itM2_po = kol_po_M2.begin();	
		std::list<int> kol_M1;				//kolejka zadañ w obszarze zamian
		std::list<int>::iterator itM1 = kol_M1.begin();
		std::list<int> kol_M2;				//kolejka zadañ w obszarze zamian
		std::list<int>::iterator itM2 = kol_M2.begin();

		int x = 0, y = 0, pom = 0;
		int xmach = 0, ymach = 0;
		int xzad = 0, yzad = 0;		//numery zadañ

									//LOSOWANIE ZADAÑ
		x = rand() % (N-1) + 2;				//które zadanie od pocz¹tku
		y = rand() % (N/5) + 1;				//które zadanie od pocz¹tku
		if (x + y > N) y = x - y;
		else y = x + y;
		if (x > y) { pom = x; x = y; y = pom; }
		for (int i = 0;i < rozw.first.getSoT();i++) {
			if (rozw.first.getN(i)== -1)
			{
				tmp.first.set(i, -1);
			}
		}


		std::cout << "Rozw " << std::endl;
		//rozw.first.test();
		std::cout << std::endl;
		//rozw.second.test();
		std::cout << "--------------------------------------" << std::endl;



		//NR ZADAN
		xzad = rozw1.first.get_nr_zad(x);
		yzad = rozw1.first.get_nr_zad(y);

		xmach = zadania[xzad-1].get_mach();		//na której maszynie
		ymach = zadania[yzad-1].get_mach();		//na której maszynie

												//CZASY ZADAN
		int tx_m1 = rozw1.first.whenDone(xzad);			//czas skoñczenia zadania przed x
		int ty_m1 = rozw1.first.whenDone(yzad);			//czas rozpoczecia zadania po zadaniu y 
		
		if (xmach == 1) tx_m1 = tx_m1 - zadania[xzad - 1].get_op1()-1;	//czas skoñczenia zadania przed x
		else
			tx_m1 = tx_m1 - zadania[xzad - 1].get_op2();

		int tx_m2 = rozw1.second.getTime_on_M2(tx_m1);	//czas skoñczenia zadania na M2 które jest pod M1
		int ty_m2 = rozw1.second.getTime_on_M2(ty_m1);
		//ZADANIA KTORE BYLY UZYTE	I VECTOR NIE UZYTYCH ZADAN	
		for (int i = 0; i < N; i++) { Tsks_M1[i] = (i + 1);Tsks_M2[i] = (i + 1);
		}

		usedTasks_M1 = rozw1.first.getUsdTasks(x-1);			//zadania które by³y u¿yte
		usedTasks_M2 = rozw1.second.getUsdTasks(x - 1);			//zadania które by³y u¿yte
		
		for (auto &i : usedTasks_M1)
		{
			Tsks_M1.erase(std::remove(Tsks_M1.begin(), Tsks_M1.end(), i), Tsks_M1.end()); //usuwanie wszystkich zadan kt juz wykonano
		}
		for (auto &i : usedTasks_M2)
		{
			Tsks_M2.erase(std::remove(Tsks_M2.begin(), Tsks_M2.end(), i), Tsks_M2.end()); //usuwanie wszystkich zadan kt juz wykonano
		}
		// KOPIOWANIE ROZW PRZED MIEJSCEM ZAMIANY

		for (int i = 0;i < tx_m1 ;i++) {
			tmp.first.set(i, rozw1.first.getN(i));
		}
		for (int i = 0;i < tx_m2 + 1;i++) {
			tmp.second.set(i, rozw1.second.getN(i));
		}

		for (int i = 0;i < tmp.first.getSoT()-1;i++) {
			if (tmp.first.getN(i)>0 && tmp.first.getN(i + 1) != tmp.first.getN(i)) {
				if (zadania[tmp.first.getN(i) - 1].get_mach() == 1) zadania[tmp.first.getN(i) - 1].set_done_op1(i);
			}
		}
		for (int i = 0;i < tmp.second.getSoT()-1;i++) {
			if (tmp.second.getN(i)>0 && tmp.second.getN(i + 1) != tmp.second.getN(i)) {
				if (zadania[tmp.second.getN(i) - 1].get_mach() == 2) zadania[tmp.second.getN(i) - 1].set_done_op1(i);
			}
		}

		std::cout <<"Po skopiowaniu poczatku "<< std::endl;
		//tmp.first.test();
		std::cout << std::endl;
		//tmp.second.test();
		std::cout << "--------------------------------------" << std::endl;
		
//NIEPOTRZEBNE I NIE DO KONCA DZIALA		
//		tmpbegin.first.copyTimeline(tx_m1);				//kopiowanie przodu rozw M1
//		tmpbegin.second.copyTimelineM2(tx_m2);			//kopiowanie przodu rozw M2


														// BEZ SENSU, BO ZADANIA MOGA SIE PRZESUNAC														
														//		tmpend.first.copyTimelineend(ty_m1 + 1);		//kopiowanie ty³u rozwi¹zania M1
														//		tmpend.second.copyTimelineendM2(ty_m1 + 1);		//kopiowanie tylu rozw M2


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
		

		int zadx = 0, zady = 0, zadpom = 0;
		zadx = kol_M1.back();		//za zadx podstawione jest zady
		kol_M1.pop_back();
		zady = kol_M1.front();		//za zady podstawione jest zadx
		kol_M1.pop_front();
		kol_M1.push_back(zady);		//zady wrzucone na koniec (czyli by³e zadx)
		kol_M1.push_front(zadx);	//zadx wrzucone na pocz¹tek (czyli by³e zady)
		if (zadania[zadx-1].get_mach() == 2) {
			for (itM2 = kol_M2.begin(); itM2 != kol_M2.end(); itM2++) {
				//std::cout << *itM2 << "   ";
				if (*itM2 == zadx) {
					std::cout << std::endl << "YES_przerzucono op2 na pocz¹tek "<<*itM2 << std::endl;
					kol_M2.erase(itM2);
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
					break;
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
					break;
				}
			}
		}
		else
			std::cout << "Not this time2" << std::endl;

		std::cout << "Po przerzuceniu zadan " << std::endl;
		//tmp.first.test();
		std::cout << std::endl;
		//tmp.second.test();
		std::cout << "--------------------------------------" << std::endl;

		int zad_m1 = 0, zad_m2 = 0;

		while (kol_M1.empty() == false || kol_M2.empty() == false) 
		{

			if (kol_M1.empty() == false) { zad_m1 = kol_M1.front();}
			if (kol_M2.empty() == false) { zad_m2 = kol_M2.front();}
//------------------------
			if (kol_M2.empty() == true) //robi zadania z kolejki M1
			{
				int dlg = zadania[zad_m1 - 1].get_op1();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m1 - 1].get_mach() == 2) dlg = zadania[zad_m1 - 1].get_op2();

				int id = zadania[zad_m1-1].get_rt();
				if (tx_m1 + 1 >  zadania[zad_m1-1].get_rt())id = tx_m1 + 1;
				if ((zadania[zad_m1 - 1].get_mach() == 2) && (id < zadania[zad_m1 - 1].get_done_op1())) id = zadania[zad_m1 - 1].get_done_op1();
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (tmp.first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
					if (dlg>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.first.getN(id + dlg - 1) != 0))id += dlg; // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + dlg - 1) && tmp.first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == dlg - 2) // jezeli same zera
						{
							empt = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id = c;
						}
					}
					else empt = 1;
				}
				int c = id;
				while (c < (id + dlg))
				{
					tmp.first.set(c, zadania[zad_m1 - 1].get_nr());
					c++;
				}
				if(zadania[zad_m1-1].get_mach()==1)  zadania[zad_m1 - 1].set_done_op1(id + dlg); //ustaw op1 na done
				kol_M1.pop_front();
			}
//------------------------------
			else if (kol_M1.empty() == true) //robi zadania z kolejki M2
			{
				int dlg2 = zadania[zad_m2 - 1].get_op2();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m2 - 1].get_mach() == 2) dlg2 = zadania[zad_m2 - 1].get_op1();
				int id2 = zadania[zad_m2 - 1].get_rt();
				if (tx_m2 + 1 >  zadania[zad_m2 - 1].get_rt())id2 = tx_m2 + 1;
				if ((zadania[zad_m2 - 1].get_mach() == 1) && (id2 < zadania[zad_m2 - 1].get_done_op1())) id2 = zadania[zad_m2 - 1].get_done_op1()+1;
				int empt2 = 0;
				while (empt2 == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c2 = 0;
					while (tmp.second.getN(id2) != 0)id2++; //przeszukiwany poczatek jest pusty
					if (dlg2>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.second.getN(id2 + dlg2 - 1) != 0))id2 += dlg2; // przeszukiwany koniec jest pusty
						for (c2 = id2 + 1; (c2 < id2 + dlg2 - 1) && tmp.second.getN(c2) == 0; c2++); //przejscie po zerach od poczatku do konca
						if ((c2 - (id2 + 1)) == dlg2 - 2) // jezeli same zera
						{
							empt2 = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id2 = c2;
						}
					}
					else empt2 = 1;
				}
				int c2 = id2;
				while (c2 < (id2 + dlg2))
				{
					tmp.second.set(c2, zadania[zad_m2 - 1].get_nr());
					c2++;
				}
				if (zadania[zad_m2 - 1].get_mach() == 2)  zadania[zad_m2 - 1].set_done_op1(id2 + dlg2); //ustaw op1 na done
				kol_M2.pop_front();
			}
//------------------------------------------------
			else if ((zadania[zad_m1 - 1].get_mach() == 1)&&(zadania[zad_m2-1].get_mach()==1)) //zadanie na M1 jest op1, a zadanie na M2 op2
			{
				int dlg = zadania[zad_m1 - 1].get_op1();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m1 - 1].get_mach() == 2) dlg = zadania[zad_m1 - 1].get_op2();

				int id = zadania[zad_m1 - 1].get_rt();
				if (tx_m1 + 1 >  zadania[zad_m1 - 1].get_rt())id = tx_m1 + 1;
				if ((zadania[zad_m1 - 1].get_mach() == 2) && (id < zadania[zad_m1 - 1].get_done_op1())) id = zadania[zad_m1 - 1].get_done_op1()+1;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (tmp.first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
					if (dlg>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.first.getN(id + dlg - 1) != 0))id += dlg; // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + dlg - 1) && tmp.first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == dlg - 2) // jezeli same zera
						{
							empt = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id = c;
						}
					}
					else empt = 1;
				}
				int c = id;
				while (c < (id + dlg))
				{
					tmp.first.set(c, zadania[zad_m1 - 1].get_nr());
					c++;
				}
				if (zadania[zad_m1 - 1].get_mach() == 1)  zadania[zad_m1 - 1].set_done_op1(id + dlg); //ustaw op1 na done
				kol_M1.pop_front();

				int dlg2 = zadania[zad_m2 - 1].get_op2();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m2 - 1].get_mach() == 2) dlg2 = zadania[zad_m2 - 1].get_op1();
				int id2 = zadania[zad_m2 - 1].get_rt();
				if (tx_m2 + 1 >  zadania[zad_m2 - 1].get_rt())id2 = tx_m2 + 1;
				if ((zadania[zad_m2 - 1].get_mach() == 1) && (id2 < zadania[zad_m2 - 1].get_done_op1())) id2 = zadania[zad_m2 - 1].get_done_op1()+1;
				int empt2 = 0;
				while (empt2 == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c2 = 0;
					while (tmp.second.getN(id2) != 0)id2++; //przeszukiwany poczatek jest pusty
					if (dlg2>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.second.getN(id2 + dlg2 - 1) != 0))id2 += dlg2; // przeszukiwany koniec jest pusty
						for (c2 = id2 + 1; (c2 < id2 + dlg2 - 1) && tmp.second.getN(c2) == 0; c2++); //przejscie po zerach od poczatku do konca
						if ((c2 - (id2 + 1)) == dlg2 - 2) // jezeli same zera
						{
							empt2 = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id2 = c2;
						}
					}
					else empt2 = 1;
				}
				int c2 = id2;
				while (c2 < (id2 + dlg2))
				{
					tmp.second.set(c2, zadania[zad_m2 - 1].get_nr());
					c2++;
				}
				if (zadania[zad_m2 - 1].get_mach() == 2)  zadania[zad_m2 - 1].set_done_op1(id2 + dlg2); //ustaw op1 na done
				kol_M2.pop_front();


			}
//------------------------------------------------------			
			else if ((zadania[zad_m1 - 1].get_mach() == 2) && (zadania[zad_m2 - 1].get_mach() == 2)) //zadanie na M2 jest op1, a zadanie na M1 op2
			{
				int dlg2 = zadania[zad_m2 - 1].get_op2();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m2 - 1].get_mach() == 2) dlg2 = zadania[zad_m2 - 1].get_op1();
				int id2 = zadania[zad_m2 - 1].get_rt();
				if (tx_m2 + 1 >  zadania[zad_m2 - 1].get_rt())id2 = tx_m2 + 1;
				if ((zadania[zad_m2 - 1].get_mach() == 1) && (id2 < zadania[zad_m2 - 1].get_done_op1())) id2 = zadania[zad_m2 - 1].get_done_op1()+1;
				int empt2 = 0;
				while (empt2 == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c2 = 0;
					while (tmp.second.getN(id2) != 0)id2++; //przeszukiwany poczatek jest pusty
					if (dlg2>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.second.getN(id2 + dlg2 - 1) != 0))id2 += dlg2; // przeszukiwany koniec jest pusty
						for (c2 = id2 + 1; (c2 < id2 + dlg2 - 1) && tmp.second.getN(c2) == 0; c2++); //przejscie po zerach od poczatku do konca
						if ((c2 - (id2 + 1)) == dlg2 - 2) // jezeli same zera
						{
							empt2 = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id2 = c2;
						}
					}
					else empt2 = 1;
				}
				int c2 = id2;
				while (c2 < (id2 + dlg2))
				{
					tmp.second.set(c2, zadania[zad_m2 - 1].get_nr());
					c2++;
				}
				if (zadania[zad_m2 - 1].get_mach() == 2)  zadania[zad_m2 - 1].set_done_op1(id2 + dlg2); //ustaw op1 na done
				kol_M2.pop_front();

			}
//------------------------------------------------------
			else if ((zadania[zad_m1 - 1].get_mach() == 1) && (zadania[zad_m2 - 1].get_mach() == 2)) //oba zadania s¹ op1
			{
				int dlg = zadania[zad_m1 - 1].get_op1();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m1 - 1].get_mach() == 2) dlg = zadania[zad_m1 - 1].get_op2();

				int id = zadania[zad_m1 - 1].get_rt();
				if (tx_m1 + 1 >  zadania[zad_m1 - 1].get_rt())id = tx_m1 + 1;
				if ((zadania[zad_m1 - 1].get_mach() == 2) && (id < zadania[zad_m1 - 1].get_done_op1())) id = zadania[zad_m1 - 1].get_done_op1()+1;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (tmp.first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
					if (dlg>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.first.getN(id + dlg - 1) != 0))id += dlg; // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + dlg - 1) && tmp.first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == dlg - 2) // jezeli same zera
						{
							empt = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id = c;
						}
					}
					else empt = 1;
				}
				int c = id;
				while (c < (id + dlg))
				{
					tmp.first.set(c, zadania[zad_m1 - 1].get_nr());
					c++;
				}
				if (zadania[zad_m1 - 1].get_mach() == 1)  zadania[zad_m1 - 1].set_done_op1(id + dlg); //ustaw op1 na done
				kol_M1.pop_front();
				
				int dlg2 = zadania[zad_m2 - 1].get_op2();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m2 - 1].get_mach() == 2) dlg2 = zadania[zad_m2 - 1].get_op1();
				int id2 = zadania[zad_m2 - 1].get_rt();
				if (tx_m2 + 1 >  zadania[zad_m2 - 1].get_rt())id2 = tx_m2 + 1;
				if ((zadania[zad_m2 - 1].get_mach() == 1) && (id2 < zadania[zad_m2 - 1].get_done_op1())) id2 = zadania[zad_m2 - 1].get_done_op1()+1;
				int empt2 = 0;
				while (empt2 == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c2 = 0;
					while (tmp.second.getN(id2) != 0)id2++; //przeszukiwany poczatek jest pusty
					if (dlg2>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.second.getN(id2 + dlg2 - 1) != 0))id2 += dlg2; // przeszukiwany koniec jest pusty
						for (c2 = id2 + 1; (c2 < id2 + dlg2 - 1) && tmp.second.getN(c2) == 0; c2++); //przejscie po zerach od poczatku do konca
						if ((c2 - (id2 + 1)) == dlg2 - 2) // jezeli same zera
						{
							empt2 = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id2 = c2;
						}
					}
					else empt2 = 1;
				}
				int c2 = id2;
				while (c2 < (id2 + dlg2))
				{
					tmp.second.set(c2, zadania[zad_m2 - 1].get_nr());
					c2++;
				}
				if (zadania[zad_m2 - 1].get_mach() == 2)  zadania[zad_m2 - 1].set_done_op1(id2 + dlg2); //ustaw op1 na done
				kol_M2.pop_front();
			}
			else if ((zadania[zad_m1 - 1].get_mach() == 2) && (zadania[zad_m2 - 1].get_mach() == 1)) //oba zadania s¹ op2
			{

				int dlg = zadania[zad_m1 - 1].get_op1();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m1 - 1].get_mach() == 2) dlg = zadania[zad_m1 - 1].get_op2();

				int id = zadania[zad_m1 - 1].get_rt();
				if (tx_m1 + 1 >  zadania[zad_m1 - 1].get_rt())id = tx_m1 + 1;
				if ((zadania[zad_m1 - 1].get_mach() == 2) && (id < zadania[zad_m1 - 1].get_done_op1())) id = zadania[zad_m1 - 1].get_done_op1()+1;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (tmp.first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
					if (dlg>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.first.getN(id + dlg - 1) != 0))id += dlg; // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + dlg - 1) && tmp.first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == dlg - 2) // jezeli same zera
						{
							empt = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id = c;
						}
					}
					else empt = 1;
				}
				int c = id;
				while (c < (id + dlg))
				{
					tmp.first.set(c, zadania[zad_m1 - 1].get_nr());
					c++;
				}
				if (zadania[zad_m1 - 1].get_mach() == 1)  zadania[zad_m1 - 1].set_done_op1(id + dlg); //ustaw op1 na done
				kol_M1.pop_front();

				int dlg2 = zadania[zad_m2 - 1].get_op2();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m2 - 1].get_mach() == 2) dlg2 = zadania[zad_m2 - 1].get_op1();
				int id2 = zadania[zad_m2 - 1].get_rt();
				if (tx_m2 + 1 >  zadania[zad_m2 - 1].get_rt())id2 = tx_m2 + 1;
				if ((zadania[zad_m2 - 1].get_mach() == 1) && (id2 < zadania[zad_m2 - 1].get_done_op1())) id2 = zadania[zad_m2 - 1].get_done_op1()+1;
				int empt2 = 0;
				while (empt2 == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c2 = 0;
					while (tmp.second.getN(id2) != 0)id2++; //przeszukiwany poczatek jest pusty
					if (dlg2>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.second.getN(id2 + dlg2 - 1) != 0))id2 += dlg2; // przeszukiwany koniec jest pusty
						for (c2 = id2 + 1; (c2 < id2 + dlg2 - 1) && tmp.second.getN(c2) == 0; c2++); //przejscie po zerach od poczatku do konca
						if ((c2 - (id2 + 1)) == dlg2 - 2) // jezeli same zera
						{
							empt2 = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id2 = c2;
						}
					}
					else empt2 = 1;
				}
				int c2 = id2;
				while (c2 < (id2 + dlg2))
				{
					tmp.second.set(c2, zadania[zad_m2 - 1].get_nr());
					c2++;
				}
				if (zadania[zad_m2 - 1].get_mach() == 2)  zadania[zad_m2 - 1].set_done_op1(id2 + dlg2); //ustaw op1 na done
				kol_M2.pop_front();
			}

		}

		std::cout << "Po pierwszej kolejce zadan " << std::endl;
		//tmp.first.test();
		std::cout << std::endl;
		//tmp.second.test();
		std::cout << "--------------------------------------" << std::endl;

		while (kol_po_M1.empty() == false || kol_po_M2.empty() == false)
		{

			if (kol_po_M1.empty() == false) { zad_m1 = kol_po_M1.front(); }
			if (kol_po_M2.empty() == false) { zad_m2 = kol_po_M2.front(); }
			//------------------------
			if (kol_po_M2.empty() == true) //robi zadania z kolejki M1
			{
				int dlg = zadania[zad_m1 - 1].get_op1();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m1 - 1].get_mach() == 2) dlg = zadania[zad_m1 - 1].get_op2();
				int id = zadania[zad_m1 - 1].get_rt();
				if (tx_m1 + 1 >  zadania[zad_m1 - 1].get_rt())id = tx_m1 + 1;
				if ((zadania[zad_m1 - 1].get_mach() == 2) && (id < zadania[zad_m1 - 1].get_done_op1())) id = zadania[zad_m1 - 1].get_done_op1()+1;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (tmp.first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
					if (dlg>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.first.getN(id + dlg - 1) != 0))id += dlg; // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + dlg - 1) && tmp.first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == dlg - 2) // jezeli same zera
						{
							empt = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id = c;
						}
					}
					else empt = 1;
				}
				int c = id;
				while (c < (id + dlg))
				{
					tmp.first.set(c, zadania[zad_m1 - 1].get_nr());
					c++;
				}
				if (zadania[zad_m1 - 1].get_mach() == 1)  zadania[zad_m1 - 1].set_done_op1(id + dlg); //ustaw op1 na done
				kol_po_M1.pop_front();
			}
			//------------------------------
			else if (kol_po_M1.empty() == true) //robi zadania z kolejki M2
			{
				int dlg2 = zadania[zad_m2 - 1].get_op2();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m2 - 1].get_mach() == 2) dlg2 = zadania[zad_m2 - 1].get_op1();
				int id2 = zadania[zad_m2 - 1].get_rt();
				if (tx_m2 + 1 >  zadania[zad_m2 - 1].get_rt())id2 = tx_m2 + 1;
				if ((zadania[zad_m2 - 1].get_mach() == 1) && (id2 < zadania[zad_m2 - 1].get_done_op1())) id2 = zadania[zad_m2 - 1].get_done_op1()+1;
				int empt2 = 0;
				while (empt2 == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c2 = 0;
					while (tmp.second.getN(id2) != 0)id2++; //przeszukiwany poczatek jest pusty
					if (dlg2>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.second.getN(id2 + dlg2 - 1) != 0))id2 += dlg2; // przeszukiwany koniec jest pusty
						for (c2 = id2 + 1; (c2 < id2 + dlg2 - 1) && tmp.second.getN(c2) == 0; c2++); //przejscie po zerach od poczatku do konca
						if ((c2 - (id2 + 1)) == dlg2 - 2) // jezeli same zera
						{
							empt2 = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id2 = c2;
						}
					}
					else empt2 = 1;
				}
				int c2 = id2;
				while (c2 < (id2 + zadania[zad_m2 - 1].get_op1()))
				{
					tmp.second.set(c2, zadania[zad_m2 - 1].get_nr());
					c2++;
				}
				if (zadania[zad_m2 - 1].get_mach() == 2)  zadania[zad_m2 - 1].set_done_op1(id2 + dlg2); //ustaw op1 na done
				kol_po_M2.pop_front();
			}
			//------------------------------------------------
			else if ((zadania[zad_m1 - 1].get_mach() == 1) && (zadania[zad_m2 - 1].get_mach() == 1)) //zadanie na M1 jest op1, a zadanie na M2 op2
			{

				int dlg = zadania[zad_m1 - 1].get_op1();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m1 - 1].get_mach() == 2) dlg = zadania[zad_m1 - 1].get_op2();
				int id = zadania[zad_m1 - 1].get_rt();
				if (tx_m1 + 1 >  zadania[zad_m1 - 1].get_rt())id = tx_m1 + 1;
				if ((zadania[zad_m1 - 1].get_mach() == 2) && (id < zadania[zad_m1 - 1].get_done_op1())) id = zadania[zad_m1 - 1].get_done_op1()+1;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (tmp.first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
					if (dlg>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.first.getN(id + dlg - 1) != 0))id += dlg; // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + dlg - 1) && tmp.first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == dlg - 2) // jezeli same zera
						{
							empt = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id = c;
						}
					}
					else empt = 1;
				}
				int c = id;
				while (c < (id + dlg))
				{
					tmp.first.set(c, zadania[zad_m1 - 1].get_nr());
					c++;
				}
				if (zadania[zad_m1 - 1].get_mach() == 1)  zadania[zad_m1 - 1].set_done_op1(id + dlg); //ustaw op1 na done
				kol_po_M1.pop_front();

				int dlg2 = zadania[zad_m2 - 1].get_op2();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m2 - 1].get_mach() == 2) dlg2 = zadania[zad_m2 - 1].get_op1();
				int id2 = zadania[zad_m2 - 1].get_rt();
				if (tx_m2 + 1 >  zadania[zad_m2 - 1].get_rt())id2 = tx_m2 + 1;
				if ((zadania[zad_m2 - 1].get_mach() == 1) && (id2 < zadania[zad_m2 - 1].get_done_op1())) id2 = zadania[zad_m2 - 1].get_done_op1()+1;
				int empt2 = 0;
				while (empt2 == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c2 = 0;
					while (tmp.second.getN(id2) != 0)id2++; //przeszukiwany poczatek jest pusty
					if (dlg2>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.second.getN(id2 + dlg2 - 1) != 0))id2 += dlg2; // przeszukiwany koniec jest pusty
						for (c2 = id2 + 1; (c2 < id2 + dlg2 - 1) && tmp.second.getN(c2) == 0; c2++); //przejscie po zerach od poczatku do konca
						if ((c2 - (id2 + 1)) == dlg2 - 2) // jezeli same zera
						{
							empt2 = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id2 = c2;
						}
					}
					else empt2 = 1;
				}
				int c2 = id2;
				while (c2 < (id2 + zadania[zad_m2 - 1].get_op1()))
				{
					tmp.second.set(c2, zadania[zad_m2 - 1].get_nr());
					c2++;
				}
				if (zadania[zad_m2 - 1].get_mach() == 2)  zadania[zad_m2 - 1].set_done_op1(id2 + dlg2); //ustaw op1 na done
				kol_po_M2.pop_front();


			}
			//------------------------------------------------------			
			else if ((zadania[zad_m1 - 1].get_mach() == 2) && (zadania[zad_m2 - 1].get_mach() == 2)) //zadanie na M2 jest op1, a zadanie na M1 op2
			{
				int dlg2 = zadania[zad_m2 - 1].get_op2();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m2 - 1].get_mach() == 2) dlg2 = zadania[zad_m2 - 1].get_op1();
				int id2 = zadania[zad_m2 - 1].get_rt();
				if (tx_m2 + 1 >  zadania[zad_m2 - 1].get_rt())id2 = tx_m2 + 1;
				if ((zadania[zad_m2 - 1].get_mach() == 1) && (id2 < zadania[zad_m2 - 1].get_done_op1())) id2 = zadania[zad_m2 - 1].get_done_op1()+1;
				int empt2 = 0;
				while (empt2 == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c2 = 0;
					while (tmp.second.getN(id2) != 0)id2++; //przeszukiwany poczatek jest pusty
					if (dlg2>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.second.getN(id2 + dlg2 - 1) != 0))id2 += dlg2; // przeszukiwany koniec jest pusty
						for (c2 = id2 + 1; (c2 < id2 + dlg2 - 1) && tmp.second.getN(c2) == 0; c2++); //przejscie po zerach od poczatku do konca
						if ((c2 - (id2 + 1)) == dlg2 - 2) // jezeli same zera
						{
							empt2 = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id2 = c2;
						}
					}
					else empt2 = 1;
				}
				int c2 = id2;
				while (c2 < (id2 + zadania[zad_m2 - 1].get_op1()))
				{
					tmp.second.set(c2, zadania[zad_m2 - 1].get_nr());
					c2++;
				}
				if (zadania[zad_m2 - 1].get_mach() == 2)  zadania[zad_m2 - 1].set_done_op1(id2 + dlg2); //ustaw op1 na done
				kol_po_M2.pop_front();

				int dlg = zadania[zad_m1 - 1].get_op1();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m1 - 1].get_mach() == 2) dlg = zadania[zad_m1 - 1].get_op2();
				int id = zadania[zad_m1 - 1].get_rt();
				if (tx_m1 + 1 >  zadania[zad_m1 - 1].get_rt())id = tx_m1 + 1;
				if ((zadania[zad_m1 - 1].get_mach() == 2) && (id < zadania[zad_m1 - 1].get_done_op1())) id = zadania[zad_m1 - 1].get_done_op1()+1;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (tmp.first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
					if (dlg>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.first.getN(id + dlg - 1) != 0))id += dlg; // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + dlg - 1) && tmp.first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == dlg - 2) // jezeli same zera
						{
							empt = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id = c;
						}
					}
					else empt = 1;
				}
				int c = id;
				while (c < (id + dlg))
				{
					tmp.first.set(c, zadania[zad_m1 - 1].get_nr());
					c++;
				}
				if (zadania[zad_m1 - 1].get_mach() == 1)  zadania[zad_m1 - 1].set_done_op1(id + dlg); //ustaw op1 na done
				kol_po_M1.pop_front();

			}
			//------------------------------------------------------
			else if ((zadania[zad_m1 - 1].get_mach() == 1) && (zadania[zad_m2 - 1].get_mach() == 2)) //oba zadania s¹ op1
			{
				int dlg = zadania[zad_m1 - 1].get_op1();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m1 - 1].get_mach() == 2) dlg = zadania[zad_m1 - 1].get_op2();
				int id = zadania[zad_m1 - 1].get_rt();
				if (tx_m1 + 1 >  zadania[zad_m1 - 1].get_rt())id = tx_m1 + 1;
				if ((zadania[zad_m1 - 1].get_mach() == 2) && (id < zadania[zad_m1 - 1].get_done_op1())) id = zadania[zad_m1 - 1].get_done_op1()+1;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (tmp.first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
					if (dlg>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.first.getN(id + dlg - 1) != 0))id += dlg; // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + dlg - 1) && tmp.first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == dlg - 2) // jezeli same zera
						{
							empt = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id = c;
						}
					}
					else empt = 1;
				}
				int c = id;
				while (c < (id + dlg))
				{
					tmp.first.set(c, zadania[zad_m1 - 1].get_nr());
					c++;
				}
				if (zadania[zad_m1 - 1].get_mach() == 1)  zadania[zad_m1 - 1].set_done_op1(id + dlg); //ustaw op1 na done
				kol_po_M1.pop_front();

				int dlg2 = zadania[zad_m2 - 1].get_op2();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m2 - 1].get_mach() == 2) dlg2 = zadania[zad_m2 - 1].get_op1();
				int id2 = zadania[zad_m2 - 1].get_rt();
				if (tx_m2 + 1 >  zadania[zad_m2 - 1].get_rt())id2 = tx_m2 + 1;
				if ((zadania[zad_m2 - 1].get_mach() == 1) && (id2 < zadania[zad_m2 - 1].get_done_op1())) id2 = zadania[zad_m2 - 1].get_done_op1()+1;
				int empt2 = 0;
				while (empt2 == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c2 = 0;
					while (tmp.second.getN(id2) != 0)id2++; //przeszukiwany poczatek jest pusty
					if (dlg2>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.second.getN(id2 + dlg2 - 1) != 0))id2 += dlg2; // przeszukiwany koniec jest pusty
						for (c2 = id2 + 1; (c2 < id2 + dlg2 - 1) && tmp.second.getN(c2) == 0; c2++); //przejscie po zerach od poczatku do konca
						if ((c2 - (id2 + 1)) == dlg2 - 2) // jezeli same zera
						{
							empt2 = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id2 = c2;
						}
					}
					else empt2 = 1;
				}
				int c2 = id2;
				while (c2 < (id2 + zadania[zad_m2 - 1].get_op1()))
				{
					tmp.second.set(c2, zadania[zad_m2 - 1].get_nr());
					c2++;
				}
				if (zadania[zad_m2 - 1].get_mach() == 2)  zadania[zad_m2 - 1].set_done_op1(id2 + dlg2); //ustaw op1 na done
				kol_po_M2.pop_front();
			}
			else if ((zadania[zad_m1 - 1].get_mach() == 2) && (zadania[zad_m2 - 1].get_mach() == 1)) //oba zadania s¹ op2
			{
				int dlg = zadania[zad_m1 - 1].get_op1();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m1 - 1].get_mach() == 2) dlg = zadania[zad_m1 - 1].get_op2();
				int id = zadania[zad_m1 - 1].get_rt();
				if (tx_m1 + 1 >  zadania[zad_m1 - 1].get_rt())id = tx_m1 + 1;
				if ((zadania[zad_m1 - 1].get_mach() == 2) && (id < zadania[zad_m1 - 1].get_done_op1())) id = zadania[zad_m1 - 1].get_done_op1()+1;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (tmp.first.getN(id) != 0)id++; //przeszukiwany poczatek jest pusty
					if (dlg>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.first.getN(id + dlg - 1) != 0))id += dlg; // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + dlg - 1) && tmp.first.getN(c) == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == dlg - 2) // jezeli same zera
						{
							empt = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id = c;
						}
					}
					else empt = 1;
				}
				int c = id;
				while (c < (id + dlg))
				{
					tmp.first.set(c, zadania[zad_m1 - 1].get_nr());
					c++;
				}
				if (zadania[zad_m1 - 1].get_mach() == 1)  zadania[zad_m1 - 1].set_done_op1(id + dlg); //ustaw op1 na done
				kol_po_M1.pop_front();

				int dlg2 = zadania[zad_m2 - 1].get_op2();;		// d³ugoœæ trwania zadania
				if (zadania[zad_m2 - 1].get_mach() == 2) dlg2 = zadania[zad_m2 - 1].get_op1();
				int id2 = zadania[zad_m2 - 1].get_rt();
				if (tx_m2 + 1 >  zadania[zad_m2 - 1].get_rt())id2 = tx_m2 + 1;
				if ((zadania[zad_m2 - 1].get_mach() == 1) && (id2 < zadania[zad_m2 - 1].get_done_op1())) id2 = zadania[zad_m2 - 1].get_done_op1()+1;
				int empt2 = 0;
				while (empt2 == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c2 = 0;
					while (tmp.second.getN(id2) != 0)id2++; //przeszukiwany poczatek jest pusty
					if (dlg2>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((tmp.second.getN(id2 + dlg2 - 1) != 0))id2 += dlg2; // przeszukiwany koniec jest pusty
						for (c2 = id2 + 1; (c2 < id2 + dlg2 - 1) && tmp.second.getN(c2) == 0; c2++); //przejscie po zerach od poczatku do konca
						if ((c2 - (id2 + 1)) == dlg2 - 2) // jezeli same zera
						{
							empt2 = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							id2 = c2;
						}
					}
					else empt2 = 1;
				}
				int c2 = id2;
				while (c2 < (id2 + zadania[zad_m2 - 1].get_op1()))
				{
					tmp.second.set(c2, zadania[zad_m2 - 1].get_nr());
					c2++;
				}
				if (zadania[zad_m2 - 1].get_mach() == 2)  zadania[zad_m2 - 1].set_done_op1(id2 + dlg2); //ustaw op1 na done
				kol_po_M2.pop_front();
			}

		}

		std::cout << "Jest GIT " << std::endl;
		//tmp.first.test();
		std::cout << std::endl;
		//tmp.second.test();
		std::cout << "--------------------------------------" << std::endl;

		return tmp;
	}
	return rozw;
}
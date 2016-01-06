// JobShop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	srand(time(NULL));

	int sizeOfPopulation = 30;
	int testNr = 4;
	int mut_chance = 100;

	std::string tasksFile = "tests/tasks.txt";
	std::string resFile = "tests/results.txt";
	tasksFile.insert(11, std::to_string(testNr));
	resFile.insert(13, std::to_string(testNr));
	//GENEROWANIE------------------------------------------------------------------
	/*
	

	int N = 100; //liczba operacji
	int minX = 20; //min czas trwania operacji
	int maxX = 50; //max czas trwania operacji
	int M = std::ceil(0.3*N);
	int maxMT = 10; //max czas trwania przerwy tecknicznej
	int TimeX = N*maxX + M*maxMT; //dlugosc osi czasu

	std::fstream fileOUT;
	fileOUT.open(tasksFile, std::fstream::out);

	fileOUT << "*** " << std::to_string(testNr) << " ***\n";

	fileOUT << N << "\n";


	std::cout << "Test\n";

	Generator* gen1 = new Generator(N);
	gen1->rdm(0, N - 1, minX, maxX);
	//gen1->test();

	Generator* gen2 = new Generator(N);
	gen2->rdm(0, N - 1, minX, maxX);
	//gen2->test();

	Readytime* rdy = new Readytime(N);
	rdy->rdm();
	//rdy->test();

	Timeline* TimeL1 = new Timeline(TimeX);
	TimeL1->maintenance(M, maxMT);
	//TimeL1->randomMaint(M, maxMT);
	//TimeL1->test();


	std::vector<Task> zadania;

	zadania.resize(N); //ilosc zadan

	for (int i = 0; i < N; i++)  //sprawdzanie czy dziala przypisywanie wartosci do tablicy zadan
	{
		zadania[i].set_params(i + 1, rdy->getN(i), gen1->getN(i), gen2->getN(i), 1);
	}
	

	for (int i = 0; i < N; i++)
	{
		std::cout << zadania[i].get_nr() << " " << zadania[i].get_op1() << " " << zadania[i].get_op2() << "\n\n";
		fileOUT
			<< zadania[i].get_op1() << "; "
			<< zadania[i].get_op2() << "; "
			<< ((i % 2) + 1) << "; "
			<< (2 - (i % 2)) << "; "
			<< zadania[i].get_rt() << ";\n";
	}

	TimeL1->CntMt();
	std::map<int, int> mappy;
	mappy = TimeL1->getMp();
	int licz = 1;

	for each (std::pair<int,int>pr in mappy)
	{
		fileOUT
			<< licz << "; "
			<< 1 << "; "
			<< pr.second << "; "
			<< pr.first << ";\n";
		licz++;
	}
	
	fileOUT << "*** EOF ***";
	fileOUT.close();
	//*/ //KONIEC GENEROWANIA --------------------------------------------------------------------------------------------

	//ROCK 'N ROLL -------------------------------------------------------------------------------------------------------/*

	std::fstream fileIN;
	std::fstream fileOUT;


	fileIN.open(tasksFile, std::fstream::in);
	fileOUT.open(resFile, std::fstream::out);

	std::string tmpStr;
	std::getline(fileIN, tmpStr);

	int N;
	fileIN >> N;

	std::vector<Task> zadania;
	zadania.resize(N); //ilosc zadan

	std::string zad;

	int pom[5];

	for (int i = 0; i < N; i++) //czytawanie
	{
		for (int k = 0; k < 5; k++)
		{
			fileIN >> zad;
			zad.pop_back();
			pom[k] = std::stoi(zad, 0, 10);
		}
		zadania[i].set_params(i + 1, pom[4], pom[0], pom[1], pom[2]);
		
	}
	std::cout << "Pobrano dane z pliku\n";
	//for (int i = 0; i < N; i++) 
	//{
	//	std::cout 
	//		<< zadania[i].get_nr() << " " 
	//		<< zadania[i].get_op1() << " " 
	//		<< zadania[i].get_op2() << " "
	//		<< zadania[i].get_rt() << "\n";
	//}


	Timeline* TimeL = new Timeline(10000);
	while (!fileIN.eof() && zad[0]!='*')
	{
		for (int k = 0; k < 4; k++)
		{
			fileIN >> zad;
			if (zad[0] == '*')break;
			zad.pop_back();
			pom[k] = std::stoi(zad, 0, 10);
		}
		if (zad[0] != '*')
		{
			TimeL->SetMt(pom[3], pom[2]);
		}
	}
	//std::pair<Timeline, Timeline> rozw = TimeL->Instancja(zadania, N); //tworzenie rozwiazania
	//std::pair<Timeline, Timeline> rozw1 = TimeL->Instancja(zadania, N); 

	//if (rozw.first.cmp(rozw.first)) std::cout << "\ndziala porownywanie!!!!\n\n";

	//if (rozw1.first.cmp(rozw.first)) std::cout << "\nTO SAMO!!!!\n\n";
	
	//tworzenie populacji------------------------------------------------------------------------
 	std::vector<std::pair<Timeline, Timeline>> populacja;
	populacja.resize(sizeOfPopulation);
	int a = 0;
	std::pair<Timeline, Timeline> tmpSol;
	
	//TimeL->test();
	//populacja[0] = TimeL->Instancja123(zadania);
	//populacja[0].first.test();
	//populacja[0].second.test();
	
	//if (TimeL->compareTsks(populacja[0].first, -1))std::cout << "jest to samo\n\n";

	while (a < sizeOfPopulation)
	{

		tmpSol = TimeL->Instancja123(zadania);
		if (TimeL->compareTsks(tmpSol.first, -1) && tmpSol.first.checkMach(zadania,1) && tmpSol.second.checkMach(zadania,2) && tmpSol.first.FirstIsFirst(tmpSol.second,zadania,1)==-1)
		{
  			populacja[a] = tmpSol;
			a++;
		}
		else
		{
			if (!(TimeL->compareTsks(tmpSol.first, -1)))
			{
				std::cout << "WRONG MAINT! " << std::endl;
			}
			if (!tmpSol.first.checkMach(zadania, 1) || !tmpSol.second.checkMach(zadania, 2))
			{
				std::cout << "blad z zadaniami" << std::endl;
			}
			if (tmpSol.first.FirstIsFirst(tmpSol.second, zadania, 1)>0)
			{
				std::cout << "op2 nie jest za op1 w zadaniu " << tmpSol.first.FirstIsFirst(tmpSol.second, zadania, 1);
				std::cout << "\t";
			}
			std::cout << "AGAIN for inst " << a << std::endl;			
		}
			
	}

	int iq = 0;
	int iw = 0;
	bool dupl = false;
	for (auto &q : populacja) //sprawdzanie duplikatow w populacji
	{
		iw = 0;
		for (auto &w : populacja) {
			if (iq != iw &&q.first.cmp(w.first) && q.second.cmp(w.second))
			{
				dupl = true;
				std::cout << iq << " i " << iw << "\tpopulacja FeelsBadMan\n\n";
				//break;
			}
			iw++;
		}
		iq++;
	}
	std::vector<std::pair<Timeline, Timeline>> najlepszyWynik = wybierz(populacja, 1);
	int przed = najlepszyWynik[0].first.TargetFnctn(najlepszyWynik[0]);
	
	//std::pair<Timeline, Timeline> proba;
	//std::vector<int> tab1 = {0,0,-1,0,0,2,2,1,0,-1};
	//proba.first.copy(tab1);
	//tab1 = {1,1,0,2,0,0,0,0,0,0};
	//proba.second.copy(tab1);

	//proba.first.test();
	//proba.second.test();
	//if (!proba.first.FirstIsFirst(proba.second, zadania, 1))
	//{
	//	std::cout << "dziala\n";
	//}
	//

	//for (auto &i : populacja)
	//{
	//	if (!i.first.FirstIsFirst(i.second, zadania, 1))
	//	{
	//		std::cout << std::endl;
	//	}
	//}

// TU BYL BREAKPOINT
//-------------------------------
	populacja = crossing(populacja, 80, zadania, 3*sizeOfPopulation);
	
	for (auto &i : populacja)
	{
		if (!i.first.FirstIsFirst(i.second, zadania, 1))
		{
			std::cout << std::endl;
		}
	}


	populacja = wybierz(populacja, 10);

	//zapisanie rozwiazania
	fileOUT << "*** " << std::to_string(testNr) << " ***\n";

	//najlepszy wynik
	najlepszyWynik = wybierz(populacja, 1);

	int po = najlepszyWynik[0].first.TargetFnctn(najlepszyWynik[0]);

	std::cout << std::endl;
	najlepszyWynik[0].first.test();
	std::cout << najlepszyWynik[0].first.TargetFnctn1(najlepszyWynik[0]) << std::endl;
	najlepszyWynik[0].second.test();
	std::cout << najlepszyWynik[0].second.TargetFnctn2(najlepszyWynik[0]) << std::endl;
	std::cout << najlepszyWynik[0].first.TargetFnctn(najlepszyWynik[0]) << std::endl;
	//rozw.first.test();
	//rozw.second.test();
	//PrintableResult M1 = rozw.first.resOut(zadania, 1);
	PrintableResult M1 = najlepszyWynik[0].first.resOut(zadania, 1);
	//PrintableResult M2 = rozw.second.resOut(zadania, 2);
	PrintableResult M2 = najlepszyWynik[0].first.resOut(zadania, 2);
//	int wartFnCelu1 = populacja[0].first.TargetFnctn1(rozw);
//	int wartFnCelu2 = populacja[0].first.TargetFnctn2(rozw);
//	int wartFnCelu = populacja[0].first.TargetFnctn(rozw);
//	std::cout << wartFnCelu1 << std::endl;
//	std::cout << wartFnCelu2 << std::endl;
//	std::cout << wartFnCelu1 + wartFnCelu2 << std::endl;
//	std::cout << wartFnCelu << std::endl;
	int wartFnCelu=0;

	int mut_done = 0; //zrobione mutacje
	int pop_size = populacja.size();
	std::vector<std::pair<Timeline, Timeline>> populacja_mut;
	std::pair<std::pair<Timeline, Timeline>, int> instan;
	
	//	for (int i = 0; i < pop_size && mut_done < std::ceil(populacja.size() * (mut_chance / 100)); i++) {
	//	instan = Mutacja(populacja[i], zadania, N, mut_chance);
	//		//wartFnCelu = populacja[0].first.TargetFnctn(populacja[0]);
	//		if (instan.second == 1) {
	//		mut_done++;
	//		std::cout << std::endl << "Mutacja " << mut_done << std::endl;
	//		populacja_mut.insert(populacja_mut.end(), instan.first);	
	//	}
	//		//std::cout << wartFnCelu << std::endl;
	//}

	fileOUT << po <<", "<<przed << std::endl;
	fileOUT << "M1: " << M1.getS() << std::endl;
	fileOUT << "M2: " << M2.getS() << std::endl;
	fileOUT << M1.getM() << std::endl;
	fileOUT << M2.getM() << std::endl;
	fileOUT << M1.getI() << std::endl;
	fileOUT << M2.getI() << std::endl;
	//TimeL->test();
	fileOUT << "*** EOF ***";
	fileOUT.close();
	fileIN.close();
	//*/ //KONIEC FEELSBADMAN ------------------------------------------------------------


	return 0;
}


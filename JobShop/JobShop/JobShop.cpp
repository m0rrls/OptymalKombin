// JobShop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	int testNr = 2;

	std::string tasksFile = "tests/tasks.txt";
	std::string resFile = "tests/results.txt";
	tasksFile.insert(11, std::to_string(testNr));
	resFile.insert(13, std::to_string(testNr));
	//GENEROWANIE------------------------------------------------------------------
	/*
	srand(time(0));

	int N = 200; //liczba operacji
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
	gen1->test();

	Generator* gen2 = new Generator(N);
	gen2->rdm(0, N-1, minX, maxX);
	gen2->test();

	Readytime* rdy = new Readytime(N);
	rdy->rdm();
	rdy->test();

	Timeline* TimeL1 = new Timeline(TimeX);
	TimeL1->maintenance(M, maxMT);
	TimeL1->test();


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
	 */ //KONIEC GENEROWANIA ---------------------------------------------------------

	//ROCK 'N ROLL --------------------------------------------------------------------/*

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


	Timeline* TimeL = new Timeline(N*N);
	while (!fileIN.eof() && zad[0]!='*')
	{
		for (int k = 0; k < 4; k++)
		{
			fileIN >> zad;
			if (zad[0] == '*')break;
			zad.pop_back();
			pom[k] = std::stoi(zad, 0, 10);
		}
		if(zad[0]!='*') TimeL->SetMt(pom[3], pom[2]);
	}
	std::pair<Timeline, Timeline> rozw = TimeL->Instancja(zadania, N); //tworzenie rozwiazania



	//zapisanie rozwiazania
	fileOUT << "*** " << std::to_string(testNr) << " ***\n";

	//rozw.first.test();
	//rozw.second.test();
	PrintableResult M1 = rozw.first.resOut(zadania, 1);
	PrintableResult M2 = rozw.second.resOut(zadania, 2);
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


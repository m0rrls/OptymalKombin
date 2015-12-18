// JobShop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{

	//GENEROWANIE------------------------------------------------------------------
	/*
	srand(time(0));

	int N = 20; //liczba operacji
	int minX = 2; //min czas trwania operacji
	int maxX = 5; //max czas trwania operacji
	int M = std::ceil(0.3*N);
	int maxMT = 2; //max czas trwania przerwy tecknicznej
	int TimeX = N*maxX + M*maxMT; //dlugosc osi czasu

	std::fstream fileOUT;
	fileOUT.open("tasks1.txt", std::fstream::out);
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
	fileIN.open("tasks1.txt", std::fstream::in);
	fileOUT.open("results1.txt", std::fstream::out);

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

	for (int i = 0; i < N; i++)
	{
		std::cout 
			<< zadania[i].get_nr() << " " 
			<< zadania[i].get_op1() << " " 
			<< zadania[i].get_op2() << " "
			<< zadania[i].get_rt() << "\n";
	}


	Timeline* TimeL = new Timeline(N*N/2);
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

	TimeL->test();
	fileOUT.close();
	fileIN.close();
	// */ //KONIEC FEELSBADMAN -------------------------------------------------------------

 	return 0;
}


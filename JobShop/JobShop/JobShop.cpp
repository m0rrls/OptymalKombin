// JobShop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	int N = 10;
	int Z = 100; //max czas trwania operacji

	std::cout << "Test\n";
	
	Generator* gen1 = new Generator(N);
	gen1->rdm(0, N - 1, Z);
	gen1->test();

	Generator* gen2 = new Generator(N);
	gen2->rdm(0, N - 1, Z);
	gen2->test();

	Readytime* rdy = new Readytime(N);
	rdy->rdm();
	rdy->test();

	Timeline* TimeL1 = new Timeline(30);
	TimeL1->maintenance(N, 0.2, 4);
	TimeL1->test();

	Timeline* TimeL2 = new Timeline(30);
	TimeL2->maintenance(N, 0.4, 2);
	TimeL2->test();

	std::vector<Task> zadania;

	zadania.resize(N); //ilosc zadan

	for (int i = 0; i < N; i++)  //sprawdzanie czy dziala przypisywanie wartosci do tablicy zadan
	{
		zadania[i].set_params(i + 1, rdy->getN(i), gen1->getN(i), gen2->getN(i));
	}

	for (int i = 0; i < N; i++)
	{
		std::cout << zadania[i].get_nr() << " " << zadania[i].get_op1() << " " << zadania[i].get_op2() << "\n\n";
	}

	
	return 0;
}


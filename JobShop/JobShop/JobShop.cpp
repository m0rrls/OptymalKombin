// JobShop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	int N = 10;

	std::cout << "Test\n";
	Task* op1 = new Task(1, 0, 3, 3);
	std::cout << op1->get_nr() << " " << op1->get_op1() << " " << op1->get_op2() << "\n\n";
	Generator* gen = new Generator(N);
	gen->rdm(0, N-1, 2);
	gen->test();

	Readytime* rdy = new Readytime(N);
	rdy->rdm(0, N - 1);
	rdy->test();

	Timeline* TimeL = new Timeline(30);
	TimeL->maintenance(N, 0.3, 3);
	TimeL->test();

	std::vector<Task> zadania;

	zadania.resize(N); //ilosc zadan

	for (int i = 0; i < N; i++)  //sprawdzanie czy dziala przypisywanie wartosci do tablicy zadan
	{
		zadania[i].set_params(i + 1, 0, gen->getN(i), 3-gen->getN(i));
	}

	for (int i = 0; i < N; i++)
	{
		std::cout << zadania[i].get_nr() << " " << zadania[i].get_op1() << " " << zadania[i].get_op2() << "\n\n";
	}



	return 0;
}


#include "stdafx.h"
#include "Timeline.h"
#include <vector>




void Timeline::maintenance(int i, int maxL) //dodaje przerwy techniczne dla N zadan w stosunku kN do liczby zadan
{													//gdzie  podana jest maksymalna dlugosc przerwy, jezeli jest
	//srand(time(0));								//skonfigurowane by wiêcej przer by³o na poczatku a szansa na przerwe malala
	//int i = ceil(N * kN);							//wraz z numerem pozycji przerwy w tablicy
	int j = 0;
	while (j < i)
	{
		int start = rand() % tab.size();
		int len = rand() % maxL + 1;
		int alrdyTkn = 0;
		int k = start - 1;
		if (start == 0) k = start;
		int l = start + len;
		if (l >= tab.size()) l = tab.size() - 1;
		int pom = k;

		while (!alrdyTkn && k < l+1)
		{
			if (tab[k] == -1)
			{
				alrdyTkn = 1;
			}
			k++;
		}
		int h = rand()%100 + 1;
		int g = std::ceil(100*start / (double)(tab.size()));
		if (!alrdyTkn && h < (100 - g))
		{
			for (pom; pom < l; pom++)
				tab[pom] = -1;
			j++;
		}
	}
}

void Timeline::randomMaint(int i, int maxL)
{
	int j = 0;
	while (j < i)
	{
		int start = rand() % tab.size();
		int len = rand() % maxL + 1;
		int alrdyTkn = 0;
		int k = start - 1;
		if (start == 0) k = start;
		int l = start + len;
		if (l >= tab.size()) l = tab.size() - 1;
		int pom = k;

		while (!alrdyTkn && k < l + 1)
		{
			if (tab[k] == -1)
			{
				alrdyTkn = 1;
			}
			k++;
		}

		for (pom; pom < l; pom++)
			tab[pom] = -1;
		j++;

	}
}

void Timeline::CntMt()
{
	int i = 0;
	while (i < tab.size())
	{
		int j = 0;
		if (tab[i] == -1)
		{
			int k = i;
			while (tab[i++] == -1)
			{
				j++;
			}
			mp.insert(std::pair<int, int>(k, j));
		}
		else
			i++;
	}
}

void Timeline::SetMt(int when, int howL)
{
	int tmp = when;
	for (int i=when; i < (when + howL); i++)
	{
		tab[i] = -1;
	}
}

std::map<int, int> Timeline::getMp()
{
	return mp;
}

std::pair<Timeline, Timeline> Timeline::Instancja(std::vector<Task> zadania, int N)
{
	std::pair<Timeline, Timeline> rozw;
	std::vector<int> alrdyUsd;
	alrdyUsd.resize(2*N);
	for (int i = 0; i < (2*N); i++)alrdyUsd[i] = 0;
	int done = 0;
	rozw.first.tab = tab;
	rozw.second.tab.resize(tab.size());
	for (int i = 0; i < tab.size(); i++)rozw.second.tab[i] = 0;
	while (!done)
	{
		int zad = rand() % N;
		if (!alrdyUsd[zad]) //jezeli op1 nie zostala uzyta
		{
			if (zadania[zad].get_mach() == 1) //jezeli op1 jest na PIERWSZEJ maszynie
			{
				int id = zadania[zad].get_rt();
				int k = id;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (rozw.first.tab[id] != 0)id++; //przeszukiwany poczatek jest pusty
					if (zadania[zad].get_op1()>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((rozw.first.tab[id + zadania[zad].get_op1() - 1] != 0))id += zadania[zad].get_op1(); // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + zadania[zad].get_op1() - 1) && rozw.first.tab[c] == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == zadania[zad].get_op1() - 2) // jezeli same zera
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
				while (c < (id + zadania[zad].get_op1()))
				{
					rozw.first.tab[c] = zadania[zad].get_nr();
					c++;
				}
				zadania[zad].set_done_op1(id + zadania[zad].get_op1()); //ustaw op1 na done
			}
			else //jezeli op1 jest na DRUGIEJ
			{
				int id = zadania[zad].get_rt();
				int k = id;
				int empt=0;
				while (empt==0) //szukaj miejsca gdzie mozna umiescic zadanie
				{
					
					int c = 0;
					while (rozw.second.tab[id] != 0)id++; //przeszukiwany poczatek jest pusty
					if (zadania[zad].get_op1()>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((rozw.second.tab[id + zadania[zad].get_op1() - 1]) != 0)id += zadania[zad].get_op1(); // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + zadania[zad].get_op1() - 1) && rozw.second.tab[c] == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == zadania[zad].get_op1() - 2) // jezeli same zera
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
				while (c < (id + zadania[zad].get_op1()))
				{
					rozw.second.tab[c] = zadania[zad].get_nr();
					c++;
				}
				zadania[zad].set_done_op1(id+zadania[zad].get_op1()); //ustaw op1 na done
			}
			alrdyUsd[zad] = 1;
		}
		else if (!alrdyUsd[zad + N] && zadania[zad].get_done_op1()>0) //jezeli op1 zostala zrobiona a op2 nie
		{
			if (zadania[zad].get_mach() == 1) //jezeli op2 jest na DRUGIEJ maszynie (op1 jest na PIERWSZEJ)
			{
				int id = zadania[zad].get_done_op1();
				int k = id;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (rozw.second.tab[id] != 0)id++; //przeszukiwany poczatek jest pusty
					if (zadania[zad].get_op2()>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((rozw.second.tab[id + zadania[zad].get_op2() - 1] != 0))id += zadania[zad].get_op2(); // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + zadania[zad].get_op2() - 1) && rozw.second.tab[c] == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == zadania[zad].get_op2() - 2) // jezeli same zera
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
				while (c < (id + zadania[zad].get_op2())) //umiesc zadanie na osi czasu
				{
					rozw.second.tab[c] = zadania[zad].get_nr();
					c++;
				}
			}
			else //jezeli op2 jest na PIERWSZEJ maszynie (op1 jest na DRUGIEJ)
			{
				int id = zadania[zad].get_done_op1();
				int k = id;
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (rozw.first.tab[id] != 0)id++; //przeszukiwany poczatek jest pusty
					if (zadania[zad].get_op2()>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((rozw.first.tab[id + zadania[zad].get_op2() - 1] != 0))id += zadania[zad].get_op2(); // przeszukiwany koniec jest pusty
						for (c = id + 1; (c < id + zadania[zad].get_op2() - 1) && rozw.first.tab[c] == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (id + 1)) == zadania[zad].get_op2() - 2) // jezeli same zera
						{
							empt = 1;
						}
						else
						{
							id = c;
						}
					}
					else empt = 1;
				}
				int c = id;
				while (c < (id + zadania[zad].get_op2()))
				{
					rozw.first.tab[c] = zadania[zad].get_nr();
					c++;
				}
			}
			alrdyUsd[zad + N] = 1; //ustaw op2 na done
		}
		//spr czy uzyto juz wszystkich zadan
		int check = 0;
		for each (int i in alrdyUsd)
		{
			check += i;
		}
		if (check == 2*N)
		{
			done = 1;
		}

	}
	return rozw;
}


PrintableResult Timeline::resOut(std::vector<Task> zadania, int machine)
{
	std::string res = "";
	int i = 0;
	int sumM = 0;
	int sumI = 0;
	int idM = 1;
	int idI = 1;
	while (i < tab.size())
	{
		if (tab[i] == -1) //jezeli przerwa tech.
		{
			res += ("maint" + std::to_string(idM++) + "_M" + std::to_string(machine) + ", ");
			res += (std::to_string(i) + ", ");
			int j = 0;
			while (i < tab.size() && tab[i] == -1)
			{
				j++;
				i++;
			}
			sumM += j;
			res += (std::to_string(j) + "; ");
		}
		else if (tab[i] == 0) //jezeli nic nie jest robione
		{
			res += ("idle" + std::to_string(idI++) + "_M" + std::to_string(machine) + ", ");
			res += (std::to_string(i) + ", ");
			int j = 0;
			while (i < tab.size() && tab[i] == 0)
			{
				j++;
				i++;
			}
			sumI += j;
			res += (std::to_string(j) + "; ");
		}
		else
		{
			res += "op";
			if (zadania[tab[i] - 1].get_mach() == machine) //jezeli jest to maszyna na kt jest wykonywana op1
			{
				res += "1_";
			}
			else
			{
				res += "2_";
			}
			res += (std::to_string(tab[i]) + ", " + std::to_string(i) + ", ");
			int j = 0;
			int pom = tab[i];
			while (i < tab.size() && tab[i] == pom)
			{
				j++;
				i++;
			}
			res += (std::to_string(j) + "; ");
		}
	}
	PrintableResult* out = new PrintableResult();

	out->setALL(idM-1, sumM, idI-1, sumI);
	out->res(res);
	return *out;
}

Timeline::~Timeline()
{
}


int Timeline::TargetFnctn1(std::pair<Timeline, Timeline> rozw)
{
	int wart = 0;
	int i = 0;
	while (i < rozw.first.tab.size() - 1) {
		if ((rozw.first.tab[i] > 0) && (rozw.first.tab[i + 1] != rozw.first.tab[i])) {
			wart += i;
		}
		i++;
	}
	return wart;
}

int Timeline::TargetFnctn2(std::pair<Timeline, Timeline> rozw)
{
	int wart = 0;
	int i = 0;
	while (i < rozw.second.tab.size() - 1) {
		if ((rozw.second.tab[i] > 0) && (rozw.second.tab[i + 1] != rozw.second.tab[i])) {
			wart += i;
		}
		i++;
	}
	return wart;
}


int Timeline::TargetFnctn(std::pair<Timeline, Timeline> rozw)
{
	int wart = 0;
	int i = 0;
	while (i < rozw.second.tab.size() - 1) {
		if ((rozw.second.tab[i] > 0) && (rozw.second.tab[i + 1] != rozw.second.tab[i])) {
			wart += i;
		}
		i++;
	}
	i = 0;
	while (i < rozw.first.tab.size() - 1) {
		if ((rozw.first.tab[i] > 0) && (rozw.first.tab[i + 1] != rozw.first.tab[i])) {
			wart += i;
		}
		i++;
	}
	return wart;
}

std::pair<Timeline, Timeline> Timeline::Mutacja(std::pair<Timeline, Timeline> rozw, std::vector<Task> zadania, int N)
{
	srand(time(0));

	if (rand() % 101 <= MutChance) {

		std::vector <int> tabM1;
		std::vector <int> tabM2;
		std::pair<Timeline, Timeline> rozw1=rozw;
		std::vector<Task> zadaniaMut = zadania;
		rozw1.first.tab.resize(N*2*N);
		rozw1.second.tab.resize(N*2*N);
		tabM1.resize(N);
		tabM2.resize(N);
		int i = 0;
		int j = 0;

		for (i = 0 ; i < N ; i++) {
			tabM1[i] = 0;
			tabM2[i] = 0;
			zadaniaMut[i].set_done_op1(false);
		}
/*		for (i = 0; i < N; i++) 
		{
			std::cout << zadaniaMut[i].get_done_op1();
		}
*/
		i = 0;
		j = 0;
//wypisywanie
/*		while (i < rozw1.second.tab.size() - 1) {
			std::cout << rozw1.first.tab[i] << "\t" << rozw1.second.tab[i] << std::endl;
			i++;
		}
		i = 0;
*/		
//pêtle spisuj¹ wartoœci i zeruj¹ tablice
		while (i < rozw1.first.tab.size() - 1) {
			//std::cout << rozw1.first.tab[i] << " ";
			if ((rozw1.first.tab[i] > 0) && (rozw1.first.tab[i + 1] != rozw1.first.tab[i])) {
				tabM1[j] = rozw1.first.tab[i];
				j++;
			}
			if (rozw1.first.tab[i] != -1) rozw1.first.tab[i] = 0;
			i++;
		}
		std::cout << std::endl;
		j = 0;
		i = 0;
		while (i < rozw1.second.tab.size() - 1) {
			//std::cout << rozw1.second.tab[i]<<" ";
			if ((rozw1.second.tab[i] > 0) && (rozw1.second.tab[i + 1] != rozw1.second.tab[i])) {
				tabM2[j] = rozw1.second.tab[i];
				j++;
			}
			if (rozw1.second.tab[i] != -1) rozw1.second.tab[i] = 0;
			i++;
		}
		i = 0;
// wypisywanie wartoœci
/*		
	while (i < rozw1.second.tab.size() - 1) {
	std::cout << rozw1.first.tab[i] << "\t" << rozw1.second.tab[i] << std::endl;
	i++;
	}
	i=0;
*/
	std::cout << std::endl;
/**/
	for (i = 0;i < N;i++) {
		std::cout << tabM1[i] << " ";
	}
	std::cout << std::endl;
	for (i = 0;i < N;i++) {
		std::cout << tabM2[i] << " ";
	}
	std::cout << std::endl;
//
//ZAMIANA ZADAN
//
/**/
	int x = 0, y = 0, pom = 0;
	x = rand() % N;
	y = rand() % N; 
	while(x==y) y = rand() % N;
	pom = tabM1[x];
	tabM1[x] = tabM1[y];
	tabM1[y] = pom;
	std::cout << tabM1[x] << " " << tabM1[y] << std::endl;
	for (i = 0;i < N;i++) {
		if (tabM2[i] == tabM1[x]) {
			x = i;
			break;
		}
	}
	for (i = 0;i < N;i++) {
		if (tabM2[i] == tabM1[y]) {
			y = i;
			break;
		}
	}
	pom = tabM2[x];
	tabM2[x] = tabM2[y];
	tabM2[y] = pom;

	std::cout << std::endl<<"-------"<< std::endl;
	for (i = 0;i < N;i++) {
		std::cout << tabM1[i] << " ";
	}
	std::cout << std::endl;
	for (i = 0;i < N;i++) {
		std::cout << tabM2[i] << " ";
	}
	std::cout << std::endl;

	int done1 = 0, done2 = 0, xi=0, xj=0, r1=0, r2=0;
	i = 0;
	j = 0;
	xi = 0;
	xj = 0;
	int zad1;
	int zad2;
	while ((!done1) || (!done2))
	{
		r1 = 0;
		r2 = 0;
		if(!done1) zad1 = tabM1[i];
		if(!done2) zad2 = tabM2[j];

		if (!done1) {
			if ((zadaniaMut[zad1-1].get_mach() == 1) || ( (zadaniaMut[zad1-1].get_mach() == 2) && (zadaniaMut[zad1-1].get_done_op1() != false)))
			{
//				/*wywalic*/	std::cout << "Mach1\n";
				r1 = 1;
				if ((zadaniaMut[zad1-1].get_mach() == 2) && (xi < zadaniaMut[zad1-1].get_done_op1())) xi = zadaniaMut[zad1-1].get_done_op1(); // ustawia xi na koniec czasu wykonywania op_1
				if (xi < zadaniaMut[zad1-1].get_rt()) xi = zadaniaMut[zad1-1].get_rt(); //sprawdza aby nie wstwaiæ przed rt
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (rozw1.first.tab[xi] != 0)xi++; //przeszukiwany poczatek jest pusty
					if (zadaniaMut[zad1-1].get_op1() > 1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((rozw1.first.tab[xi + zadaniaMut[zad1-1].get_op1() - 1] != 0))xi += zadaniaMut[zad1-1].get_op1(); // przeszukiwany koniec jest pusty
						for (c = xi + 1; (c < xi + zadaniaMut[zad1-1].get_op1() - 1) && rozw1.first.tab[c] == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (xi + 1)) == zadaniaMut[zad1-1].get_op1() - 2) // jezeli same zera
						{
							empt = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							xi = c;
						}
					}
					else empt = 1;
				}
				int c = xi;
				while (c < (xi + zadaniaMut[zad1-1].get_op1()))
				{
					rozw1.first.tab[c] = zadaniaMut[zad1-1].get_nr();
					c++;
				}
				zadaniaMut[zad1-1].set_done_op1(xi + zadaniaMut[zad1-1].get_op1()); //ustaw op1 na done
				xi = c;
				i++;
				if (i == N) done1 = 1;
			}
		}
		if (!done2) 
		{
			if ((zadaniaMut[zad2-1].get_mach() == 2) || ((zadaniaMut[zad2-1].get_mach() == 1) && (zadaniaMut[zad1-1].get_done_op1() != false)))
			{
//				/*wywalic*/	std::cout << "Mach2\n";
				r2 = 1;
				if ((zadaniaMut[zad2-1].get_mach() == 1) && (xj < zadaniaMut[zad2-1].get_done_op1())) xj = zadaniaMut[zad2-1].get_done_op1(); // ustawia xi na koniec czasu wykonywania op_1
				if (xj < zadaniaMut[zad2-1].get_rt()) xj = zadaniaMut[zad2-1].get_rt(); //sprawdza aby nie wstwaiæ przed rt
				int empt = 0;
				while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
				{

					int c = 0;
					while (rozw1.second.tab[xj] != 0)xj++; //przeszukiwany poczatek jest pusty
					if (zadaniaMut[zad2-1].get_op1() > 1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
					{
						while ((rozw1.second.tab[xj + zadaniaMut[zad2-1].get_op1() - 1] != 0))xj += zadaniaMut[zad2-1].get_op1(); // przeszukiwany koniec jest pusty
						for (c = xj + 1; (c < xj + zadaniaMut[zad2-1].get_op1() - 1) && rozw1.second.tab[c] == 0; c++); //przejscie po zerach od poczatku do konca
						if ((c - (xj + 1)) == zadaniaMut[zad2-1].get_op1() - 2) // jezeli same zera
						{
							empt = 1;
						}
						else //jezeli nie to przesun do miejsca gdzie jest ostatnie zero
						{
							xj = c;
						}
					}
					else empt = 1;
				}
				int c = xj;
				while (c < (xj + zadaniaMut[zad2-1].get_op1()))
				{
					rozw1.second.tab[c] = zadaniaMut[zad2-1].get_nr();
					c++;
				}
				zadaniaMut[zad2-1].set_done_op1(xj + zadaniaMut[zad2-1].get_op1()); //ustaw op1 na done
				xj = c;
				j++;
				if (j == N) done2 = 1;
			}
		}
/**/
		if ((r1 == 0) && (r2 == 0)) {
			std::cout << "Nieudana  " <<i<<"  "<<j<<"   "<< std::endl;
			return rozw;
		}
	}

//wypisywanie	
/*	
	i = 0;	
	while (i < rozw1.second.tab.size() - 1) {
		std::cout << rozw1.first.tab[i] << "\t" << rozw1.second.tab[i] << std::endl;
		i++;
	}
	i = 0;
*/
	std::cout << "Udana" << std::endl;
	
	return rozw1;
	}
	return rozw;
}
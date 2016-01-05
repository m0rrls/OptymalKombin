#include "stdafx.h"
#include "Timeline.h"





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

		while (!alrdyTkn && k < l + 1)
		{
			if (tab[k] == -1)
			{
				alrdyTkn = 1;
			}
			k++;
		}
		int h = rand() % 100 + 1;
		int g = std::ceil(100 * start / (double)(tab.size()));
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
	if ((when + howL) > tab.size())
	{
		tab.resize(when + howL + 1);
	}
	for (int i = when; i < (when + howL); i++)
	{
		tab[i] = -1;
	}
}

std::map<int, int> Timeline::getMp()
{
	return mp;
}

std::pair<Timeline, Timeline> Timeline::Instancja(std::vector<Task> z1, int N)
{
	bool dNc = false;
	std::vector<Task> zadania = z1;
	std::pair<Timeline, Timeline> rozw;
	std::vector<int> alrdyUsd;

	while (!dNc)
	{
		alrdyUsd.clear();
		alrdyUsd.resize(2 * N);
		for (int i = 0; i < (2 * N); i++)alrdyUsd[i] = 0;
		int done = 0;
		rozw.first.tab.clear();
		rozw.first.tab = tab;
		rozw.second.tab.clear();
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
					int empt = 0;
					while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
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
					zadania[zad].set_done_op1(id + zadania[zad].get_op1()); //ustaw op1 na done
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
						if (zadania[zad].get_op2() > 1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
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
			if (check == 2 * N)
			{
				done = 1;
			}

		}
		if (rozw.first.checkMach(z1, 1) &&
			rozw.second.checkMach(z1, 2)
			&& rozw.first.FirstIsFirst(rozw.second, zadania, 1)
			)
		{
			dNc = true;
		}
	}
	return rozw;
}

bool Timeline::checkMach(std::vector<Task> zadania, int mach)
{
	int i = 0;
	bool checkd = true;
	std::vector<int> us;
	us.resize(zadania.size());
	for (auto &j : us)
	{
		j = 0;
	}
	while (i < tab.size())
	{
		if (tab[i]>0)
		{
			int pom = tab[i];
			int j = 0;
			while (tab[i] == pom)
			{
				i++;
				j++;
			}
			if (zadania[pom - 1].get_mach() == mach)
			{
				if (j != zadania[pom - 1].get_op1())
				{
					//std::cout << "WRONG LENGTH OF " << pom << " ON M" << mach << std::endl;
					return false;
				}
				else
					us[pom - 1] = 1;
			}
			else
			{
				if (j != zadania[pom - 1].get_op2())
				{
					//std::cout << "WRONG LENGTH OF " << pom << " ON M" << mach << std::endl;
					return false;
				}
				else
					us[pom - 1] = 1;
			}
		}
		else
			i++;
	}
	for (int j = 0; j < us.size(); j++)
	{
		if (us[j] == 0)
		{
			//std::cout << "NOT USED " << (j + 1) << std::endl;
			checkd = false;
		}
	}
	return checkd;
}

void Timeline::napraw(int pkt, std::vector<Task> zadania, int mach)
{
	int id = pkt;
	std::vector<int> Tsks;	//zadania do umieszczenia
	Tsks.resize(zadania.size());

	for (int i = 0; i < zadania.size(); i++)
	{
		Tsks[i] = i;
	}
	int x = 0;
	while (x < pkt) //usuwanie zadan przed pkt do naprawy, bo ich nie ruszamy
	{
		if (tab[x] > 0)
		{
			int pom = tab[x];
			//std::cout << pom << " ";
			//Tsks[pom - 1] = 0;
			Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), pom - 1), Tsks.end());
			while (tab[x] == pom)x++;
		}
		else
			x++;
	}
	//Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), 0), Tsks.end());
	/*
	std::cout << "\n\n";
	for (int i = 0; i < Tsks.size(); i++)
	{
	std::cout << Tsks[i]+1 << " ";
	}
	std::cout << "\n";
	*/

	while (!Tsks.empty())
	{
		int i = rand() % Tsks.size();
		int j = Tsks[i];
		if (zadania[j].get_mach() == mach) //jezeli na ten maszynie op1
		{
			if (id < zadania[j].get_rt()) id = zadania[j].get_rt(); //wykonaj dopiero po rdytime
			int k = id;
			int empt = 0;
			while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
			{

				int c = 0;
				while (tab[id] != 0)id++; //przeszukiwany poczatek jest pusty
				if (zadania[j].get_op1() > 1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
				{
					while ((tab[id + zadania[j].get_op1() - 1] != 0))id += zadania[j].get_op1(); // przeszukiwany koniec jest pusty
					for (c = id + 1; (c < id + zadania[j].get_op1() - 1) && tab[c] == 0; c++); //przejscie po zerach od poczatku do konca
					if ((c - (id + 1)) == zadania[j].get_op1() - 2) // jezeli same zera
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
			while (c < (id + zadania[j].get_op1()))
			{
				tab[c] = zadania[j].get_nr();
				c++;
			}
			zadania[j].set_done_op1(id + zadania[j].get_op1()); //ustaw op1 na done

		}
		else //jezeli na tej maszynie ma sie wykonac op2
		{
			//if (id < tmp[i1].second.whenDone(i + 1)) id = tmp[i1].second.whenDone(i + 1);
			int k = id;
			int empt = 0;
			while (empt == 0) //szukaj miejsca gdzie mozna umiescic zadanie
			{

				int c = 0;
				while (tab[id] != 0)id++; //przeszukiwany poczatek jest pusty
				if (zadania[j].get_op2()>1) //jezeli zadanie jest dluzsze niz 1 jednostka czasu to sprawd czy wejdzie
				{
					while ((tab[id + zadania[j].get_op2() - 1] != 0))id += zadania[j].get_op2(); // przeszukiwany koniec jest pusty
					for (c = id + 1; (c < id + zadania[j].get_op2() - 1) && tab[c] == 0; c++); //przejscie po zerach od poczatku do konca
					if ((c - (id + 1)) == zadania[j].get_op2() - 2) // jezeli same zera
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
			while (c < (id + zadania[j].get_op2())) //umiesc zadanie na osi czasu
			{
				tab[c] = zadania[j].get_nr();
				c++;
			}
		}
		Tsks.erase(std::remove(Tsks.begin(), Tsks.end(), j), Tsks.end());
	}
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

	out->setALL(idM - 1, sumM, idI - 1, sumI);
	out->res(res);
	return *out;
}

Timeline::~Timeline()
{
}


std::vector<Timeline> Timeline::copyTimeline(int dokiedy)
{
	std::vector<Timeline> rozw;
	rozw.resize(dokiedy + 1);
	for (int i = 0; i <= dokiedy;i++) rozw[i] = 0;

	for (int i = 0; i <= dokiedy;i++) {
		rozw[i] = tab[i];
	}

	return rozw;
}

std::vector<Timeline> Timeline::copyTimelineend(int odkiedy)
{
	std::vector<Timeline> rozw;
	int rozm = tab.size() - odkiedy + 1;
	rozw.resize(rozm);
	for (int i = 0; i <= rozm;i++) rozw[i] = 0;
	int j = 0;
	for (int i = odkiedy; i < tab.size(); i++) {
		rozw[j] = tab[i];
		j++;
	}

	return rozw;
}

std::vector<Timeline> Timeline::copyTimelineM2(int dokiedy)
{
	std::vector<Timeline> rozw;
	rozw.resize(dokiedy + 50);
	for (int i = 0; i <= dokiedy + 50; i++) rozw[i] = 0;
	int i = dokiedy;
	if (tab[dokiedy] == 0) {}
	else
	{
		while (tab[i] == tab[dokiedy]) { i++; }
	}
	for (int j = 0; j <= i; j++) {
		rozw[j] = tab[j];
	}
	rozw.resize(i + 1);
	return rozw;
}

std::vector<Timeline> Timeline::copyTimelineendM2(int odkiedy)
{
	std::vector<Timeline> rozw;
	int rozm = tab.size() - odkiedy + 1;
	rozw.resize(rozm);
	int k = odkiedy;
	if (tab[k] == 0) {}
	else
	{
		while (tab[k] == tab[odkiedy])k++;
	}
	for (int i = 0; i <= rozm;i++) rozw[i] = 0;
	int j = 0;
	for (int i = k; i < tab.size(); i++) {
		rozw[j] = tab[i];
		j++;
	}
	rozw.resize(tab.size() - k + 1);

	return rozw;
}

void Timeline::wyswietl(int od, int dok)
{
	int i = od;
	for (i; i < dok; i++) {
		std::cout << tab[i] << " ";
	}


}

int Timeline::get_nr_zad(int N)
{
	int zad;
	int i = 0;
	int j = 0;
	while (j != N)
	{
		if (tab[i]>0)
		{
			j++;
			zad = tab[i];
			while (tab[i] == zad)i++;
		}
		else
		{
			i++;
		}
	}

	return zad;
}

int Timeline::getTime_on_M2(int N)
{
	int i = N;
	if (tab[N] == 0) return N;
	else {
		while (tab[i] == tab[N]) {
			i++;
		}
	}

	return i-1;
}

std::vector<int> Timeline::getUsdTasks(int N)
{
	int i = 0;
	int j = 0;
	std::vector<int> vec;
	vec.clear();
	while (j < N && i < tab.size())
	{
		if (tab[i] > 0)
		{
			vec.insert(vec.end(), tab[i]);
			j++;
			int pom = tab[i];
			while (tab[i] == pom)i++;
		}
		else i++;
	}
	return vec;
}

int Timeline::getIAftrNTsks(int N)
{
	int i = 0;
	int j = 0;
	while (j < N && i < tab.size())
	{
		if (tab[i] > 0)
		{
			j++;
			int pom = tab[i];
			while (tab[i] == pom)i++;
		}
		else i++;
	}
	return i;
}

int Timeline::whenDone(int N)
{
	for (int i = 0; i < tab.size(); i++)
	{
		if (tab[i] == N)
		{
			while (tab[i] == N)
			{
				i++;
			}
			return i;
		}
	}
	return -1;
}

bool Timeline::compareTsks(Timeline solution, int N)
{
	for (int i = 0; i < tab.size(); i++)
	{
		if (tab[i] == N)
		{
			if (tab[i] != solution.getN(i)) return false;
		}
	}
	return true;
}

void Timeline::getOp1Ends(std::vector<Task> zadania, int mach)
{

	int i = 0;
	while (i < tab.size())
	{
		if (tab[i]>0) //jezeli zadanie
		{
			int pom = tab[i];
			if (zadania[pom - 1].get_mach() == mach)//i ma op1 na tej maszynie
			{
				while (tab[i] == pom)i++;
				zadania[pom - 1].set_done_op1(i);
			}
			else
				i++;
		}
		else
			i++;
	}
}

bool Timeline::FirstIsFirst(Timeline otherOne, std::vector<Task> zadania, int mach)
{

	//wszystko jest git jak op1 jest zawsze przed op2, wszystkie zadania sš na timelin'ie i nie naruszono przerw

	this->getOp1Ends(zadania, mach);
	otherOne.getOp1Ends(zadania, 3 - mach);
	int i = 0;
	while (i < zadania.size())
	{
		int j = zadania[i].get_done_op1();
		if (zadania[i].get_mach() == mach) //jezeli op1 jest na tej maszynie
		{
			while (otherOne.getN(j) != zadania[i].get_nr() && j < otherOne.getSoT())
			{
				j++;
			}
			if (zadania[i].get_op2() == 1 && otherOne.whenDone(i + 1) == j + 1)
			{
				i++;
			}
			else if ((otherOne.whenDone(i + 1) - j) != zadania[i].get_op2())
			{
				return false;
			}
			else
				i++;
		}
		else //jezeli na drugiej
		{
			while (j < tab.size() && tab[j] != zadania[i].get_nr())
			{
				j++;
			}
			if (zadania[i].get_op2() == 1 && this->whenDone(i + 1) == j + 1)
			{
				i++;
			}
			else if ((this->whenDone(i + 1) - j) != zadania[i].get_op2())
			{
				std::cout << "WHEN DONE dla " << i << " : " << this->whenDone(i + 1);
				return false;
			}
			else
				i++;
		}
	}
	return true;
}

std::pair<Timeline, Timeline> Timeline::Instancja123(std::vector<Task> zadania)
{
	std::vector<Task> zad = zadania;

	std::pair<Timeline, Timeline> rozw;
	rozw.first.tab = tab;
	rozw.second.tab.clear();
	rozw.second.tab.resize(tab.size());

	int N = zad.size();
	bool done = false;

	std::vector<int> uzyte;
	uzyte.resize(2 * N);
	for (auto &i : uzyte)
	{
		i = 0;
	}
	for (auto &i : zad)
	{
		i.reset();
	}

	std::pair<std::vector<int>, std::vector<int>> Tsks;
	Tsks.first.clear();
	Tsks.second.clear();




	std::pair<int, int> id; //wskaznik
	id.first = 0;
	id.second = 0;


	int space = 0;


	while (!done)
	{
		Tsks.first.clear();
		Tsks.second.clear();
		space = 0;

		//std::cout << "M1: " << id.first<< "\tM2: " << id.second;
		//obliczenie wolnego miejsca na maszynach
		int tmp123 = id.first;
		while (tmp123 < rozw.first.getSoT() && rozw.first.getN(tmp123++) == 0)
		{
			space++;
		}

		for (int i = 0; i < zad.size(); i++)//dodanie do tablic operacje ktore mozemy wykonac
		{
			if (!uzyte[i] && zad[i].get_mach() == 1 && zad[i].get_op1() <= space && zad[i].get_rt() <= id.first) //op1 dla M1
				Tsks.first.insert(Tsks.first.begin(), i);
			if (!uzyte[i] && zad[i].get_mach() == 2 && zad[i].get_rt() <= id.second) //op1 dla M2
				Tsks.second.insert(Tsks.second.begin(), i);
			if (!uzyte[N + i] && zad[i].get_mach() == 1 && zad[i].get_done_op1() != 0 && zad[i].get_done_op1() <= id.second) //op2 dla M2
				Tsks.second.insert(Tsks.second.begin(), i);
			if (!uzyte[N + i] && zad[i].get_mach() == 2 && zad[i].get_done_op1() != 0 && zad[i].get_op2() <= space && zad[i].get_done_op1() <= id.first) //op2 dla M1
				Tsks.first.insert(Tsks.first.begin(), i);
		}

		int mach = rand() % 2 + 1;
		//std::cout << "\tlosM: " << mach << std::endl;
		int i;
		if (mach == 1)
		{
			if (!Tsks.first.empty()) //wylos M1
			{
				int los = rand() % Tsks.first.size();
				int x = Tsks.first[los];
				Task z = zad[x];
				//bool empty = false;
				//while (!empty)
				//{
				//	while (rozw.first.getN(id.first) != 0)id.first++;
				//	i = id.first;
				//	if (z.get_mach() == 1)
				//	{
				//		if (z.get_op1() == 1)
				//		{
				//			//Tsks.first.erase(Tsks.first.begin() + los); //uzyto juz
				//			empty = true;
				//		}
				//		else
				//		{
				//			int czas = z.get_op1();
				//			while (czas > 0 && rozw.first.getN(i++) == 0)
				//			{
				//				czas--;
				//			}
				//			if (czas == 0) empty = true;
				//			else id.first = i;
				//		}
				//	}
				//	else if (z.get_mach() == 2 && uzyte[x])
				//	{
				//		if (z.get_op2() == 1)
				//		{
				//			empty = true;
				//		}
				//		else
				//		{
				//			int czas = z.get_op2();
				//			while (czas > 0 && rozw.first.getN(i++) == 0)
				//			{
				//				czas--;
				//			}
				//			if (czas == 0) empty = true;
				//			else id.first = i;
				//		}
				//	}
				//}//jest wolne miejsce
				int pom = 0;
				if (z.get_mach() == 1)
				{
					pom = z.get_op1();
					zad[x].set_done_op1(id.first + pom);
					uzyte[x] = 1;
					Tsks.first.erase(Tsks.first.begin() + los);
				}
				else if (z.get_mach() == 2)
				{
					pom = z.get_op2();
					uzyte[N + x] = 1;
					Tsks.first.erase(Tsks.first.begin() + los);
				}
				for (int j = id.first; j < id.first + pom; j++)
				{
					rozw.first.set(j, z.get_nr());
				}
				id.first += pom;
			}
			else
			{
				id.first++;
			}
			//if (Tsks.second.empty())id.second++;
		}
		if (mach == 2) //wylos M2
		{
			if (!Tsks.second.empty())
			{
				int los = rand() % Tsks.second.size();
				int x = Tsks.second[los];
				Task z = zad[x];
				//bool empty = false;
				//while (!empty)
				//{
				//	while (id.second < rozw.second.getSoT() && rozw.second.getN(id.second) != 0)id.second++;
				//	i = id.second;
				//	if (z.get_mach() == 2)
				//	{
				//		if (z.get_op1() == 1)
				//		{
				//			empty = true;
				//		}
				//		else
				//		{
				//			int czas = z.get_op1();
				//			while (czas > 0 && rozw.second.getN(i++) == 0)
				//			{
				//				czas--;
				//			}
				//			if (czas == 0) empty = true;
				//			else id.second = i;
				//		}
				//	}
				//	else if (z.get_mach() == 1 && uzyte[x])
				//	{
				//		if (z.get_op2() == 1)
				//		{
				//			empty = true;
				//		}
				//		else
				//		{
				//			int czas = z.get_op2();
				//			while (czas > 0 && rozw.second.getN(i++) == 0)
				//			{
				//				czas--;
				//			}
				//			if (czas == 0) empty = true;
				//			else id.second = i;
				//		}
				//	}
				//}//jest wolne miejsce
				int pom = 0;
				if (z.get_mach() == 2)
				{
					pom = z.get_op1();
					zad[x].set_done_op1(id.first + pom);
					uzyte[x] = 1;
					Tsks.second.erase(Tsks.second.begin() + los);
				}
				else if (z.get_mach() == 1)
				{
					pom = z.get_op2();
					uzyte[N + x] = 1;
					Tsks.second.erase(Tsks.second.begin() + los);
				}
				for (int j = id.second; j < id.second + pom; j++)
				{
					rozw.second.set(j, z.get_nr());
				}
				id.second += pom;
			}
			else
			{
				id.second++;
			}
			//if (Tsks.first.empty())id.first++;
		}
		int uzytL = 0;
		for (auto &i : uzyte) uzytL += i;
		if (Tsks.first.empty() && Tsks.second.empty() && uzytL == uzyte.size()) done = true;
	}
	return rozw;
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

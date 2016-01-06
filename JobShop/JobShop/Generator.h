#pragma once
#include <vector>

class Generator
{
public:
	Generator();
	Generator(int l);
	~Generator();
	//generowanie w tablicy w przedziale [start;end] liczb z zakresu [k;j]
	virtual void rdm(int start, int end, int k, int j);
	void test();
	int getN(int a);
	int getSoT();
	
	//porownywanie: jezeli sa takie same to true
	bool cmp(Generator a);
	
	//usuwanie wartosci z tab
	void del(int start, int end); //podano koniec
	void del(int start); //usun od pkt do konca

	//dodawanie wart do tab
	void add(int val);

	//dodawanie wektora na koncu
	void add(std::vector<int> vec);

	//ustawienie komorki na wartosc
	void set(int it, int val);

	void copy(std::vector<int> t);

protected:
	std::vector<int> tab;
};


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
protected:
	std::vector<int> tab;
};


#pragma once
#include <vector>

class Generator
{
public:
	Generator(int l);
	~Generator();
	virtual void rdm(int start, int end, int k);
	void test();
	int getN(int a);
protected:
	std::vector<int> tab;
};


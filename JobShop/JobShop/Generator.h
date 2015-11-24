#pragma once
#include <vector>

class Generator
{
public:
	Generator(int l);
	~Generator();
	void rdm(int start, int end, int k);
private:
	int len;
	std::vector<int> tab;
};


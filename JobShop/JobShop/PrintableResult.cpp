#include "stdafx.h"
#include "PrintableResult.h"


PrintableResult::PrintableResult()
{
}


PrintableResult::~PrintableResult()
{
}

std::string PrintableResult::getS()
{
	return ciag;
}

void PrintableResult::res(std::string addon)
{
	ciag += addon;
}

void PrintableResult::setALL(int a, int b, int c, int d)
{
	maint = a;
	sumOfM = b;
	idle = c;
	sumOfI = d;
}

std::string PrintableResult::getM()
{
	std::string tmp =
		std::to_string(maint) + ", " + std::to_string(sumOfM);
	return tmp;
}

std::string PrintableResult::getI()
{
	std::string tmp =
		std::to_string(idle) + ", " + std::to_string(sumOfI);
	return tmp;
}

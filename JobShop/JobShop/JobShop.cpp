// JobShop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main()
{
	std::cout << "Test\n";
	Task* op1 = new Task(1, 3, 3);
	std::cout << op1->get_nr() << " " << op1->get_op1() << " " << op1->get_op2() << "\n";

	
    return 0;
}


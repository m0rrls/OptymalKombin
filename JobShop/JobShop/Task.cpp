#include "stdafx.h"
#include "Task.h"


Task::Task(int a, int b, int c)
{
	x = a;
	y1 = b;
	y2 = c;
}

int Task::get_nr() 
{
	return x;
}

int Task::get_op1()
{
	return y1;
}

int Task::get_op2()
{
	return y2;
}

Task::~Task()
{
}

#include "stdafx.h"
#include "Task.h"


Task::Task()
{
	x = -1;
	rt = -1;
	y1 = -1;
	y2 = -1;
}

Task::Task(int a, int b, int c, int d)
{
	x = a;
	rt = b;
	y1 = c;
	y2 = d;
	done_op1 = false;
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

int Task::get_rt()
{
	return rt;
}

bool Task::get_done_op1()
{
	return done_op1;
}

void Task::set_done_op1()
{
	done_op1 = true;
}

void Task::set_params(int a, int b, int c, int d)
{
	x = a;
	rt = b;
	y1 = c;
	y2 = d;
}


Task::~Task()
{
}

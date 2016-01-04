#include "stdafx.h"
#include "Task.h"


Task::Task()
{
	x = -1;
	rt = -1;
	y1 = -1;
	y2 = -1;
	done_op1 = 0;
}

Task::Task(int a, int b, int c, int d, int e)
{
	x = a;
	rt = b;
	y1 = c;
	y2 = d;
	mach = e;
	done_op1 = 0;
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

int Task::get_mach()
{
	return mach;
}

int Task::get_done_op1()
{
	return done_op1;
}

void Task::set_done_op1(int r)
{
	done_op1 = r;
}

void Task::set_params(int a, int b, int c, int d, int e)
{
	x = a;
	rt = b;
	y1 = c;
	y2 = d;
	mach = e;
}

void Task::reset()
{
	done_op1 = 0;
}


Task::~Task()
{
}

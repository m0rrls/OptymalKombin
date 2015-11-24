#pragma once
class Task
{
public:
	Task(int a, int b, int c);
	~Task();
	int get_nr();
	int get_op1();
	int get_op2();
private:
	int x; //numer zadania
	int y1, y2; //czas trwania operacji 1 i 2
};


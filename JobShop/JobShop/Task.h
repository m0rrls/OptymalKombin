#pragma once
class Task
{
public:
	Task();
	Task(int a, int b, int c, int d, int e);
	~Task();
	int get_nr();
	int get_op1();
	int get_op2();
	int get_rt();
	bool get_done_op1();
	void set_done_op1();
	void set_params(int a, int b, int c, int d, int e);
private:
	int x; //numer zadania
	int y1, y2; //czas trwania operacji 1 i 2
	int rt; //readytime
	bool mach; //na ktorej maszynie 
	bool done_op1; //czy zrobiono pierwsza operacjei mozna ropoczac druga
};


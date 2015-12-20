#pragma once
class PrintableResult
{
public:
	PrintableResult();
	~PrintableResult();
	std::string getS();
	void res(std::string addon);
	void setALL(int a, int b, int c, int d);
	std::string getM();
	std::string getI();
private:
	std::string ciag="";
	int maint;
	int sumOfM;
	int idle;
	int sumOfI;
};


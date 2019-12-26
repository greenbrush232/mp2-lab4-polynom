#pragma once
#include <iostream>
using namespace std;

struct Monom
{
	int Power;
	double Coeff;
	
	Monom* Next;

	Monom()
	{
		Coeff = 0;
		Power = 0;
		Next = nullptr;
	}
	Monom(double coeff, int power);
	Monom(double coeff, int power, Monom* next);
	Monom(const Monom& tm);

	Monom& operator=(const Monom& tm)
	{
		Coeff = tm.Coeff;
		Power = tm.Power;
		return *this;
	}

	bool operator==(const Monom& tm);
			
	

	int operator<(const Monom& tm)
	{
		return Power < tm.Power;
	}
};

class Polynom
{
private:
	Monom* head;
	int size;
public:
	Polynom();
	Polynom(const Polynom& polynom);
	~Polynom();

	int getSize() { return size; }
	void clear();
	void insert(Monom monom);
	void insert(double coef, int pow);

	void merge(const Polynom& polynom);
	void pop_front();
	void push_front(Monom monom);
	void push_back(Monom monom);
	void del(Monom monom);
	bool find(int pow);

	int Calculate(int x);
	Polynom operator+(const Polynom& right) const;
	Polynom operator-(Polynom& right);
	Polynom operator*(const Polynom& right);
	Polynom operator*(const double& val) const;
	const Polynom& operator = (const Polynom& right);

	friend ostream& operator << (ostream& os, const Polynom& object);
};


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
	Monom* head; // заголовок
	int size; // длинна списка

public:
	Polynom();// конструктор
	Polynom(const Polynom& polynom); // конструктор копирования
	~Polynom();// деструктор

	int getSize() { return size; }// к-во звеньев
	void clear();// очистить список
	void insert(Monom monom); // вставка в список
	void insert(double coef, int pow);

	void merge(const Polynom& polynom); // добавление полинома к другому
	void pop_front();// удаление элемента из списка
	void push_front(Monom monom); // вставка в начало
	void push_back(Monom monom); // вставка в конец
	void del(Monom monom); // удаление элемента из списка
	bool find(int pow); // проверка на наличие в списке

	int Calculate(int x); // вычисление
	Polynom operator+(const Polynom& right) const; // сложение
	Polynom operator-(Polynom& right); // вычитание
	Polynom operator*(const Polynom& right); // умножение
	Polynom operator*(const double& val) const;
	const Polynom& operator = (const Polynom& right); // присваивание

	friend ostream& operator << (ostream& os, const Polynom& object); // вывод

};


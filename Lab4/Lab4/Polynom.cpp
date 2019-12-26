#pragma once
#include "Polynom.h"
#include <cmath>
#define eps 0.00000001
using namespace std;


Monom::Monom(double _coef, int _pow)
{
	if (_pow > 999 || _pow < 0) {
		throw exception();
	}
	Coeff = _coef;
	Power = _pow;
	Next = 0;
}

Monom::Monom(double _coef, int _pow, Monom* _next)
{
	Coeff = _coef;
	Power = _pow;
	Next = _next;
}

Monom::Monom(const Monom& monom)
{
	Coeff = monom.Coeff;
	Power = monom.Power;
	Next = monom.Next;
}

bool Monom::operator==(const Monom& right)
{
	if (Power == right.Power && abs(Coeff - right.Coeff) < eps) return true;
	else return false;
}

Polynom::Polynom()
{
	size = 0;
	head = 0;
}

Polynom::Polynom(const Polynom& polynom) : Polynom()
{
	Monom* tmp = polynom.head;
	while (tmp != 0)
	{
		this->insert(tmp->Coeff, tmp->Power);
		tmp = tmp->Next;
	}
	size = polynom.size;
}



Polynom::~Polynom()
{
	clear();
}

inline void Polynom::clear()
{
	while (size && head != 0) {
		pop_front();
	}
}

void Polynom::merge(const Polynom& pol) // ������� 
{
	Polynom tmp;

	Monom* curr1 = (this)->head;
	Monom* curr2 = pol.head;

	while (curr1 != 0 && curr2 != 0) {
		if (curr1->Power <= curr2->Power) {
			Monom newMonom(*curr1);
			newMonom.Next = 0;
			tmp.push_back(newMonom);
			curr1 = curr1->Next;
		}
		else {
			Monom newMonom(*curr2);
			newMonom.Next = 0;
			tmp.push_back(newMonom);
			curr2 = curr2->Next;
		}
	}
	while (curr1 != 0) {
		Monom newMonom(*curr1);
		newMonom.Next = 0;
		tmp.push_back(newMonom);
		curr1 = curr1->Next;
	}
	while (curr2 != 0) {
		Monom newMonom(*curr2);
		newMonom.Next = 0;
		tmp.push_back(newMonom);
		curr2 = curr2->Next;
	}
	*this = tmp;

	tmp.head = 0;
	tmp.size = 0;
}

inline void Polynom::pop_front()//�������� �������
{
	Monom* tmp = head;
	head = head->Next;
	delete tmp;
	size--;
}

inline void Polynom::push_front(Monom monom) //������� � ������ �������
{
	head = new Monom(monom.Coeff, monom.Power, head);
	size++;
}

void Polynom::push_back(Monom monom)//������� � ����� �������
{
	if (head == 0) {
		head = new Monom(monom);
	}
	else {
		Monom* curr = head;
		while (curr->Next != 0) {
			curr = curr->Next;
		}
		curr->Next = new Monom(monom);
	}
	size++;
}

void Polynom::insert(Monom monom)
{
	if (head == 0 || head->Power > monom.Power) {
		push_front(monom);
		return;
	}

	Monom* curr = head;
	while (curr->Next != 0 && curr->Next->Power <= monom.Power && curr->Power <= monom.Power) {
		curr = curr->Next;
	}
	if (curr->Power == monom.Power) {
		curr->Coeff += monom.Coeff;
		if (abs(curr->Coeff) < eps) {
			del(*curr);
		}
		return;
	}
	Monom* newObject = new Monom(monom);
	newObject->Next = curr->Next;
	curr->Next = newObject;
	size++;
}

void Polynom::insert(double coef, int pow) // �������� �� ���� � �������
{
	Monom monom(coef, pow);
	if (head == 0 || head->Power > monom.Power) {
		push_front(monom);
		return;
	}

	Monom* curr = head;
	while (curr->Next != 0 && curr->Next->Power <= monom.Power && curr->Power <= monom.Power) 
	{
		curr = curr->Next;
	}
	if (curr->Power == monom.Power) 
	{
		curr->Coeff += monom.Coeff;
		if (abs(curr->Coeff) < eps) 
		{
			del(*curr);
		}
		return;
	}
	Monom* newObject = new Monom(monom);
	newObject->Next = curr->Next;
	curr->Next = newObject;
	size++;
}

void Polynom::del(Monom monom)
{
	Monom* curr = head;
	if (curr->Power == monom.Power && abs(curr->Coeff - monom.Coeff) < eps) 
	{
		pop_front();
		return;
	}
	while (curr->Next != 0 && curr->Next->Power != monom.Power) 
	{
		curr = curr->Next;
	}
	Monom* tmp = curr->Next->Next;
	delete curr->Next;
	curr->Next = tmp;
	size--;
}

bool Polynom::find(int pow) // ����� �� �������
{
	Monom* curr = head;
	while (curr != 0) 
	{
		if (curr->Power == pow) 
		{
			return true;
		}
		curr = curr->Next;
	}
	return false;
}

Polynom Polynom::operator*(const double& val) const //�������� ����-� �������� �� val
{
	Polynom tmp;
	Monom* a = this->head;
	while (a != 0) 
	{
		tmp.insert(a->Coeff, a->Power);
		a = a->Next;
	}
	Monom* temp = tmp.head;
	while (temp != 0) {
		temp->Coeff = temp->Coeff * val;
		temp = temp->Next;
	}
	return tmp;
}

const Polynom& Polynom::operator = (const Polynom& right) // ������������ ��������
{
	if (this->head != right.head) {
		clear();
		Monom* tmp = right.head;
		while (tmp != 0) {
			insert(tmp->Coeff, tmp->Power);
			tmp = tmp->Next;
		}

	}
	return *this;
}

Polynom Polynom::operator + (const Polynom& right) const //�������� ���������
{
	Polynom curr;
	Monom* thisHead = this->head;
	while (thisHead != 0) {
		curr.insert(thisHead->Coeff, thisHead->Power);
		thisHead = thisHead->Next;
	}

	Monom* rightHead = right.head;
	while (rightHead != 0) {
		curr.insert(rightHead->Coeff, rightHead->Power);
		rightHead = rightHead->Next;
	}
	return curr;
}

Polynom Polynom::operator * (const Polynom& right)// ��������� ���������
{
	Polynom curr;
	Monom* f = head;
	Monom* s = right.head;
	while (f != 0) {
		s = right.head;
		while (s != 0)
		{
			double coef = s->Coeff * f->Coeff;
			int pow = s->Power + f->Power;
			curr.insert(coef, pow);
			s = s->Next;
		}
		f = f->Next;
	}
	return curr;
}

Polynom Polynom::operator-(Polynom& right)//��������� ���������
{
	Polynom c = right * (-1.0);
	return *this + c;
}

int Polynom::Calculate(int x) //���������� 
{
	Monom* tmp = head;
	int res = 0;

	while (tmp != 0)
	{
		res += tmp->Coeff * pow(x, tmp->Power);
		tmp = tmp->Next;
	}
	return res;
}

ostream& operator << (ostream& os, const Polynom& object) //����� ��������
{
	if (object.head == 0) 
	{
		os << 0;
		return os;
	}
	Monom* temp = object.head;
	while (temp != 0)
	{
		if (temp->Coeff > 0) 
		{
			os << temp->Coeff << " ";
		}
		else 
		{
			os << "(" << temp->Coeff << ") ";
		}
		if (temp->Power != 0) 
		{
			os << "* x^" << temp->Power << " ";
		}
		if (temp->Next != 0) 
		{
			os << "+ ";
		}
		temp = temp->Next;
	}
	return os;
}
void inputPolynom(Polynom& a, int _number)
{
	for (int i = 0; i < _number; i++) {
		cout << "������� ����������� � ������� " << i + 1 << " ������: ";
		double coef;
		int ppow;
		cin >> coef >> ppow;
		a.insert(coef, ppow);
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	try
	{
		int kM1;
		cout << "���������� ������� ������� ��������: \n";
		cin >> kM1;
		Polynom pol1;
		inputPolynom(pol1, kM1);

		cout << "���������� ������� ������� ��������:  \n";
		int kM2;
		cin >> kM2;
		Polynom pol2;
		inputPolynom(pol2, kM2);
		cout << "������ �������: " << pol1 << "\n";
		cout << "������ �������: " << pol2 << "\n";
		cout << "�� ��������: " << pol1 + pol2 << "\n";
		cout << "�� ��������: " << pol1 - pol2 << "\n";
		cout << "�� ���������: " << pol1 * pol2 << "\n";
		cout << "������� x: ";
		int val;
		cin >> val;
		cout << "������ ������� ����� ����������� " << val << ": " << pol1.Calculate(val) << "\n";
		cout << "������ ������� ����� ����������� " << val << ": " << pol2.Calculate(val) << "\n";
	}
	catch (exception str) {
		throw exception(str);
	}
	system("pause");
}
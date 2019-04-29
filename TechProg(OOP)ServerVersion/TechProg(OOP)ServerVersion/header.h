#pragma once

#include "iostream"
#include "fstream"
#include <string>

using namespace std;

class type
{
public:
	// иденитфикация, порождение и ввод объекта из потока
	static type * InType(ifstream &ifst, type *current);		//Для ввода последующих эл-ов
	virtual bool InData(ifstream &ifst) = 0;			// ввод с учетом типа объекта
	virtual void Out(ofstream &ofst) = 0;// вывод с учетом типа объекта
	virtual void OutDiagonal(ofstream &ofst);
	virtual int SumOfElements() = 0;
	bool Compare(type *current);
	static int Is_Numeral_Element_and_Skip_Strings(int repeat, ifstream &ifst);

	int *mass;
	type *next;
	int HowToOut;
};


class container
{
	int len;			//кол-во элементов
public:

	type *current;	//указатель на текущий элемент

	void In(ifstream &ifst);	//ввод матриц
	void Out(ofstream &ofst);	//вывод матриц
	void Clear();				//очистка контейнера
	void Sorting();
	void FiltredOut(ofstream &ofst);
	void OutputDiagonal(ofstream &ofst);
	container();				//инициализация контейнера
};


class diagonal : public type {
	int size;
	int *mass;
public:

	// переопределяем интерфейс класса
	bool InData(ifstream &ifst); // ввод
	void Out(ofstream &ofst); // вывод
	int SumOfElements();
	void OutDiagonal(ofstream &ofst);

	diagonal() {} // создание без инициализации.
};

class matrix : public type {
	int size;
	int *mass;
public:

	// переопределяем интерфейс класса
	bool InData(ifstream &ifst); // ввод
	void Out(ofstream &ofst); // вывод
	int SumOfElements();

	matrix() {} // создание без инициализации.
};

class triagonal : public type {
	int size;
	int *mass;
public:
	// переопределяем интерфейс класса
	bool InData(ifstream &ifst); // ввод
	void Out(ofstream &ofst); // вывод
	int SumOfElements();
	triagonal() {} // создание без инициализации.
};

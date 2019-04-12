#pragma once

#include "iostream"
#include "fstream"

using namespace std;

class type
{
public:
	// иденитфикация, порождение и ввод объекта из потока
	static type* In(ifstream &ifst, type *current);				//Для ввода последующих эл-ов
	virtual int * InData(ifstream &ifst) = 0;					// ввод с учетом типа объекта
	virtual void Out(ofstream &ofst, type *current) = 0;		// вывод с учетом типа объекта
	virtual void OutDiagonal(ofstream &ofst, type *current);
	virtual int SumOfElements(type *current) = 0;

	int *mass;
	type *next;
	int HowToOut;
};


class container
{
	int len;			//кол-во элементов

public:

	type *current;	//указатель на текущий элемент

	bool In(ifstream &ifst);	//ввод матриц
	void Out(ofstream &ofst);	//вывод матриц
	void Clear();				//очистка контейнера
	void FiltredOut(ofstream &ofst);
	void OutputDiagonal(ofstream &ofst);
	container();				//инициализация контейнера
};


class diagonal : public type {
	int size;
	int *mass;
public:

	
	// переопределяем интерфейс класса
	int * InData(ifstream &ifst); // ввод
	void Out(ofstream &ofst, type *current); // вывод
	int SumOfElements(type *current);
	void OutDiagonal(ofstream &ofst, type *current);

	diagonal() {} // создание без инициализации.
};

class matrix : public type {
	int size;
	int *mass;

public:

	
	// переопределяем интерфейс класса
	int * InData(ifstream &ifst); // ввод
	void Out(ofstream &ofst, type *current); // вывод
	int SumOfElements(type *current);

	matrix() {} // создание без инициализации.
};

class triagonal : public type {
	int size;
	int *mass;

public:
	// переопределяем интерфейс класса
	int * InData(ifstream &ifst); // ввод
	void Out(ofstream &ofst, type *current); // вывод
	triagonal() {} // создание без инициализации.
};

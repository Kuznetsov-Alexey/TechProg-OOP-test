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
	virtual void Multimethod(type *other, ofstream &ofst) = 0;
	virtual void MMDiagonal(ofstream &ofst) = 0;
	virtual void MMMatrix(ofstream &ofst) = 0;

	int *mass;
	type *next;
};


class container
{
	int len;			//кол-во элементов

public:

	void Multimetod(ofstream &ofst);
	type *current;	//указатель на текущий элемент
	void In(ifstream &ifst);	//ввод матриц
	void Out(ofstream &ofst);	//вывод матриц
	void Clear();				//очистка контейнера
	container();				//инициализация контейнера
};


class diagonal : public type {
	int size;
	int *mass;
public:
	// переопределяем интерфейс класса
	int * InData(ifstream &ifst); // ввод
	void Out(ofstream &ofst, type *current); // вывод
	void Multimethod(type *other, ofstream &ofst);
	void MMDiagonal(ofstream &ofst);
	void MMMatrix(ofstream &ofst);
	diagonal() {} // создание без инициализации.
};

class matrix : public type {
	int size;
	int *mass;

public:
	// переопределяем интерфейс класса
	int * InData(ifstream &ifst); // ввод
	void Out(ofstream &ofst, type *current); // вывод
	void Multimethod(type *other, ofstream &ofst);
	void MMDiagonal(ofstream &ofst);
	void MMMatrix(ofstream &ofst);
	matrix() {} // создание без инициализации.
};

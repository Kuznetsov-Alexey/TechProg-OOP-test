#pragma once

#include "iostream"
#include "fstream"
#include <string>

using namespace std;

class type
{
public:
	// иденитфикация, порождение и ввод объекта из потока
	static type * Input_type(ifstream &ifst, type *current);//чтение из файла, классификация объекта по типу
	virtual bool Input_objects_data(ifstream &ifst) = 0;//ввод с учетом типа объекта
	virtual void Output_single_element (ofstream &ofst) = 0;//вывод с учетом типа объекта
	virtual void Output_diagonal(ofstream &ofst);//фильтрованный вывод
	virtual int Sum_of_elements() = 0;//подсчет суммы элементов в матрице
	bool Compare_two_matrix(type *current);//сравнение двух матриц
	static int Is_Numeral_Element_and_Skip_Strings(int repeat, ifstream &ifst);
	virtual void Multimethod_first_element_type(type *current, ofstream &ofst) = 0;
	virtual void Multimethod_first_diagonal(ofstream &ofst) = 0;
	virtual void Multimethod_first_matrix(ofstream &ofst) = 0;
	virtual void Multimethod_first_triagonal(ofstream &ofst) = 0;

	int *object_data;//массив элементов матрицы
	type *next_element;//указатель на следующий элемент
	int how_to_out;//способ вывода матрицы
};

class container
{
	int length;//кол-во элементов
public:
	type *current;	//указатель на текущий элемент
	void Input_from_file(ifstream &ifst);//ввод матриц
	void Output_in_file(ofstream &ofst);//вывод матриц
	void Clear();//очистка контейнера
	void Sorting();//сортировка контейнера
	void Filtred_out(ofstream &ofst);//фильтрованный вывод, первый вариант
	void Output_only_diagonal(ofstream &ofst);//фильтрованный вывод, второй вариант
	void Multimethod(ofstream &ofst);
	container();//инициализация контейнера
};

class diagonal : public type {
	int size_of_matrix;
	int *matrix_mass;
public:
	bool Input_objects_data(ifstream &ifst); // ввод
	void Output_single_element(ofstream &ofst); // вывод
	int Sum_of_elements();
	void Output_diagonal(ofstream &ofst);
	void Multimethod_first_element_type(type *current, ofstream &ofst);
	void Multimethod_first_diagonal(ofstream &ofst);
	void Multimethod_first_matrix(ofstream &ofst);
	void Multimethod_first_triagonal(ofstream &ofst);

	diagonal() {} // создание без инициализации.
};

class matrix : public type {
	int size_of_matrix;
	int *matrix_mass;
public:
	bool Input_objects_data(ifstream &ifst); // ввод
	void Output_single_element(ofstream &ofst); // вывод
	int Sum_of_elements();
	void Multimethod_first_element_type(type *current, ofstream &ofst);
	void Multimethod_first_diagonal(ofstream &ofst);
	void Multimethod_first_matrix(ofstream &ofst);
	void Multimethod_first_triagonal(ofstream &ofst);
	matrix() {} // создание без инициализации.
};

class triagonal : public type {
	int size_of_matrix;
	int *matrix_mass;
public:
	bool Input_objects_data(ifstream &ifst); // ввод
	void Output_single_element(ofstream &ofst); // вывод
	int Sum_of_elements();
	void Multimethod_first_element_type(type *current, ofstream &ofst);
	void Multimethod_first_diagonal(ofstream &ofst);
	void Multimethod_first_matrix(ofstream &ofst);
	void Multimethod_first_triagonal(ofstream &ofst);
	triagonal() {} // создание без инициализации.
};

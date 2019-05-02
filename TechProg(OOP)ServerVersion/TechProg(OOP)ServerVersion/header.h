#pragma once

#include "iostream"
#include "fstream"
#include <string>

using namespace std;

class type
{
public:
	// �������������, ���������� � ���� ������� �� ������
	static type * Input_type(ifstream &ifst, type *current);//������ �� �����, ������������� ������� �� ����
	virtual bool Input_objects_data(ifstream &ifst) = 0;//���� � ������ ���� �������
	virtual void Output_single_element (ofstream &ofst) = 0;//����� � ������ ���� �������
	virtual void Output_diagonal(ofstream &ofst);//������������� �����
	virtual int Sum_of_elements() = 0;//������� ����� ��������� � �������
	bool Compare_two_matrix(type *current);//��������� ���� ������
	static int Is_Numeral_Element_and_Skip_Strings(int repeat, ifstream &ifst);
	virtual void Multimethod_first_element_type(type *current, ofstream &ofst) = 0;
	virtual void Multimethod_first_diagonal(ofstream &ofst) = 0;
	virtual void Multimethod_first_matrix(ofstream &ofst) = 0;
	virtual void Multimethod_first_triagonal(ofstream &ofst) = 0;

	int *object_data;//������ ��������� �������
	type *next_element;//��������� �� ��������� �������
	int how_to_out;//������ ������ �������
};

class container
{
	int length;//���-�� ���������
public:
	type *current;	//��������� �� ������� �������
	void Input_from_file(ifstream &ifst);//���� ������
	void Output_in_file(ofstream &ofst);//����� ������
	void Clear();//������� ����������
	void Sorting();//���������� ����������
	void Filtred_out(ofstream &ofst);//������������� �����, ������ �������
	void Output_only_diagonal(ofstream &ofst);//������������� �����, ������ �������
	void Multimethod(ofstream &ofst);
	container();//������������� ����������
};

class diagonal : public type {
	int size_of_matrix;
	int *matrix_mass;
public:
	bool Input_objects_data(ifstream &ifst); // ����
	void Output_single_element(ofstream &ofst); // �����
	int Sum_of_elements();
	void Output_diagonal(ofstream &ofst);
	void Multimethod_first_element_type(type *current, ofstream &ofst);
	void Multimethod_first_diagonal(ofstream &ofst);
	void Multimethod_first_matrix(ofstream &ofst);
	void Multimethod_first_triagonal(ofstream &ofst);

	diagonal() {} // �������� ��� �������������.
};

class matrix : public type {
	int size_of_matrix;
	int *matrix_mass;
public:
	bool Input_objects_data(ifstream &ifst); // ����
	void Output_single_element(ofstream &ofst); // �����
	int Sum_of_elements();
	void Multimethod_first_element_type(type *current, ofstream &ofst);
	void Multimethod_first_diagonal(ofstream &ofst);
	void Multimethod_first_matrix(ofstream &ofst);
	void Multimethod_first_triagonal(ofstream &ofst);
	matrix() {} // �������� ��� �������������.
};

class triagonal : public type {
	int size_of_matrix;
	int *matrix_mass;
public:
	bool Input_objects_data(ifstream &ifst); // ����
	void Output_single_element(ofstream &ofst); // �����
	int Sum_of_elements();
	void Multimethod_first_element_type(type *current, ofstream &ofst);
	void Multimethod_first_diagonal(ofstream &ofst);
	void Multimethod_first_matrix(ofstream &ofst);
	void Multimethod_first_triagonal(ofstream &ofst);
	triagonal() {} // �������� ��� �������������.
};

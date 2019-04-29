#pragma once

#include "iostream"
#include "fstream"
#include <string>

using namespace std;

class type
{
public:
	// �������������, ���������� � ���� ������� �� ������
	static type * InType(ifstream &ifst, type *current);		//��� ����� ����������� ��-��
	virtual bool InData(ifstream &ifst) = 0;			// ���� � ������ ���� �������
	virtual void Out(ofstream &ofst) = 0;// ����� � ������ ���� �������
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
	int len;			//���-�� ���������
public:

	type *current;	//��������� �� ������� �������

	void In(ifstream &ifst);	//���� ������
	void Out(ofstream &ofst);	//����� ������
	void Clear();				//������� ����������
	void Sorting();
	void FiltredOut(ofstream &ofst);
	void OutputDiagonal(ofstream &ofst);
	container();				//������������� ����������
};


class diagonal : public type {
	int size;
	int *mass;
public:

	// �������������� ��������� ������
	bool InData(ifstream &ifst); // ����
	void Out(ofstream &ofst); // �����
	int SumOfElements();
	void OutDiagonal(ofstream &ofst);

	diagonal() {} // �������� ��� �������������.
};

class matrix : public type {
	int size;
	int *mass;
public:

	// �������������� ��������� ������
	bool InData(ifstream &ifst); // ����
	void Out(ofstream &ofst); // �����
	int SumOfElements();

	matrix() {} // �������� ��� �������������.
};

class triagonal : public type {
	int size;
	int *mass;
public:
	// �������������� ��������� ������
	bool InData(ifstream &ifst); // ����
	void Out(ofstream &ofst); // �����
	int SumOfElements();
	triagonal() {} // �������� ��� �������������.
};

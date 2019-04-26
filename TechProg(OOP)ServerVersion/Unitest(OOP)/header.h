#pragma once
//#include "stdafx.h"
#include "iostream"
#include "fstream"

using namespace std;

class type
{
public:
	// �������������, ���������� � ���� ������� �� ������
	static type* In(ifstream &ifst, type *current);				//��� ����� ����������� ��-��
	virtual void InData(ifstream &ifst) = 0;					// ���� � ������ ���� �������
	virtual void Out(ofstream &ofst) = 0;		// ����� � ������ ���� �������
	virtual void OutDiagonal(ofstream &ofst);
	virtual int SumOfElements(type *current) = 0;
	virtual void SetMass(int* expected) = 0;
	bool Compare(type *current);

	int *mass;
	type *next;
	int HowToOut;
};


class container
{
	int len;			//���-�� ���������

public:

	type *current;	//��������� �� ������� �������

	void lenplus();
	bool In(ifstream &ifst);	//���� ������
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
	void InData(ifstream &ifst); // ����
	void Out(ofstream &ofst); // �����
	int SumOfElements(type *current);
	void OutDiagonal(ofstream &ofst, type *current);
	void SetMass(int* expected);

	diagonal() {} // �������� ��� �������������.
};

class matrix : public type {
	int size;
	int *mass;

public:

	// �������������� ��������� ������
	void InData(ifstream &ifst); // ����
	void Out(ofstream &ofst); // �����
	int SumOfElements(type *current);
	void SetMass(int* expected);

	matrix() {} // �������� ��� �������������.
};

class triagonal : public type {
	int size;
	int *mass;

public:
	// �������������� ��������� ������
	void InData(ifstream &ifst); // ����
	void Out(ofstream &ofst); // �����
	int SumOfElements(type *current);
	void SetMass(int* expected);
	triagonal() {} // �������� ��� �������������.
};

#pragma once

#include "iostream"
#include "fstream"

using namespace std;

class type
{
public:
	// �������������, ���������� � ���� ������� �� ������
	static type* In(ifstream &ifst, type *current);				//��� ����� ����������� ��-��
	virtual int * InData(ifstream &ifst) = 0;					// ���� � ������ ���� �������
	virtual void Out(ofstream &ofst, type *current) = 0;		// ����� � ������ ���� �������
	virtual void OutDiagonal(ofstream &ofst, type *current);
	virtual int SumOfElements(type *current) = 0;

	int *mass;
	type *next;
	int HowToOut;
};


class container
{
	int len;			//���-�� ���������

public:

	type *current;	//��������� �� ������� �������

	bool In(ifstream &ifst);	//���� ������
	void Out(ofstream &ofst);	//����� ������
	void Clear();				//������� ����������
	void FiltredOut(ofstream &ofst);
	void OutputDiagonal(ofstream &ofst);
	container();				//������������� ����������
};


class diagonal : public type {
	int size;
	int *mass;
public:

	
	// �������������� ��������� ������
	int * InData(ifstream &ifst); // ����
	void Out(ofstream &ofst, type *current); // �����
	int SumOfElements(type *current);
	void OutDiagonal(ofstream &ofst, type *current);

	diagonal() {} // �������� ��� �������������.
};

class matrix : public type {
	int size;
	int *mass;

public:

	
	// �������������� ��������� ������
	int * InData(ifstream &ifst); // ����
	void Out(ofstream &ofst, type *current); // �����
	int SumOfElements(type *current);

	matrix() {} // �������� ��� �������������.
};

class triagonal : public type {
	int size;
	int *mass;

public:
	// �������������� ��������� ������
	int * InData(ifstream &ifst); // ����
	void Out(ofstream &ofst, type *current); // �����
	triagonal() {} // �������� ��� �������������.
};

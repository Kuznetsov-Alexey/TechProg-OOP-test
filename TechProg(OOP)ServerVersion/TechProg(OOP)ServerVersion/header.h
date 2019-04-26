#pragma once

#include "iostream"
#include "fstream"

using namespace std;

class type
{
public:
	// �������������, ���������� � ���� ������� �� ������
	static type* In(ifstream &ifst, type *current);		//��� ����� ����������� ��-��
	virtual void InData(ifstream &ifst) = 0;			// ���� � ������ ���� �������
	virtual void Out(ofstream &ofst) = 0;// ����� � ������ ���� �������
	virtual void OutDiagonal(ofstream &ofst);
	virtual int SumOfElements() = 0;
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
	int SumOfElements();
	void OutDiagonal(ofstream &ofst);

	diagonal() {} // �������� ��� �������������.
};

class matrix : public type {
	int size;
	int *mass;

public:

	// �������������� ��������� ������
	void InData(ifstream &ifst); // ����
	void Out(ofstream &ofst); // �����
	int SumOfElements();

	matrix() {} // �������� ��� �������������.
};

class triagonal : public type {
	int size;
	int *mass;

public:
	// �������������� ��������� ������
	void InData(ifstream &ifst); // ����
	void Out(ofstream &ofst); // �����
	int SumOfElements();
	triagonal() {} // �������� ��� �������������.
};

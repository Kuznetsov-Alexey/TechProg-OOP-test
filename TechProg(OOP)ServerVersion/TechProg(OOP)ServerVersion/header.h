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
	virtual void Multimethod(type *other, ofstream &ofst) = 0;
	virtual void MMDiagonal(ofstream &ofst) = 0;
	virtual void MMMatrix(ofstream &ofst) = 0;

	int *mass;
	type *next;
};


class container
{
	int len;			//���-�� ���������

public:

	void Multimetod(ofstream &ofst);
	type *current;	//��������� �� ������� �������
	void In(ifstream &ifst);	//���� ������
	void Out(ofstream &ofst);	//����� ������
	void Clear();				//������� ����������
	container();				//������������� ����������
};


class diagonal : public type {
	int size;
	int *mass;
public:
	// �������������� ��������� ������
	int * InData(ifstream &ifst); // ����
	void Out(ofstream &ofst, type *current); // �����
	void Multimethod(type *other, ofstream &ofst);
	void MMDiagonal(ofstream &ofst);
	void MMMatrix(ofstream &ofst);
	diagonal() {} // �������� ��� �������������.
};

class matrix : public type {
	int size;
	int *mass;

public:
	// �������������� ��������� ������
	int * InData(ifstream &ifst); // ����
	void Out(ofstream &ofst, type *current); // �����
	void Multimethod(type *other, ofstream &ofst);
	void MMDiagonal(ofstream &ofst);
	void MMMatrix(ofstream &ofst);
	matrix() {} // �������� ��� �������������.
};

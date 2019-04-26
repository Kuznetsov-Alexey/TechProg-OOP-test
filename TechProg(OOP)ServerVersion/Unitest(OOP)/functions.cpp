#include "stdafx.h"
#include "header.h"

bool container::In(ifstream &ifst)
{
	bool ErrorFlag = false;
	while ((!ifst.eof())&&(!ErrorFlag)) {
		if ((current = current->In(ifst, current)) != 0) {
			len++;
		}
		else
		{
			cout << "Incorrect Type in File";
			ErrorFlag = true;
		}
	}
	return(ErrorFlag);
}

void container::Out(ofstream &ofst)
{
	ofst << "Container contents " << len
		<< " elements." << endl;

	for (int i = 0; i < len; i++) {
		ofst << i + 1 << ": ";
		if (len > 0)
		{
			current->Out(ofst);
			current = current->next;
		}
	}
}

void container::Clear()
{
	while (len > 0)
	{
		if (len == 1)
		{
			type *temp = current;
			current = NULL;
			free(temp);
			len = len - 1;
			break;
		}
		type *temp;
		temp = current->next;
		while (temp->next != current)
			temp = temp->next;

		temp->next = current->next;
		free(current);
		current = temp;
		len = len - 1;
	}



}

void container::FiltredOut(ofstream &ofst)
{
	int DiagonalCount = 0;
	for (int i = 0; i < len; i++)
	{
		diagonal* Temporary = dynamic_cast<diagonal*>(current);
		if (Temporary)
			DiagonalCount++;
		current = current->next;
	}
	ofst << "Container contents " << DiagonalCount
		<< " Diagonal elements." << endl;

	DiagonalCount = 1;

	for (int i = 0; i < len; i++) {

		if (len > 0)
		{
			diagonal* Temporary = dynamic_cast<diagonal*>(current);
			if (Temporary)
			{
				ofst << DiagonalCount << ": ";
				current->Out(ofst);
				DiagonalCount++;
			}
			current = current->next;
		}
	}
}

void container::OutputDiagonal(ofstream &ofst)
{
	ofst << "Only Diagonal matrix." << endl;
	for (int i = 0; i < len; i++)
	{
		ofst << i << ": ";
		current->OutDiagonal(ofst);
		current = current->next;
	}
}

container::container()
{
	current = NULL;
	len = 0;
}

void container::Sorting()
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - 1; j++)
		{
			if (current->Compare(current))
			{
				type *previously1 = current;

				while (previously1->next != current)
					previously1 = previously1->next;

				type *next1 = current->next;
				type *next2 = current->next->next;

				current->next->next = current;
				current->next = next2;
				previously1->next = next1;
				current = next1;
			}
		}
		current = current->next;
	}
	current = current->next;
}


type* type::In(ifstream &ifst, type *current)
{
	type *temporary, *point;	//Временные указатели
	int k;
	ifst >> k;
	switch (k) {
	case 1:
		temporary = new diagonal; break;
	case 2:
		temporary = new matrix; break;
	case 3:
		temporary = new triagonal; break;

	default:
		return 0;
	}

	ifst >> temporary->HowToOut;

	if (current == NULL)
	{
		temporary->InData(ifst);
		temporary->next = temporary; // указатель на сам корневой узел
	}
	else
	{
		temporary->InData(ifst);
		point = current->next; // сохранение указателя на следующий элемент
		current->next = temporary; // предыдущий узел указывает на создаваемый
		temporary->next = point; // созданный узел указывает на следующий элемент
		current->mass = temporary->mass;
	}
	return temporary;
}

void type::OutDiagonal(ofstream &ofst)
{
	ofst << endl;
}

bool type::Compare(type *current)
{
	int FirstSum = SumOfElements(current);
	int SecondSum = SumOfElements(current->next);
	return(FirstSum > SecondSum);
}


void diagonal::InData(ifstream &ifst)
{
	ifst >> size;
	mass = new int[size]; // массив значений эл-ов главной диагонали
	for (int i = 0; i < size; i++)
	{
		ifst >> mass[i];
	}
}

void diagonal::Out(ofstream &ofst)
{
	ofst << "It's Diagonal matrix " << size << "x" << size << endl;

	for (int i = 0; i < size; i++)
	{
		int j = size - i;
		int k = i + 1;
		while (j < size)
		{
			ofst << "0 ";
			j++;
		}

		ofst << mass[i];

		while (k < size)
		{
			ofst << " 0";
			k++;
		}
		if (HowToOut == 1)
			ofst << endl;
		else
			ofst << " ";
	}

	if (HowToOut != 1)
		ofst << endl;

	ofst << endl;
}

int diagonal::SumOfElements(type *current)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
			sum = sum + mass[i];

	return sum;
}

void diagonal::OutDiagonal(ofstream &ofst, type *current)
{
	Out(ofst);
}

void diagonal::SetMass(int* expected)
{
	for (int i = 0; i < size; i++)
		expected[i] = mass[i];
}


void matrix::InData(ifstream &ifst)
{
	ifst >> size;
	mass = new int[size*size]; // массив значений 

	for (int i = 0; i < size*size; i++)
	{
		ifst >> mass[i];
	}
}

void matrix::Out(ofstream &ofst)
{
	ofst << "It's Casual matrix " << size << "x" << size << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			ofst << mass[i*size + j] << " ";
		}

		if (HowToOut == 1)
			ofst << endl;
		else
			ofst << " ";
	}

	if (HowToOut != 1)
		ofst << endl;
	ofst << endl;
}

int matrix::SumOfElements(type *current)
{
	int sum = 0;
	for (int i = 0; i < size*size; i++)
		sum = sum + mass[i];

	return sum;
}

void matrix::SetMass(int* expected)
{
	for (int i = 0; i < size * size; i++)
		expected[i] = mass[i];
}


void triagonal::InData(ifstream &ifst)
{
	ifst >> size;
	int RealSize = size * size - size;
	RealSize = RealSize / 2;
	RealSize = RealSize + size;

	mass = new int[RealSize];

	for (int i = 0; i < RealSize; i++)
	{
		ifst >> mass[i];
	}
}

void triagonal::Out(ofstream &ofst)
{
	ofst << "It's Triagonal matrix " << size << "x" << size << endl;

	int RealMass = 0;

	for (int i = 0; i < size; i++)
	{
		int j = size - i - 1;
		int k = i + 1;				

		while (j < size)
		{
			ofst << mass[RealMass] << " ";
			RealMass++;
			j++;
		}
		
		while (k < size)
		{
			ofst << "0 ";
			k++;
		}

		if (HowToOut == 1)
			ofst << endl;
	}

	if (HowToOut != 1)
		ofst << endl;

	ofst << endl;
}

int triagonal::SumOfElements(type *current)
{
	int sum = 0;
	int RealSize = size * size - size;
	RealSize = RealSize / 2;
	RealSize = RealSize + size;

	for (int i = 0; i < RealSize; i++)
		sum = sum + mass[i];

	return sum;
}

void triagonal::SetMass(int* expected)
{
	int RealSize = size * size - size;
	RealSize = RealSize / 2;
	RealSize = RealSize + size;

	for (int i = 0; i < RealSize; i++)
		expected[i] = mass[i];
}

void container::lenplus()
{
	len++;
}




#include "header.h"

bool container::In(ifstream &ifst)
{
	bool ErrorFlag = false;
	while ((!ifst.eof())&&(!ErrorFlag)) {
		if ((container::current = type::In(ifst, current)) != 0) {
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
			current->Out(ofst, current);
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

container::container()
{
	current = NULL;
	len = 0;
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
		temporary->mass = temporary->InData(ifst);
		temporary->next = temporary; // указатель на сам корневой узел
	}
	else
	{
		temporary->mass = temporary->InData(ifst);
		point = current->next; // сохранение указателя на следующий элемент
		current->next = temporary; // предыдущий узел указывает на создаваемый
		temporary->next = point; // созданный узел указывает на следующий элемент
		current->mass = temporary->mass;
	}
	return temporary;
}


int * diagonal::InData(ifstream &ifst)
{
	ifst >> size;
	mass = new int[size]; // массив значений эл-ов главной диагонали
	for (int i = 0; i < size; i++)
	{
		ifst >> mass[i];
	}
	return(mass);
}

void diagonal::Out(ofstream &ofst, type *current)
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
	
	if(HowToOut !=1)
		ofst << endl;

	ofst << endl;
}


int * matrix::InData(ifstream &ifst)
{
	ifst >> size;
	mass = new int[size*size]; // массив значений 

	for (int i = 0; i < size*size; i++)
	{
		ifst >> mass[i];
	}
	return(mass);
}

void matrix::Out(ofstream &ofst, type *current)
{
	ofst << "It's Casual matrix " << size << "x" << size << endl;
	for (int i = 0; i < size; i++)
	ofst << "It's casual matrix " << size << "x" << size << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			ofst << matrix::mass[i*size + j] << " ";
		}
		ofst << endl;
	}
	ofst << endl;
}

int * triagonal::InData(ifstream &ifst)
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
	return(mass);
}

void triagonal::Out(ofstream &ofst, type *current)
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
		
		if(HowToOut == 1)
			ofst << endl;
		else
			ofst << " ";

		ofst << endl;
	}

	if (HowToOut != 1)
		ofst << endl;
	ofst << endl;
}
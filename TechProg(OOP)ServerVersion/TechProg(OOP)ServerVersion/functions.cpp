#include "header.h"

void container::In(ifstream &ifst)
{
	while (!ifst.eof()) {
		if ((container::current = type::In(ifst, current)) != 0) {
			len++;
		}
	}
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

bool type::Compare(type *current)
{
	int FirstSum = SumOfElements(current);
	int SecondSum = current->next->SumOfElements(current->next);
	return(FirstSum > SecondSum);
}
type* type::In(ifstream &ifst, type *current)
{
	type *temporary, *point;	//Временные указатели
	int k;
	//int size;
	ifst >> k;
	switch (k) {
	case 1:
		temporary = new diagonal; break;
	case 2:
		temporary = new matrix; break;
	default:
		return 0;
	}

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

		ofst << endl;
	}
	ofst << endl;
}

int diagonal::SumOfElements(type *current)
{
	int sum = 0;
	for (int i = 0; i < size; i++)
			sum = sum + mass[i];

	return sum;
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
	ofst << "It's casual matrix " << size << "x" << size << endl;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			ofst << mass[i*size + j] << " ";
		}
		ofst << endl;
	}
	ofst << endl;
}

int matrix::SumOfElements(type *current)
{
	int sum = 0;
	for (int i = 0; i < size*size; i++)
		sum = sum + mass[i];

	return sum;
}

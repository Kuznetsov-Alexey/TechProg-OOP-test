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

type* type::In(ifstream &ifst, type *current)
{

	type *temporary, *point;	//Âðåìåííûå óêàçàòåëè
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
		temporary->next = temporary; // óêàçàòåëü íà ñàì êîðíåâîé óçåë
	}
	else
	{
		temporary->mass = temporary->InData(ifst);
		point = current->next; // ñîõðàíåíèå óêàçàòåëÿ íà ñëåäóþùèé ýëåìåíò
		current->next = temporary; // ïðåäûäóùèé óçåë óêàçûâàåò íà ñîçäàâàåìûé
		temporary->next = point; // ñîçäàííûé óçåë óêàçûâàåò íà ñëåäóþùèé ýëåìåíò
		current->mass = temporary->mass;
	}
	return temporary;


}


int * diagonal::InData(ifstream &ifst)
{
	ifst >> size;
	mass = new int[size]; // ìàññèâ çíà÷åíèé ýë-îâ ãëàâíîé äèàãîíàëè
	for (int i = 0; i < size; i++)
	{
		ifst >> mass[i];
	}
	return(mass);
}

void diagonal::Out(ofstream &ofst, type *current)
{
	ofst << "It's simple matrix " << size << "x" << size << endl;

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


int * matrix::InData(ifstream &ifst)
{
	ifst >> size;
	matrix::mass = new int[size*size]; // ìàññèâ çíà÷åíèé 

	for (int i = 0; i < size*size; i++)
	{
		ifst >> mass[i];
	}
	return(mass);
}

void matrix::Out(ofstream &ofst, type *current)
{
	ofst << "It's casual matrix " << matrix::size << "x" << matrix::size << endl;
	for (int i = 0; i < matrix::size; i++)
	{
		for (int j = 0; j < matrix::size; j++)
		{
			ofst << matrix::mass[i*matrix::size + j] << " ";
		}
		ofst << endl;
	}
	ofst << endl;
}

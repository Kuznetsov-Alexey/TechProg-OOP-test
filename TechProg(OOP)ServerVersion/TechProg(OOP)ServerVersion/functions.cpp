#include "header.h"

void container::In(ifstream &ifst)
{
	bool ErrorFlag = false;
	while ((!ifst.eof())&&(!ErrorFlag)) 
	{

		if (container::current == NULL)
		{
			if ((container::current = type::InType(ifst, current)) != 0)
				len++;
		}
		else
		{
			if(type::InType(ifst, current)!= 0)
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
			current = current->next;
		}
		current = current->next;
	}	
}


type* type::InType(ifstream &ifst, type *current)
{
	int key;
	if ((key = Is_Numeral_Element_and_Skip_Strings(4, ifst)) == 0)
		return 0;

	type *temporary, *point;	//Временные указатели
	bool success_input;
	
	switch (key)
	{
		case 1:
			temporary = new diagonal; break;
		case 2:
			temporary = new matrix; break;
		case 3:
			temporary = new triagonal; break;

		default:
			Is_Numeral_Element_and_Skip_Strings(4, ifst);
			return 0;
	}
	
	success_input = temporary->InData(ifst);

	if (!success_input)
		return 0;
	if (current == NULL)
		temporary->next = temporary; // указатель на сам корневой узел		
	
	else
	{
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
	int FirstSum = SumOfElements();
	int SecondSum = next->SumOfElements();
	return(FirstSum > SecondSum);
}

int type::Is_Numeral_Element_and_Skip_Strings(int repeat, ifstream &ifst)
{
	int result;
	string line;
	ifst >> line;
	if (!isdigit(unsigned char(line.front())))
	{
		for (int i = 0; i < repeat; i++)
			getline(ifst, line, '\n');
		return 0;
	}
	result = stoul(line);
	getline(ifst, line, '\n');
	return result;
}


bool diagonal::InData(ifstream &ifst)
{
	string line_of_elements;
	string element;
	int length_element;

	if ((HowToOut = Is_Numeral_Element_and_Skip_Strings(3, ifst)) == 0)
		return 0;

	if ((size = Is_Numeral_Element_and_Skip_Strings(2, ifst)) == 0)
		return 0;

	getline(ifst, line_of_elements, '\n');

	mass = new int[size]; // массив значений эл-ов главной диагонали
	for (int i = 0; i < size; i++)
	{
		
		if (line_of_elements.length() == 0)
			return 0;

		length_element = line_of_elements.find(' ');

		if (length_element > 0)
		{
			element = line_of_elements.substr(0, length_element);
			length_element++;
		}
		else
		{
			length_element = line_of_elements.length();
			element = line_of_elements;
		}

		if (!isdigit(unsigned char(element.front())))
			return 0;

		mass[i] = stoul(element);
		element = "";
		line_of_elements.erase(0, length_element);
	}
	return 1;
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

int diagonal::SumOfElements()
{
	int sum = 0;
	for (int i = 0; i < size; i++)
			sum = sum + mass[i];

	return sum;
}

void diagonal::OutDiagonal(ofstream &ofst)
{
	Out(ofst);
}


bool matrix::InData(ifstream &ifst)
{
	string line_of_elements;
	string element;
	int length_element;

	if ((HowToOut = Is_Numeral_Element_and_Skip_Strings(3, ifst)) == 0)
		return 0;

	if ((size = Is_Numeral_Element_and_Skip_Strings(2, ifst)) == 0)
		return 0;

	getline(ifst, line_of_elements, '\n');

	mass = new int[size*size]; // массив значений 

	for (int i = 0; i < size*size; i++)
	{
		if (line_of_elements.length() == 0)
			return 0;

		length_element = line_of_elements.find(' ');

		if (length_element > 0)
		{
			element = line_of_elements.substr(0, length_element);
			length_element++;
		}
		else
		{
			length_element = line_of_elements.length();
			element = line_of_elements;
		}

		if (!isdigit(unsigned char(element.front())))
			return 0;

		mass[i] = stoul(element);
		element = "";
		line_of_elements.erase(0, length_element);
	}
	return 1;
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

int matrix::SumOfElements()
{
	int sum = 0;
	for (int i = 0; i < size*size; i++)
		sum = sum + mass[i];

	return sum;
}


bool triagonal::InData(ifstream &ifst)
{
	string line_of_elements;
	string element;
	int length_element;

	if ((HowToOut = Is_Numeral_Element_and_Skip_Strings(3, ifst)) == 0)
		return 0;

	if ((size = Is_Numeral_Element_and_Skip_Strings(2, ifst)) == 0)
		return 0;

	getline(ifst, line_of_elements, '\n');

	int RealSize = size * size - size;
	RealSize = RealSize / 2;
	RealSize = RealSize + size;

	mass = new int[RealSize];

	for (int i = 0; i < RealSize; i++)
	{
		if (line_of_elements.length() == 0)
			return 0;

		length_element = line_of_elements.find(' ');

		if (length_element > 0)
		{
			element = line_of_elements.substr(0, length_element);
			length_element++;
		}
		else
		{
			length_element = line_of_elements.length();
			element = line_of_elements;
		}

		if (!isdigit(unsigned char(element.front())))
			return 0;

		mass[i] = stoul(element);
		element = "";
		line_of_elements.erase(0, length_element);
	}
	return 1;
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

int triagonal::SumOfElements()
{
	int sum = 0;
	int RealSize = size * size - size;
	RealSize = RealSize / 2;
	RealSize = RealSize + size;

	for (int i = 0; i < RealSize; i++)
		sum = sum + mass[i];

	return sum;
}





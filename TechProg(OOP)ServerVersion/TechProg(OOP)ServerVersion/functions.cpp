#include "header.h"

void container::Input_from_file(ifstream &ifst)
{
	while ((!ifst.eof()))
	{
		if (current == NULL)
		{
			if ((current = type::Input_type(ifst, current)) != 0)
				length++;
		}
		else
		{
			if(type::Input_type(ifst, current)!= 0)
				length++;
		}
	}	
}

void container::Output_in_file(ofstream &ofst)
{
	ofst << "Container contents " << length
		<< " elements." << endl;
	for (int i = 0; i < length; i++) {
		ofst << i + 1 << ": ";
		if (length > 0)
		{
			current->Output_single_element(ofst);
			current = current->next_element;
		}
	}
}

void container::Clear()
{
	while (length > 0)
	{
		if (length == 1)
		{
			type *temporary = current;
			current = NULL;
			free(temporary);
			length = length - 1;
			break;
		}
		type *temporary;
		temporary = current->next_element;
		while (temporary->next_element != current)
			temporary = temporary->next_element;

		temporary->next_element = current->next_element;
		free(current);
		current = temporary;
		length = length - 1;
	}
}

void container::Filtred_out(ofstream &ofst)
{
	int diagonal_count = 0;
	for (int i = 0; i < length; i++)
	{
		diagonal* Temporary = dynamic_cast<diagonal*>(current);
		if (Temporary)
			diagonal_count++;
		current = current->next_element;
	}
	ofst << "Container contents " << diagonal_count
		<< " Diagonal elements." << endl;

	diagonal_count = 1;
	for (int i = 0; i < length; i++)
	{
		if (length > 0)
		{
			diagonal* Temporary = dynamic_cast<diagonal*>(current);
			if (Temporary)
			{
				ofst << diagonal_count << ": ";
				current->Output_single_element(ofst);
				diagonal_count++;
			}
			current = current->next_element;
		}
	}
}

void container::Output_only_diagonal(ofstream &ofst)
{
	ofst << "Only Diagonal matrix." << endl;
	for (int i = 0; i < length; i++)
	{
		ofst << i << ": ";
		current->Output_diagonal(ofst);
		current = current->next_element;
	}
}

container::container()
{
	current = NULL;
	length = 0;
}

void container::Sorting()
{
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - 1; j++)
		{
			if (current->Compare_two_matrix(current))
			{
				type *previously1 = current;
				while (previously1->next_element != current)
					previously1 = previously1->next_element;

				type *next1 = current->next_element;
				type *next2 = current->next_element->next_element;

				current->next_element->next_element = current;
				current->next_element = next2;
				previously1->next_element = next1;
				current = next1;
			}
			current = current->next_element;
		}
		current = current->next_element;
	}	
}

type* type::Input_type(ifstream &ifst, type *current)
{
	int type_of_element;
	if ((type_of_element = Is_Numeral_Element_and_Skip_Strings(4, ifst)) == 0)
		return 0;

	type *object_from_file, *point;	//Временные указатели
	bool success_input;	
	switch (type_of_element)
	{
		case 1:
			object_from_file = new diagonal; break;
		case 2:
			object_from_file = new matrix; break;
		case 3:
			object_from_file = new triagonal; break;

		default:
			Is_Numeral_Element_and_Skip_Strings(4, ifst);
			return 0;
	}
	
	success_input = object_from_file->Input_objects_data(ifst);
	if (!success_input)
		return 0;
	if (current == NULL)
		object_from_file->next_element = object_from_file; // указатель на сам корневой узел		
	
	else
	{
		point = current->next_element; // сохранение указателя на следующий элемент
		current->next_element = object_from_file; // предыдущий узел указывает на создаваемый
		object_from_file->next_element = point; // созданный узел указывает на следующий элемент
	}
	return object_from_file;
}

void type::Output_diagonal(ofstream &ofst)
{
	ofst << endl;
}

bool type::Compare_two_matrix(type *current)
{
	int first_sum = Sum_of_elements();
	int second_sum = next_element->Sum_of_elements();
	return(first_sum > second_sum);
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

bool diagonal::Input_objects_data(ifstream &ifst)
{
	string line_of_elements;
	string numeral_from_string;
	int length_element;

	if ((how_to_out = Is_Numeral_Element_and_Skip_Strings(3, ifst)) == 0)
		return 0;

	if ((size_of_matrix = Is_Numeral_Element_and_Skip_Strings(2, ifst)) == 0)
		return 0;

	getline(ifst, line_of_elements, '\n');
	matrix_mass = new int[size_of_matrix]; // массив значений эл-ов главной диагонали
	for (int i = 0; i < size_of_matrix; i++)
	{		
		if (line_of_elements.length() == 0)
			return 0;

		length_element = line_of_elements.find(' ');

		if (length_element > 0)
		{
			numeral_from_string = line_of_elements.substr(0, length_element);
			length_element++;
		}
		else
		{
			length_element = line_of_elements.length();
			numeral_from_string = line_of_elements;
		}

		if (!isdigit(unsigned char(numeral_from_string.front())))
			return 0;

		matrix_mass[i] = stoul(numeral_from_string);
		numeral_from_string = "";
		line_of_elements.erase(0, length_element);
	}
	return 1;
}

void diagonal::Output_single_element(ofstream &ofst)
{
	ofst << "It's Diagonal matrix " << size_of_matrix << "x" << size_of_matrix << endl;

	for (int i = 0; i < size_of_matrix; i++)
	{
		int count_nulls_before_unit = size_of_matrix - i;
		int count_nulls_after_unit = i + 1;
		while (count_nulls_before_unit < size_of_matrix)
		{
			ofst << "0 ";
			count_nulls_before_unit++;
		}

		ofst << matrix_mass[i];

		while (count_nulls_after_unit < size_of_matrix)
		{
			ofst << " 0";
			count_nulls_after_unit++;
		}
		if (how_to_out == 1)
			ofst << endl;
		else
			ofst << " ";
	}

	if (how_to_out != 1)
		ofst << endl;

	ofst << endl;
}

int diagonal::Sum_of_elements()
{
	int sum_of_elements = 0;
	for (int i = 0; i < size_of_matrix; i++)
			sum_of_elements = sum_of_elements + matrix_mass[i];

	return sum_of_elements;
}

void diagonal::Output_diagonal(ofstream &ofst)
{
	Output_single_element(ofst);
}

bool matrix::Input_objects_data(ifstream &ifst)
{
	string line_of_elements;
	string numeral_from_string;
	int length_element;

	if ((how_to_out = Is_Numeral_Element_and_Skip_Strings(3, ifst)) == 0)
		return 0;

	if ((size_of_matrix = Is_Numeral_Element_and_Skip_Strings(2, ifst)) == 0)
		return 0;

	getline(ifst, line_of_elements, '\n');
	matrix_mass = new int[size_of_matrix*size_of_matrix]; // массив значений 
	for (int i = 0; i < size_of_matrix*size_of_matrix; i++)
	{
		if (line_of_elements.length() == 0)
			return 0;

		length_element = line_of_elements.find(' ');

		if (length_element > 0)
		{
			numeral_from_string = line_of_elements.substr(0, length_element);
			length_element++;
		}
		else
		{
			length_element = line_of_elements.length();
			numeral_from_string = line_of_elements;
		}

		if (!isdigit(unsigned char(numeral_from_string.front())))
			return 0;

		matrix_mass[i] = stoul(numeral_from_string);
		numeral_from_string = "";
		line_of_elements.erase(0, length_element);
	}
	return 1;
}

void matrix::Output_single_element(ofstream &ofst)
{
	ofst << "It's Casual matrix " << size_of_matrix << "x" << size_of_matrix << endl;
	for (int i = 0; i < size_of_matrix; i++)
	{
		for (int j = 0; j < size_of_matrix; j++)
		{
			ofst << matrix_mass[i * size_of_matrix + j] << " ";
		}

		if (how_to_out == 1)
			ofst << endl;
		else
			ofst << " ";
	}

	if (how_to_out != 1)
		ofst << endl;
	ofst << endl;
}

int matrix::Sum_of_elements()
{
	int sum_of_elements = 0;
	for (int i = 0; i < size_of_matrix*size_of_matrix; i++)
		sum_of_elements = sum_of_elements + matrix_mass[i];

	return sum_of_elements;
}

bool triagonal::Input_objects_data(ifstream &ifst)
{
	string line_of_elements;
	string numeral_from_string;
	int length_element;

	if ((how_to_out = Is_Numeral_Element_and_Skip_Strings(3, ifst)) == 0)
		return 0;

	if ((size_of_matrix = Is_Numeral_Element_and_Skip_Strings(2, ifst)) == 0)
		return 0;

	getline(ifst, line_of_elements, '\n');

	int real_data_size = size_of_matrix * size_of_matrix - size_of_matrix;
	real_data_size = real_data_size / 2;
	real_data_size = real_data_size + size_of_matrix;

	matrix_mass = new int[real_data_size];
	for (int i = 0; i < real_data_size; i++)
	{
		if (line_of_elements.length() == 0)
			return 0;

		length_element = line_of_elements.find(' ');

		if (length_element > 0)
		{
			numeral_from_string = line_of_elements.substr(0, length_element);
			length_element++;
		}
		else
		{
			length_element = line_of_elements.length();
			numeral_from_string = line_of_elements;
		}

		if (!isdigit(unsigned char(numeral_from_string.front())))
			return 0;

		matrix_mass[i] = stoul(numeral_from_string);
		numeral_from_string = "";
		line_of_elements.erase(0, length_element);
	}
	return 1;
}

void triagonal::Output_single_element(ofstream &ofst)
{
	ofst << "It's Triagonal matrix " << size_of_matrix << "x" << size_of_matrix << endl;

	int point_to_real_elements = 0;
	for (int i = 0; i < size_of_matrix; i++)
	{
		int count_real_elements = size_of_matrix - i - 1;
		int count_zero_elements = i + 1;				

		while (count_real_elements < size_of_matrix)
		{
			ofst << matrix_mass[point_to_real_elements] << " ";
			point_to_real_elements++;
			count_real_elements++;
		}
		
		while (count_zero_elements < size_of_matrix)
		{
			ofst << "0 ";
			count_zero_elements++;
		}

		if (how_to_out == 1)
			ofst << endl;
	}

	if (how_to_out != 1)
		ofst << endl;

	ofst << endl;
}

int triagonal::Sum_of_elements()
{
	int sum_of_elements = 0;
	int real_data_size = size_of_matrix * size_of_matrix - size_of_matrix;
	real_data_size = real_data_size / 2;
	real_data_size = real_data_size + size_of_matrix;

	for (int i = 0; i < real_data_size; i++)
		sum_of_elements = sum_of_elements + matrix_mass[i];

	return sum_of_elements;
}





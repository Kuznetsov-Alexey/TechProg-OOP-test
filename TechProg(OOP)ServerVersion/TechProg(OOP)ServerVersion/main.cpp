#include "header.h"

int main(int argc, char* argv[])
{
	ifstream ifst("input.txt");  // файлы для ввода и вывода
	ofstream ofst("output.txt"); // с ними удобнее работать
	cout << "Start" << endl;
	container c;
	c.Input_from_file(ifst);
	ofst << "Filled container. " << endl;
	c.Sorting();
	c.Output_in_file(ofst);
	c.Filtred_out(ofst);
	c.Output_only_diagonal(ofst);
	c.Clear();
	ofst << "Empty container. " << endl;
	c.Output_in_file(ofst);
	cout << "Stop" << endl;
	return 0;
}

#include "stdafx.h"
#include "CppUnitTest.h"
#include "header.h"
#include <fstream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitestOOP
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Sum_Diagonal)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\inDiagonal.txt");
			
			type * test = new diagonal;
			test->InData(fin);
			int sum = test->SumOfElements(test);

			Assert::AreEqual(15, sum);
		}

		TEST_METHOD(Sum_Matrix)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\inMatrix.txt");

			type * test = new matrix;
			test->InData(fin);
			int sum = test->SumOfElements(test);

			Assert::AreEqual(10, sum);		
		}

		TEST_METHOD(Sum_Triagonal)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\inTriagonal.txt");

			type * test = new triagonal;
			test->InData(fin);
			int sum = test->SumOfElements(test);

			Assert::AreEqual(6, sum);
		}


		TEST_METHOD(Input_Diagonal)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\inDiagonal.txt");
		
			type * test = new diagonal;
			test->InData(fin);
			int actual[3] = {4,5,6};
			int expected[3];
			test->SetMass(expected);

			Assert::AreEqual(actual[0], expected[0]);
			Assert::AreEqual(actual[1], expected[1]);
			Assert::AreEqual(actual[2], expected[2]);
		}

		TEST_METHOD(Input_Matrix)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\inMatrix.txt");


			type * test = new matrix;
			test->InData(fin);
			int actual[4] = { 1,2,3,4 };
			int expected[4];
			test->SetMass(expected);

			Assert::AreEqual(actual[0], expected[0]);
			Assert::AreEqual(actual[1], expected[1]);
			Assert::AreEqual(actual[2], expected[2]);
			Assert::AreEqual(actual[3], expected[3]);

		}

		TEST_METHOD(Input_Triagonal)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\inTriagonal.txt");

			type * test = new triagonal;
			test->InData(fin);
			int actual[3] = { 1,2,3};
			int expected[3];
			test->SetMass(expected);

			Assert::AreEqual(actual[0], expected[0]);
			Assert::AreEqual(actual[1], expected[1]);
			Assert::AreEqual(actual[2], expected[2]);
		}

		TEST_METHOD(Input_Type)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\input_Type.txt");
			ofstream ofst("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output_Type(test).txt");

			container test;
			test.current = NULL;
			test.current = type::In(fin, test.current);
			test.lenplus();
			test.Out(ofst);
			ofst.close();

			ifstream fin1("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output_Type(test).txt");
			ifstream fin2("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output_Type(correct).txt");
			string expected;
			getline(fin1, expected, '\0');
			string actual;
			getline(fin2, actual, '\0');

			Assert::AreEqual(actual, expected);
		}



		TEST_METHOD(Input_Output_container)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\input.txt");
			ofstream ofst("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output_test.txt");

			container test;
			test.In(fin);
			test.Out(ofst);
			ofst.close();

			ifstream fin1("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output_test.txt");
			ifstream fin2("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output_correct.txt");
			string expected;
			getline(fin1, expected, '\0');
			string actual;
			getline(fin2, actual, '\0');

			Assert::AreEqual(actual, expected);
		}

		TEST_METHOD(Output_Type)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\input_Type.txt");
			ofstream ofst("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output_Type(test).txt");

			container test;
			test.current = NULL;
			test.In(fin);
			test.current->Out(ofst);
			ofst.close();

			ifstream fin1("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output_Type(test).txt");
			ifstream fin2("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output_Type_Out(correct).txt");
			string expected;
			getline(fin1, expected, '\0');
			string actual;
			getline(fin2, actual, '\0');

			Assert::AreEqual(actual, expected);
			
		}

		TEST_METHOD(Output_Diagonal)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\inDiagonal.txt");
			ofstream ofst("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\outDiagonal(Test).txt");


			type * test = new diagonal;
			test->InData(fin);
			test->Out(ofst);
			ofst.close();

			ifstream fin1("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\outDiagonal(Test).txt");
			ifstream fin2("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\outDiagonal(Correct).txt");
			string expected;
			getline(fin1, expected, '\0');
			string actual;
			getline(fin2, actual, '\0');

			Assert::AreEqual(actual, expected);
		}

		TEST_METHOD(Output_Matrix)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\inMatrix.txt");
			ofstream ofst("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\outMatrix(Test).txt");


			type * test = new matrix;
			test->InData(fin);
			test->Out(ofst);
			ofst.close();

			ifstream fin1("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\outMatrix(Test).txt");
			ifstream fin2("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\outMatrix(Correct).txt");
			string expected;
			getline(fin1, expected, '\0');
			string actual;
			getline(fin2, actual, '\0');

			Assert::AreEqual(actual, expected);
		}

		TEST_METHOD(Output_Triagonal)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\inTriagonal.txt");
			ofstream ofst("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\outTriagonal(Test).txt");


			type * test = new triagonal;
			test->InData(fin);
			test->Out(ofst);
			ofst.close();

			ifstream fin1("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\outTriagonal(Test).txt");
			ifstream fin2("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\outTriagonal(Correct).txt");
			string expected;
			getline(fin1, expected, '\0');
			string actual;
			getline(fin2, actual, '\0');

			Assert::AreEqual(actual, expected);
		}


		TEST_METHOD(Filtred_Out)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\input.txt");
			ofstream ofst("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output(OnlyDiagonal-test).txt");

			container test;
			test.In(fin);
			test.FiltredOut(ofst);
			ofst.close();

			ifstream fin1("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output(OnlyDiagonal-test).txt");
			ifstream fin2("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output(OnlyDiagonal-correct).txt");
			string expected;
			getline(fin1, expected, '\0');
			string actual;
			getline(fin2, actual, '\0');

			Assert::AreEqual(actual, expected);
		}

		TEST_METHOD(Sorting)
		{
			ifstream fin("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\input.txt");
			ofstream ofst("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output(Sorted_test).txt");

			container test;
			test.In(fin);
			test.Sorting();
			test.Out(ofst);
			ofst.close();

			ifstream fin1("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output(Sorted_test).txt");
			ifstream fin2("D:\\repositories\\techprog(oop)serverversion\\techprog(oop)serverversion\\unitest(oop)\\Text_Files\\output(Sorted_correct).txt");
			string expected;
			getline(fin1, expected, '\0');
			string actual;
			getline(fin2, actual, '\0');

			Assert::AreEqual(actual, expected);
		}
				
	};
}
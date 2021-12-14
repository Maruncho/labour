
#include <iostream>
#include "Matrix11.h"
#include "MatrixIO11.h"
#include <cmath>
#include <iomanip>
#include <complex>
#include <numeric>

using namespace Numeric_lib;

int main()
{
	
	std::cout << "char: " << sizeof(char) << '\n';
	std::cout << "int: " << sizeof(int) << '\n';
	std::cout << "long: " << sizeof(long) << '\n';
	std::cout << "float: " << sizeof(float) << '\n';
	std::cout << "double: " << sizeof(double) << '\n';
	std::cout << "int*: " << sizeof(int*) << '\n';
	std::cout << "double*: " << sizeof(double*) << '\n';
	

	
	std::cout << "Matrix<int> a(10): " << sizeof(Matrix<int>(10)) << '\n';
	std::cout << "Matrix<int> b(100): " << sizeof(Matrix<int>(100)) << '\n';
	std::cout << "Matrix<double> c(10): " << sizeof(Matrix<double>(10)) << '\n';
	std::cout << "Matrix<int,2> d(10,10): " << sizeof(Matrix<int, 2>(10, 10)) << '\n';
	std::cout << "Matrix<int,3> e(10,10,10): " << sizeof(Matrix<int,3>(10, 10, 10)) << '\n';
	

	
	std::cout << "Matrix<int> a(10): " << Matrix<int>(10).size() << '\n';
	std::cout << "Matrix<int> b(100): " << Matrix<int>(100).size() << '\n';
	std::cout << "Matrix<double> c(10): " << Matrix<double>(10).size() << '\n';
	std::cout << "Matrix<int,2> d(10,10): " << Matrix<int, 2>(10, 10).size() << '\n';
	std::cout << "Matrix<int,3> e(10,10,10): " << Matrix<int, 3>(10, 10, 10).size() << '\n';
	

	std::cout << "\nEnter a number:";
	int x;
	std::cin >> x;
	if(x<0)
		std::cout << "no sqrt" << '\n';
	else
		std::cout << "it's square root is: " << sqrt(x) << '\n';
	
	std::cout << "\nEnter 10 floating point numbers:";
	
	const int entries = 10;

	Matrix<double> md(entries);
	for (int i = 0; i < entries; ++i)
		std::cin >> md[i];

	std::cout << "\nresult: " << md << '\n';
	
	std::cout << "Enter the dimensions for the table: ";


	int m, n;
	std::cin >> m >> n;
	std::cout << '\n';

	Matrix<double, 2> mult_table(m, n);

	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			mult_table(i, j) = i == 0 || j == 0 ? i + j : i * j;

	//std::cout << mult_table << '\n'; // ugly
	for (int i = 0; i < mult_table.dim1(); ++i) {
		for (int j = 0; j < mult_table.dim2(); ++j)
			std::cout << std::setw(5) << mult_table(i, j);
		std::cout << '\n';
	}
	
	std::cout << "\nEnter 10 complex numbers:\n";


	Matrix<std::complex<double>> mcd(10);
	for (int i = 0; i < mcd.size(); ++i) {
		std::cin >> mcd[i];
	}

	std::cout << "Total: "
		<< std::accumulate(mcd.data(), mcd.data() + mcd.size(),
			std::complex<double>{})
		<< '\n';


	std::cout << "Enter 6 ints for a 2x3 Matrix:\n";


	Matrix<int, 2> mm(2, 3);
	for (int i = 0; i < mm.dim1(); ++i)
		for (int j = 0; j < mm.dim2(); ++j)
			std::cin >> mm[i][j];

	std::cout << mm << '\n';
	
}


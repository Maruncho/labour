
#include <iostream>
#include <vector>
#include <stdexcept>

//4
void print_array10(std::ostream& os, int* a) {
	for (int i = 0; i < 10; i++) {
		os << a[i] << ' ';
	}
	os << '\n';
}
//7
void print_array(std::ostream& os, int* a, int n) {
	for (int i = 0; i < n; i++) {
		os << a[i] << ' ';
	}
	os << '\n';
}
//10
void print_vector(std::ostream& os, const std::vector<int>& v) {
	for (int x : v)
		os << x << ' ';
	os << '\n';
}

int main()
{
	// 1-3
	int* p = new int[10];
	for (int i = 0; i < 10; i++) {
		std::cout << p[i] << ' ';
	}
	std::cout << '\n';
	delete[] p; //9

	//5
	int* a = new int[10];
	for (int i = 0; i < 10; i++) {
		a[i] = 100+i;
	}
	print_array10(std::cout, a);
	delete[] a; //9

	//6
	int* b = new int[11];
	for (int i = 0; i < 11; i++) {
		b[i] = 100 + i;
	}
	print_array(std::cout, b, 11);
	delete[] b; //9

	//8
	int* c = new int[20];
	for (int i = 0; i < 20; i++) {
		c[i] = 100 + i;
	}
	print_array(std::cout, c, 20);
	delete[] c; //9

	std::cout << "--------------------------------\n";

	//10 5
	std::vector<int> v1;
	for (int i = 0; i < 10; i++) {
		v1.push_back(100+i);
	}
	print_vector(std::cout, v1);

	//10 6
	std::vector<int> v2;
	for (int i = 0; i < 11; i++) {
		v2.push_back(100 + i);
	}
	print_vector(std::cout, v2);

	//10 8
	std::vector<int> v3;
	for (int i = 0; i < 20; i++) {
		v3.push_back(100 + i);
	}
	print_vector(std::cout, v3);
}

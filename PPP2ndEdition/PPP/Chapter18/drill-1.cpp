
#include <iostream>

int fac(int n) { return n > 1 ? n * fac(n - 1) : 1; }


//1
int ga[10]{ 2,4,8,16,32,64,128,256,512,1024 };

void f(int a[], int n) {
	//a
	int la[10];
	//b
	for (int i = 0; i < 10; i++) la[i] = ga[i]; //b
	//c
	for (int i = 0; i < 10; i++) std::cout << la[i] << ' ';
	std::cout << '\n';
	//d
	int* p = new int[n];
	//e
	for (int i = 0; i < n; i++) p[i] = a[i];
	//f
	for (int i = 0; i < n; i++) std::cout << p[i] << ' ';
	std::cout << '\n';
	//g
	delete[] p;
	//bonus
	std::cout << 'e' << 'n' << 'd' << '\n';
}

int main() 
{
	//a
	f(ga, 10);
	//b
	int aa[10];
	for (int i = 0; i < 10; i++) aa[i] = fac(i + 1);
	//c
	f(aa, 10);
}
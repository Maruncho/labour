
#include <vector>
#include <iostream>

int fac(int n) { return n > 1 ? n * fac(n - 1) : 1; }

std::vector<int> gv = { 2,4,8,16,32,64,128,256,512,1024 };

void f(std::vector<int> v) {
	//a
	std::vector<int> lv(v.size());
	//b
	lv = gv;
	//c
	for (int i = 0; i < lv.size(); i++) std::cout << lv[i] << ' ';
	std::cout << '\n';
	//d
	std::vector<int>lv2 = v;
	//e
	for (int i = 0; i < lv2.size(); i++) std::cout << lv2[i] << ' ';
	std::cout << '\n';
	//bonus
	std::cout << 'e' << 'n' << 'd' << '\n';
}

int main()
{
	//a
	f(gv);
	//b
	std::vector<int> vv(10);
	for (int i = 0; i < vv.size(); i++) vv[i] = fac(i + 1);
	//c
	f(vv);
}
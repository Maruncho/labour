
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <memory>

template<typename C>
void print_contents(const C& c, const std::string& s = "")
{
	std::cout << s << '\t';
	for (auto& a : c)
		std::cout << a << ' ';
	std::cout << '\n';
}

template<typename C>
void inc_contents(C& c, int n = 1)
{
	for (auto& a : c)
		a += n;
}

template<typename Iter1, typename Iter2>
// requires Input_iterator<Iter1>() && Output_iterator<Iter2>()
Iter2 mycopy(Iter1 f1, Iter1 e1, Iter2 f2)
{
	for (Iter1 p = f1; p != e1; ++p)
		*f2++ = *p;
	return f2;
}

int main() {

	int a1[] = { 0,1,2,3,4,5,6,7,8,9 };
	std::vector<int> v1 = { 0,1,2,3,4,5,6,7,8,9 };
	std::list<int> l1 = { 0,1,2,3,4,5,6,7,8,9 };

	int a2[10];
	std::copy(a1, a1 + 10, a2);
	std::vector<int> v2 = v1;
	std::list<int> l2 = l1;

	inc_contents(a2,2);
	inc_contents(v2,3);
	inc_contents(l2,5);

	mycopy(a2, a2 + 10, v2.begin());
	mycopy(l2.begin(), l2.end(), a2);
	
	std::vector<int>::iterator vit = std::find(v2.begin(), v2.end(), 3);
	if (vit == v2.end()) std::cout << "Not found!\n";
	else std::cout << std::distance(v2.begin(), vit) << '\n';

	std::list<int>::iterator lit = std::find(l2.begin(), l2.end(), 16);
	if (lit == l2.end()) std::cout << "Not found!\n";
	else std::cout << std::distance(l2.begin(), lit) << '\n';


}
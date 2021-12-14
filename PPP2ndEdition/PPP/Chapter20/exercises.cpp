
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

template<typename Iter>
Iter high(Iter first, Iter last) {
	Iter high = first;
	for(Iter p = first; p != last; p++)
		if (*high < *p)
			high = p;
	return high;
}

int main() 
{
	//exercise 7
	
	std::vector<std::string> v = {"abc", "ccca", "c", "ab", "ac", "bca", "ccba", "b", "a", "sca", "bca"};
	auto var = high(v.begin(), v.end());
	if (var == v.end())
		std::cerr << "Error!?";
	else
		std::cout << *var;
}

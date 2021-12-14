
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <set>
#include <list>

struct Item {
	std::string name;
	int iid;
	double value;
};

std::istream& operator>>(std::istream& is, Item& item) {
	return is >> item.name >> item.iid >> item.value;
}

std::ostream& operator<<(std::ostream& os, const Item& item) {
	return os << item.name << '\t' << item.iid << '\t' << item.value << '\n';
}

struct Sort_name {
	bool operator()(Item first, Item second) {
		return first.name < second.name;
	}
};

struct Sort_iid {
	bool operator()(Item first, Item second) {
		return first.iid < second.iid;
	}
};

struct Sort_value {
	bool operator()(Item first, Item second) {
		return first.value > second.value;
	}
};

struct Find_by_name {
	std::string name;
	Find_by_name(std::string n) : name{ n } {}
	bool operator()(Item i) {
		return i.name == name;
	}
};

struct Find_by_iid {
	int iid;
	Find_by_iid(int n) : iid{ n } {}
	bool operator()(Item i) {
		return i.iid == iid;
	}
};

int main() try
{
	std::ifstream vis{ "drill1.txt" };

	std::istream_iterator<Item> vii{ vis };
	std::istream_iterator<Item> veos;


	std::vector<Item> vec = { vii,veos };
	std::sort(vec.begin(), vec.end(), Sort_name());
	std::sort(vec.begin(), vec.end(), Sort_iid());
	std::sort(vec.begin(), vec.end(), Sort_value());

	Item tmp = { "horseshoe",99,12.34 };
	vec.insert(vec.begin(),tmp);
	tmp = { "Canon S400",9988,499.95 };
	vec.insert(vec.begin(), tmp);
	std::sort(vec.begin(), vec.end(), Sort_value());

	vec.erase(find_if(vec.begin(), vec.end(), Find_by_name("horseshoe")));
	vec.erase(find_if(vec.begin(), vec.end(), Find_by_name("Canon S400")));
	vec.erase(find_if(vec.begin(), vec.end(), Find_by_iid(2011)));
	vec.erase(find_if(vec.begin(), vec.end(), Find_by_iid(83)));


	for (auto x : vec)
		std::cout << x;

	//----------------------------------------------------------------------
	std::cout << "\nList Version:\n";

	std::ifstream lis{ "drill1.txt" };

	std::istream_iterator<Item> lii{ lis };
	std::istream_iterator<Item> leos;
	
	std::list<Item> li{ lii,leos };
	li.sort(Sort_name());
	li.sort(Sort_iid());
	li.sort(Sort_value());
	Item temp = { "horseshoe",99,12.34 };
	li.insert(li.begin(), temp);
	temp = { "Canon S400",9988,499.95 };
	li.insert(li.begin(), temp);
	li.sort(Sort_value());
	li.erase(std::find_if(li.begin(), li.end(), Find_by_name("horseshoe")));
	li.erase(std::find_if(li.begin(), li.end(), Find_by_name("Canon S400")));
	li.erase(std::find_if(li.begin(), li.end(), Find_by_iid(2011)));
	li.erase(std::find_if(li.begin(), li.end(), Find_by_iid(83)));

	for (auto x : li)
		std::cout << x;
}
catch (std::exception& e) {
	std::cerr << e.what();
}
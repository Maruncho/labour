
#include <iostream>
#include <map>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <numeric>


void fill_map(std::map<std::string, int>& mp, int limit) {
	std::string stmp;
	int itmp;
	int count = 0;
	std::cout << "Type in pairs: string int\n";
	while (count != limit && std::cin >> stmp >> itmp) {
		mp[stmp] = itmp;
		count++;
	}
}

int map_sum(int init, const std::pair<std::string, int>& p) {
	return init + p.second;
}

int main() try {
	std::map<std::string, int> msi;

	msi["a"] = 0;
	msi["b"] = 1;
	msi["c"] = 2;
	msi["d"] = 3;
	msi["e"] = 4;
	msi["f"] = 5;
	msi["g"] = 6;
	msi["h"] = 7;
	msi["i"] = 8;
	msi["j"] = 9;
	
	msi.erase("a");
	msi.erase("b");
	msi.erase("c");
	msi.erase("d");
	msi.erase("e");
	msi.erase("f");
	msi.erase("g");
	msi.erase("h");
	msi.erase("i");
	msi.erase("j");
	
	fill_map(msi,10);

	for (auto x : msi)
		std::cout << x.first << ' ' << x.second << '\n';
	int x = 0;
	x = std::accumulate(msi.begin(), msi.end(), x, map_sum);
	std::cout << '\n' << x << '\n';

	std::map<int, std::string> mis;

	for (auto x : msi)
		mis[x.second] = x.first;
	for (auto x : mis)
		std::cout << x.first << ' ' << x.second << '\n';

}
catch (std::exception& except)
{
	except.what();
	return 1;
}

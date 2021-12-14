
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <functional>

struct Less_than_mean {
	double mean;
	Less_than_mean(double m) : mean{m} {}
	bool operator()(double num) {
		return num < mean;
	}
};

int main() {
	std::ifstream is{ "drill3.txt" };
	std::istream_iterator<double> iit{ is };
	std::istream_iterator<double> eos;

	std::vector<double> vd{ iit,eos };

	std::vector<int> vi(vd.size());
	copy(vd.begin(), vd.end(), vi.begin());

	for (int i = 0; i < vd.size(); i++)
		std::cout << vd[i] << '\t' << vi[i] << '\n';

	double y = std::accumulate(vd.begin(), vd.end(), 0.0);
	std::cout << '\n' << y << '\n';

	double x = 0.0;
	x = std::inner_product(vd.begin(), vd.end(), vi.begin(), x, std::plus<double>(), std::minus<double>());
	std::cout << '\n' << x << '\n' << '\n';

	std::reverse(vd.begin(), vd.end());
	for (auto x : vd)
		std::cout << x << '\n';

	double mean = y / vd.size();
	std::cout << '\n' << mean << '\n'<<'\n';
	
	std::vector<double> vd2(vd.size());
	auto it = std::copy_if(vd.begin(), vd.end(), vd2.begin(), Less_than_mean(mean));
	vd2.resize(std::distance(vd2.begin(), it));
	std::sort(vd.begin(), vd.end());
	for (auto x : vd)
		std::cout << x << '\n';

}
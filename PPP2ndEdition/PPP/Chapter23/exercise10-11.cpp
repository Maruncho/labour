
#include <regex>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

int from_string(const std::string& s){
	std::istringstream is{ s };
	int t;
	is >> t;
	return t;

}

std::string to_string(int i) {
	std::ostringstream os{};
	os << i;
	return os.str();
}

int main()
{
	std::ifstream in{ "table.txt" };
	if (!in) std::cerr << "no input file\n";

	std::string line;
	int lineno = 0;

	std::regex header{R"(^[\w ]+(	[\w ]+)*$)"};
	std::regex row{R"(^[\w ]+(	\d+)(	\d+)(	\d+)$)"};
	std::regex row_10{R"((^\d+)?[\w ]+(	\d+)(	\d+)(	\d+)$)"};

	if (std::getline(in, line)) {
		std::smatch matches;
		if (!std::regex_match(line, matches, header))
			std::cerr << "no header";
	}

	std::map<std::string, int> classes;

	while (std::getline(in, line)) {
		++lineno;
		std::smatch matches;
		if (!std::regex_match(line, matches, row_10))
			std::cerr << "bad line" << lineno;

		if (matches[1].matched)
			classes[matches[1]] += from_string(matches[4]);
	}

	for (auto x : classes)
		std::cout << x.first << ": " << x.second << " (students in total)" << '\n';

	int less = 0;
	int more = 0;

	for (int i = 0; i < classes.size()-1; i++) {
		if (classes[to_string(i)] > classes[to_string(i + 1)])
			more++;
		else if (classes[to_string(i)] < classes[to_string(i + 1)])
			less++;
	}
	if (more > less)
		std::cout << "increasing in general\n";
	else if (more < less)
		std::cout << "decreasing in general\n";
	else
		std::cout << "same in general\n";

}

#include <regex>
#include <iostream>
#include <string>
#include <fstream>

int main()
{
	std::ifstream in{ "drill_input.txt" };
	if (!in) std::cerr << "nofile\n";

	std::cout << "Format:\n LineNumber: PostCode\n\t: ZIPCode (if any)\n\n";

	std::regex pat{ R"(\w{2}\s*\d{5}(-\d{4})?)" };
	int lineno = 0;
	for (std::string line; std::getline(in, line); ) {
		++lineno;
		std::smatch matches;
		if (std::regex_search(line, matches, pat)) {
			std::cout << lineno << ": " << matches[0] << '\n';
			if (matches[1].matched)
				std::cout << "\t: " << matches[1] << '\n';
		}
	}
}
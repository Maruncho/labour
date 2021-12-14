
import <string>;
import <iostream>;
import <vector>;

import ParameterExtract;
import Combinations;
import Shared;

using namespace ParameterExtract;
using namespace Combinations;
using namespace Shared;

struct Tests
{
	std::string test = "param1, params2, jisdf334re, 984.0ur,  =-po98.2,";
	std::string test1 = "param1, para2asaasf, asf33.1aa,,,,,, 42.0aaaaaaaafug, not50.69lmao,    let'sDo6Too,,,,,,,,,,   ,,,, , , ,";
	std::string test2 = "114514,214541,3413514,41435,545345,654456,7415645,877889,912231,112430,13451,1132,1135413";
	std::string test3 = "0,222,1,54,89,01,22,43,1,44,21,54";
	std::string test4 = "7,33,1,5,22,15,83,101,434,1101,10";
	std::string test5 = "22,1,43,17,9,17,32,16,21";
	std::string test6 = "1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,,1,,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1";
};

int main() try
{
	//BEWARE: THIS CLASS IS...IS... JUST UNBREAKABLE, TRUST ME!
	ParameterExtractor parExtractor{};
	std::string ws = ",";
	parExtractor.setWhiteSpace(ws = ",");
	parExtractor.setDistanceFromPoint(1);
	parExtractor.setLimit(50);

	//Tests tests;
	//std::vector<int> vec = parExtractor.extractIntegers(tests.test2);

	std::cout << "Let your cat walk on the keyboard, then put some numbers and \n'whitespace' characters here and there, if there aren't some already:\n";
	//std::cout << "Enter parameters, separated by ("<<ws<<"). Each parameter must have \none number. If there are more than one, first is selected:\n";
	std::vector<int> vec = parExtractor.extractIntegers(std::cin);

	//Combo stuff
	Combinetron9000 combo{ vec };
	combo.Sorted();
	combo.printCombinations(std::cout);
	printVector(std::cout, combo.longestAscendingCombination(), "Longest Ascending Order Combination:");
}
catch (ParameterExtractor::PExtractError e)
{
	std::cerr << "EXTRACTOR EXCEPTION: " << e.what() << '\n';
	return 1;
}
catch (Combinetron9000::Comb9000Error e)
{
	std::cerr << "Combinetron9000 THREATENS YOU: " << e.what() << '\n';
	return 1;
}
catch (std::exception e)
{
	std::cerr << "EXCEPTION: " << e.what() << '\n';
	return 1;
}
catch (...)
{
	std::cerr << "UNKNOWN ERROR?!?!?!?!?!!?" << '\n';
	return 2;
}
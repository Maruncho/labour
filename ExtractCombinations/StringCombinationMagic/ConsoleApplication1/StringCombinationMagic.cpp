
/***********************************
*
*	USE THIS FILE IF YOUR COMPILER
*	DOES NOT SUPPORT C++20 MODULES
*
***********************************/


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>


template<class T>
std::string toString(T t)
{
	std::ostringstream os;
	os << t;
	return os.str();
}

//used to compare vector<int>s
//warning: does not check for == (requires unique elements)
struct Vector_int_compare {
	bool operator()(std::vector<int> v1, std::vector<int> v2) const
	{
		for (int i = 0; i < v1.size(); i++) {
			if (i == v2.size()) return false; // v2<v1
			int n1 = v1[i];
			int n2 = v2[i];
			if (n1 < n2) return true; // v1<v2
			if (n2 < n1) return false; // v2<v1
		}
		//if (v1.size() == v2.size()) return false; // v1==v2

		return true; // v1 < v2 (fewer characters in v1)
	}
};

//ignore characters until digit
void skip_to_int(std::istream& is)
{
	//read characters until a digit is found
	for (char c; is >> c;) {
		if (isdigit(c)) {
			is.putback(c); //return the digit to the stream
			return;
		}
	}
}

template<class T>
void printVector(std::ostream& os, std::vector<T> a, std::string message = "")
{
	os << message << '\n';
	for (const T& x : a)
		os << x << " -> ";
	os << "DONE" << '\n';
}

//Creates combinations with length == limit, with the numbers from the range [0;max)
//not written by me: https://www.baeldung.com
std::vector<std::vector<int>> generateCombinations(int max, int limit)
{
	std::vector<std::vector<int>> combinations;
	std::vector<int> combination(limit);

	// initialize with lowest lexicographic combination
	for (int i = 0; i < limit; i++) {
		combination[i] = i;
	}

	while (combination[limit - 1] < max) {
		combinations.push_back(combination);

		// generate next combination in lexicographic order
		int t = limit - 1;
		while (t != 0 && combination[t] == max - limit + t) {
			t--;
		}
		combination[t]++;
		for (int i = t + 1; i < limit; i++) {
			combination[i] = combination[i - 1] + 1;
		}
	}

	return combinations;
}

//Combinetron9000------------------------------------------
class Combinetron9000 {
	//Description
	/*
		 * WORKING PRINCIPLES:
		 * 1. Generate combinations of indices e.g. 1,3,0,2,4,6,5 ; 1,4,6 ...
		 * 2. Use these indices to map the parameters, received at construction
		 *
		 *    e.g 622, 42, 21, 43, 5, 1, 132 (parameters)
		 *    are mapped to: (according to the indices above):
		 *    42, 43, 622, 21, 5, 132, 1 ; 42, 5, 132 ...
		 *
		 * Currently, it supports "int to int" mapping only
		 * Currently, it supports only up to 31 parameters
		 */
public:
	Combinetron9000(std::vector<int> cont);

	long long int getCombinationCount() { return comb_count; }

	std::vector<std::vector<int>> Sorted() { return SortedCombinationly(); } //default
	std::vector<std::vector<int>> SortedCombinationly()
	{
		generateSortedCombinationly(); //generate indices
		mapCombinations();	//map parameters to indices
		return mapped_combs; //caller may want a copy
	}
	std::vector<std::vector<int>> SortedBitwisely()
	{
		generateSortedBitwisely(); //generate indices
		mapCombinations(); //map parameters to indices
		return mapped_combs; //caller may want a copy
	}

	std::vector<int> longestAscendingCombination(); // *of current combinations

	void printCombinations(std::ostream&); //print current combinations

	//Exception class
	class Comb9000Error : public std::exception {
	public:
		using std::exception::exception;
	};

private:
	std::vector<int> parameters;//the "to be mapped" values
	int pars_size;				//parameteres.size()
	long long int comb_count = 0;	// combs.size() 
	std::vector<std::vector<int>> combs;	/*combinations of indices
											to map the parameters to*/
	std::vector<std::vector<int>> mapped_combs; //to store most recent mapping

	void generateSortedCombinationly();//generate and sort in ascending order (using sub-combinations)
	void generateSortedBitwisely();	//generate and sort in ascending order (using bitwise)

	void mapCombinations(); //map parameters to combinations
};

Combinetron9000::Combinetron9000(std::vector<int> cont)
{
	if (cont.empty()) throw Comb9000Error{ "Empty parameter list (size == 0)" };
	if (cont.size() > 31) throw Comb9000Error{ "Doesn't support more than 31 parameters" };
	pars_size = cont.size();

	parameters.resize(pars_size); //resize in advance, for efficiency
	std::move(cont.begin(), cont.end(), parameters.begin());
}

void Combinetron9000::generateSortedCombinationly()
{
	combs.clear(); //clear old results
	comb_count = pow(2, pars_size) - 1; //the size can be mathematically deduced

	//generate combinations for all possible lengths ( for each length in [1;size) )
	//the combinations here will be used as indices
	for (int i = 1; i <= pars_size; i++) {
		std::vector<std::vector<int>> temp = generateCombinations(pars_size, i);
		for (const std::vector<int> x : temp)
			combs.push_back(x);
	}
	//sort, of course
	std::sort(combs.begin(), combs.end(), Vector_int_compare());
}

void Combinetron9000::generateSortedBitwisely()
{
	combs.clear(); //clear old results
	comb_count = pow(2, pars_size) - 1; //the size can be mathematically deduced

	int n = 0;	//used to generate all the combinations

	//generate vectors of indices to map the parameters to
	for (int i = 0; i < comb_count; i++) {
		n++;
		int index = 0; //each binary digit represents index
		std::vector<int> combination;

		//every binary number yields one combination
		for (int j = n; j;) //stops when 'j>>1 == 0' (every digit is checked) 
		{
			if (j & 1) combination.push_back(index); //'1' means to put index
			index++;			//switch to next index
			j = j >> 1;			//prepare next digit for the next iteration
		}
		combs.push_back(combination); //add the combination
	}
	//sort, of course
	std::sort(combs.begin(), combs.end(), Vector_int_compare());
}

void Combinetron9000::mapCombinations()
{
	mapped_combs.clear(); //it's time for the next generation to shine
	for (const std::vector<int>& indices : combs) {
		std::vector<int> temp;
		for (int i = 0; i < indices.size(); i++)
			temp.push_back(parameters[indices[i]]); //map parameter to index
		mapped_combs.push_back(temp);
	}
}

void Combinetron9000::printCombinations(std::ostream& os)
{
	//Format:

	//////////////
	//combCount
	//"comb1"
	//...
	//"combN"
	//combCount
	//////////////

	if (combs.empty()) throw Comb9000Error{ "Can't print when there are no combinations generated" };
	os << "//////////////////////////////////////\n"
		<< "Number of combinations: " << comb_count << '\n';
	for (const auto& vec : mapped_combs) {
		for (const auto& num : vec)
			os << num << ' ';
		os << '\n';
	}
	os << "Number of combinations: " << comb_count << '\n';
	os << "//////////////////////////////////////\n";
}

std::vector<int> Combinetron9000::longestAscendingCombination()
{
	if (combs.empty()) throw Comb9000Error{ "longestAscendingCombination() requires an already generated combination" };

	std::vector<std::vector<int>> canditates; //store ordered combinations

	//just check every single combination, no smart business
	for (std::vector<int> c : mapped_combs) {
		int prev = 0; //i-1
		bool error = 0; //to indicate unordered-ness

		//compare each combination's numbers
		for (int i = 1; i < c.size(); i++) {
			if (c[prev] >= c[i]) {
				error = true; //not ordered
				break;
			}
			prev++;
		}
		if (!error) //ordered?
			canditates.push_back(c);
	}
	if (canditates.empty()) return mapped_combs[0]; //if none, then return the first

	//find the lengthiest
	std::vector<int> winner = canditates[0];
	for (auto x : canditates)
		if (x.size() > winner.size())
			winner = x;
	return winner;
}
//-------------------------------------------------------------

//ParameterExtractor-------------------------------------------
class ParameterExtractor {
	//Descrition
	/*
		 * WORKING PRINCIPLES:
		 *    A parameter is string of characters, with an optional length of 'limit'.
		 *    Parameters are separated by the whitespace characters, stored in 'white'.
		 *	  Input is terminated by '\n' (newline / pressing enter)
		 *
		 *    Integer extraction details:
		 *      Currently, we doesn't support multi-integer parameters, that is, we
		 *      extract the first found, ignoring everything after it
		 *
		 *      'distanceFromPoint' is used to determine how many digits, starting from
		 *      the floating point, we should ignore
		 *
		 *          e.g. when 'distanceFromPoint' == 1, from 12.44, we ignore 2.4 => 1___4
		 *
		 *			WARNING: RoughHandlePoints removes everything after the first number(above that is 1).
		 *					 If you don't want this, implement another similar method
		 *
		 *    Floating point extraction details:
		 *    (Currently, not implemented.)
		 *
		 *      'distanceFromPoint' can also be used to determine how many digits, starting
		 *      from the floating point, we should extract
		 */
public:
	ParameterExtractor() : white{ "" }, distanceFromPoint{ 0 }, limit{ 0 } {}

	void setWhiteSpace(std::string ws);
	void setDistanceFromPoint(int dis);
	void setLimit(int n) { if (n < 0) throw PExtractError{ "limit cannot be negative value" }; limit = n; }

	bool isWhiteSpace(char ch) const;		//is ch in the whitespace set?


	std::vector<int> extractIntegers(std::string line);		// separateParameters()
	std::vector<int> extractIntegers(std::istream& is);		// and extract integers

	//Exception class
	class PExtractError : public std::exception {
	public:
		using std::exception::exception;
	};

private:
	std::string white;		//characters considered 'whitespace'
	int distanceFromPoint;	//how many digits to consider next to a floating point; 0 == all/undefined
	int limit;				//limit maximum parameter size; 0 == undefined

	void editWhiteSpace(std::string& raw); //change the selected characters to \s (' ')
	std::vector<std::string> separateParameters(std::string raw); //divide the input
	bool roughHandlePoints(std::string& str); //deals with points; returns true if string becomes empty
};

void ParameterExtractor::setWhiteSpace(std::string ws)
{
	if (ws.find('.') != std::string::npos) // is there '.' in ws
		if (distanceFromPoint != 0) throw PExtractError{ "You can't have '.' as whitespace if distanceFromPoint is not 0" };
	white = ws;
}

void ParameterExtractor::setDistanceFromPoint(int dis)
{
	if (dis < 0) throw PExtractError{ "disFromPoint cannot be negative value" };
	distanceFromPoint = dis;

	//check if '.' is in whitespace, it's not a random point if disFromPoint != 0
	if (white.find('.') != std::string::npos) // is there '.' in white
		if (distanceFromPoint != 0) throw PExtractError{ "You can't have '.' as whitespace if distanceFromPoint is not 0" };


}

bool ParameterExtractor::isWhiteSpace(char ch) const
{
	for (char ws : white)
		if (ch == ws) return true;
	return false;
}

void ParameterExtractor::editWhiteSpace(std::string& raw)
{
	for (char& x : raw)
		if (isWhiteSpace(x))
			x = ' ';

}

bool ParameterExtractor::roughHandlePoints(std::string& str)
{
	if (distanceFromPoint) { //first check if points bother the user
		while (true) {
			int pos = str.find('.');
			if (pos != std::string::npos) {  //if '.' is found
				str.erase(pos, 1); //delete point; pos+1 is the new pos

				if (isdigit(str[pos])) { /*check if the point is 'floating' or just
										   a random one? (if a digit is after it)  */

					//delete the digits behind the point, as requested
					pos -= distanceFromPoint;
					if (pos <= 0) return true; //practically empty
					str.erase(pos); //erase [pos;size)
				}
			}
			else
				return false; //just exit when there are no more points to check
		}
	}
	return false; //point are not a concern
}

std::vector<std::string> ParameterExtractor::separateParameters(std::string line)
{
	//create white space so that the stringstream can '>>' a parameter
	editWhiteSpace(line);

	int index = 0; //to track index for the exception

	std::vector<std::string> vec;
	std::stringstream ss{ line };
	for (std::string str; ss >> str;) {
		if (limit) { // if 0 -> undefined/limitless
			if (str.size() > limit) {
				std::string message = "parameter's size is over the specified limit. Index: " + toString(index);
				throw PExtractError(message.c_str());
			}
		}
		index++;
		//push extracted string
		vec.push_back(str);
	}
	//editWhiteSpace() may leave out ONLY whitespace; it's good to tell the user if this happens
	if (vec.size() == 0) {
		std::string message = "Input consists of only 'whitespace' characters. Selected set: " + white;
		throw PExtractError{ message.c_str() };
	}
	return vec;
}

std::vector<int> ParameterExtractor::extractIntegers(std::string line)
{
	if (line.size() == 0) throw PExtractError("No input :(");

	std::vector<std::string> strv;
	//separete parameters first :)
	strv = separateParameters(line);

	int index = 0; //for exceptions
	std::vector<int> intvec;

	//the extraction
	for (std::string& str : strv) {

		// deal with points
		if (roughHandlePoints(str)) continue; //returns true if string 
											//becomes empty => skip iteration

		std::stringstream ss{ str }; //used to '>>' the int

		long long int number; // long long, because we later check if value > 'int's max size'
		skip_to_int(ss); //skip until we hit an integer
		if (ss.eof()) continue; //we didn't find an integer... NEXT!
		ss >> number; //extract integer

		//check if int overflows
		int numberNew = static_cast<int>(number);
		if (numberNew != number) {
			std::string message = "Integer overflow, value too big. Index: " + toString(index);
			throw PExtractError{ message.c_str() };
		}

		//we don't care if there is something left in the string, we have what we need

		intvec.push_back(numberNew); //finally, add number
		index++;
	}
	if (intvec.size() == 0) throw PExtractError{ "None of the parameters have a number in them" };
	return intvec;
}

std::vector<int> ParameterExtractor::extractIntegers(std::istream& is)
{
	std::string line;
	std::getline(is, line);
	return extractIntegers(line);
}
//-------------------------------------------------------------

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

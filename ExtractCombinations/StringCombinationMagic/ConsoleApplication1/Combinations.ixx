export module Combinations;

import <iostream>;
import <vector>;
import <string>;
import <algorithm>;
import Combinatorics;
import Shared;

using namespace Combinatorics;
using namespace Shared;

namespace Combinations {

	export class Combinetron9000 {
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

		//methods
		void generateSortedCombinationly();//generate and sort in ascending order (using sub-combinations)
		void generateSortedBitwisely();	//generate and sort in ascending order (using bitwise)

		void mapCombinations(); //map parameters to combinations
	};

	/***
				IMPLEMENTATIONS
	*/

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
}
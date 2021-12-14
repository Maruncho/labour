export module Combinatorics;

import <vector>;

namespace Combinatorics
{
	//Creates combinations with length == limit, with the numbers from the range [0;max)
	//not written by me: https://www.baeldung.com
	export std::vector<std::vector<int>> generateCombinations(int max, int limit)
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
}
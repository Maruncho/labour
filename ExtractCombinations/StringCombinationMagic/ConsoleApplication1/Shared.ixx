export module Shared;

import <string>;
import <iostream>;
import <vector>;

namespace Shared
{
	export
	template<class T>
	std::string toString(T t)
	{
		std::ostringstream os;
		os << t;
		return os.str();
	}

	//used to compare vector<int>s
	//warning: does not check for == (requires unique elements)
	export struct Vector_int_compare {
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
	export void skip_to_int(std::istream& is)
	{
		//read characters until a digit is found
		for (char c; is >> c;) {
			if (isdigit(c)) {
				is.putback(c); //return the digit to the stream
				return;
			}
		}
	}
	export
	template<class T>
	void printVector(std::ostream& os, std::vector<T> a, std::string message = "")
	{
		os << message << '\n';
		for (const T& x : a)
			os << x << " -> ";
		os << "DONE" << '\n';
	}

}
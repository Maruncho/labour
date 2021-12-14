export module ParameterExtract;

import <vector>;
import <string>;
import <sstream>;
import <cmath>;
import <algorithm>;
import Shared;

using namespace Shared;

namespace ParameterExtract 
{
	export class ParameterExtractor {
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

		//methods
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
}
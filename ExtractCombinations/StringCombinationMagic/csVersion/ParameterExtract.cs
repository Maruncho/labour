
using System.Text.RegularExpressions;

namespace ParameterExtract
{
    //ParameterExtractor-------------------------------------------
    class ParameterExtractor
    {
        //Description
        /*
		 * WORKING PRINCIPLES:
		 *    A parameter is string of characters, with a optional length of 'limit'.
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

        private string white;          //characters considered 'whitespace'
        private int distanceFromPoint;//how many digits to consider next to a floating point; 0 == all/undefined 
        private int limit;           //limit maximum parameter size; 0 == undefined

        //Exception class
        public class PExtractError : Exception
        {
            public PExtractError(string msg) : base(msg) { }
        }

        //Constructors
        public ParameterExtractor()
        {
            white = "";
            distanceFromPoint = 0;
            limit = 0;
        }

        //public methods
        public int Limit
        {
            get
            {
                return limit;
            }
            set
            {
                if (value < 0) throw new PExtractError("limit cannot be negative value");
                limit = value;
            }
        }
        public int DistanceFromPoint
        {
            get
            {
                return distanceFromPoint;
            }
            set
            {
                if (value < 0) throw new PExtractError("disFromPoint cannot be negative value");
                distanceFromPoint = value;

                //check if '.' is in whitespace, it's not a random point if disFromPoint != 0
                if (white.Contains('.'))
                    if (distanceFromPoint != 0) throw new PExtractError("You can't have '.' as whitespace if distanceFromPoint is not 0");
            }
        }
        public string WhiteSpace
        {
            get
            {
                return white;
            }
            set
            {
                if (value.Contains('.'))
                    if (distanceFromPoint != 0) throw new PExtractError("You can't have '.' as whitespace if distanceFromPoint is not 0");
                white = value;
            }
        }
        public List<int> ExtractIntegers(string line)
        {
            if (line.Length == 0) throw new PExtractError("No input :(");

            List<string> strList = new List<string>();
            //separete parameters first :)
            strList = SeparateParameters(line);

            int index = 0; //for exceptions
            List<int> intList = new List<int>();

            //the extraction
            foreach (string strr in strList)
            {
                //deal with points
                string str = strr; // cannot ref string directly in foreach
                if (RoughHandlePoints(ref str)) continue; /*returns true if string
                                                          becomes empty => skip iteration*/

                //get first number (if there are more, ignore them, get first)
                Regex regex = new Regex("[0-9]+");
                string numStr = regex.Match(str).Value;

                if (numStr != "") //if number found
                {
                    //check for overflow
                    int num;
                    checked
                    {
                        try
                        {
                            num = Int32.Parse(numStr);
                        }
                        catch (OverflowException)
                        {
                            throw new PExtractError($"Integer overflow, value too big (>{int.MaxValue}). Index: {index}");
                        }
                    }
                    intList.Add(num); //finally, add number
                }
                index++;
            }
            if (intList.Count == 0) throw new PExtractError("None of the parameters have a number in them");
            return intList;
        }

        //private methods
        List<string> SeparateParameters(string line)//divide the input
        {
            //separate
            List<String> temp = new List<string>(Regex.Split(line, @$"[{white} ]+")); //split by using our whitespace :)

            List<String> lst = new List<string>(); //filtered list
            //filter empty strings
            foreach (string s in temp)
                if (s != "") lst.Add(s);

            if (lst.Count == 0) //after filtering, it may become empty
                throw new PExtractError($"Input consists of only 'whitespace' characters. Selected set: {white}");

            if (limit != 0) //if 0 -> undefined/limitless
            {
                int index = 0; //for exceptions
                foreach (string par in lst)
                {
                    if (par.Length > limit)
                        throw new PExtractError($"parameter's size is over the specified limit. Index: {index}");
                    index++;
                }
            }
            return lst;
        }
        bool RoughHandlePoints(ref string str) //deals with points; returns true if string becomes empty
        {
            //StringBuilder here is not necessary, I assume. Fix if not so

            if (distanceFromPoint != 0) //first check if points bother the user
            {
                while (true)
                {
                    int pos = str.IndexOf('.');
                    if (pos != -1)
                    {
                        str = str.Remove(pos, 1); //delete point; pos+1 is the new pos

                        if (pos < str.Length && Char.IsDigit(str[pos]))   //check if the point is 'floating' or just
                                                                          //if (pos != 0 && Char.IsDigit(str[pos - 1])) //a random one? (if a digit is after it (and before it, if uncommented))
                        {
                            //delete the digits behind the point, as requested
                            pos -= distanceFromPoint;
                            if (pos <= 0) return true; //practically empty
                            str = str.Remove(pos);
                        }
                    }
                    else
                        return false;   //exit when there are no more points to check
                }
            }
            return false; //points are not a concern
        }
    }
}

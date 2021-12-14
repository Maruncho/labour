namespace Combinations
{
    using Shared;
    //Combintegertron9000------------------------------------------
    public class CombinationMagic
    {
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
         * Currently, in supports only up to 31 parameters
         */
        private List<int> parameters = new List<int>(); //the "to be mapped" values
        private int parsSize;       //parameters.Count
        private long combCount = 0; //Combs.Count
        private List<int[]> combs = new List<int[]>();  /*combinations of indices
                                                          to map the parameters to*/
        private List<int[]> mappedCombs = new List<int[]>(); //to store most recent mapping

        //Exception class
        public class CombMagicError : Exception
        {
            public CombMagicError(string msg) : base(msg) { }
        }

        //Constructors
        public CombinationMagic(List<int> cont)
        {
            if (cont.Count == 0) throw new CombMagicError("Empty parameter list (Count == 0)");
            if (cont.Count > 31) throw new CombMagicError("Doesn't support more than 31 parameters");
            parsSize = cont.Count;
            parameters = cont;
        }

        //Public Methods
        public long CombCount { get; }
        public void PrintCombinations() //print current combination 
        {
            //Format:

            //////////////
            //combCount
            //"comb1"
            //...
            //"combN"
            //combCount
            //////////////

            if (combs.Count == 0) throw new CombMagicError("Can't print when there is no combination generated");
            Console.WriteLine("//////////////////////////////////////");
            Console.WriteLine($"Number of combinations: {combCount}");
            foreach (int[] lst in mappedCombs)
            {
                foreach (int num in lst)
                    Console.Write($"{num} ");
                Console.WriteLine();
            }
            Console.WriteLine($"Number of combinations: {combCount}");
            Console.WriteLine("//////////////////////////////////////");
        }
        public List<int[]> Sorted()//default
        {
            return SortedCombinationly();
        }
        public List<int[]> SortedCombinationly()
        {
            GenerateSortedCombinationly(); //generate indices
            MapCombinations(); //map parameters to indices
            return mappedCombs; //caller may want a copy
        }
        public List<int[]> SortedBitwisely()
        {
            GenerateSortedBitwisely(); //generate indices
            MapCombinations(); //map pararameters to indices
            return mappedCombs; //caller may want a copy
        }
        public int[] LongestAscendingCombination() //*of current combinations
        {
            if (combs.Count == 0) throw new CombMagicError("LongestAscendingCombination() requires an already generated combination");

            List<int[]> candidates = new List<int[]>(); //store ordered combinations

            //just check every single combination, no smart business
            foreach (int[] c in mappedCombs)
            {
                int prev = 0; //i-1
                bool error = false; //to indicate unordered-ness

                //compare each combination's numbers
                for (int i = 1; i < c.Length; i++)
                {
                    if (c[prev] >= c[i])
                    {
                        error = true; //not ordered
                        break;
                    }
                    prev++;
                }
                if (!error) //ordered?
                    candidates.Add(c);
            }
            if (candidates.Count == 0) return mappedCombs[0]; //if none, then it's the first

            //find the lengthiest
            int[] winner = candidates[0];
            foreach (int[] x in candidates)
                if (x.Length > winner.Length)
                    winner = x;
            return winner;
        }

        //Private Methods
        void MapCombinations() //map parameters to combinations 
        {
            mappedCombs.Clear(); //it's time for the next generation to shine
            foreach (int[] indices in combs)
            {
                List<int> temp = new List<int>();
                for (int i = 0; i < indices.Length; i++)
                    temp.Add(parameters[indices[i]]); //map parameter to index
                mappedCombs.Add(temp.ToArray());
            }
        }
        void GenerateSortedCombinationly()//generate and sort in ascending order  (using subcomb-s)
        {
            combs.Clear(); //clear old results
            combCount = (long)(Math.Pow(2, parsSize) - 1); //the size can be mathematically deduced

            //generate combinations for all possible lengths of numbers ( for each length in [1;parsSize) )
            //the combinations here will be used as indices
            for (int i = 1; i <= parsSize; i++)
            {
                List<int[]> temp = Combinatorics.GenerateCombinations(parsSize, i);
                foreach (int[] x in temp)
                    combs.Add(x);
            }
            //sort, of course
            combs.Sort(new ArrayIntComparer());
        }
        void GenerateSortedBitwisely() //generate and sort in ascending order (using bitwise) 
        {
            combs.Clear(); //clear old results
            combCount = (long)(Math.Pow(2, parsSize) - 1); //the size can be mathematically deduced

            int n = 0; //used to generate all the combinations

            //generate arrays of indices to map the parameters to
            for (int i = 0; i < combCount; i++)
            {
                n++;
                int index = 0; //each binary digit represents index
                List<int> combination = new List<int>();

                //every binary number yields one combination
                for (int j = n; j != 0;) //stops when 'j>>1 == 0' (every digit is checked)
                {
                    if ((j & 1) != 0) combination.Add(index); //'1' means to put index
                    index++;        //switch to next index
                    j = j >> 1;     //prepare next digit for the next iteration
                }
                combs.Add(combination.ToArray()); //add the combination
            }
            //sort, of course
            combs.Sort(new ArrayIntComparer());
        }
    }
}

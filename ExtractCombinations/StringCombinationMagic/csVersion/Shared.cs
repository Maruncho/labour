
namespace Shared
{
    class Combinatorics
    {
        //Creates combinations with length == limit, with the numbers from the range [0;max)
        //not written by me: https://www.baeldung.com
        internal static List<int[]> GenerateCombinations(int max, int limit)
        {
            List<int[]> combinations = new List<int[]>();
            int[] temp = new int[limit];
            List<int> combination = new List<int>(temp);

            // initialize with lowest lexicographic combination
            for (int i = 0; i < limit; i++)
            {
                combination[i] = i;
            }

            while (combination[limit - 1] < max)
            {
                combinations.Add(combination.ToArray());

                // generate next combination in lexicographic order
                int t = limit - 1;
                while (t != 0 && combination[t] == max - limit + t)
                {
                    t--;
                }
                combination[t]++;
                for (int i = t + 1; i < limit; i++)
                {
                    combination[i] = combination[i - 1] + 1;
                }
            }

            return combinations;
        }
    }

    //used to compare List<int>s
    internal class ArrayIntComparer : IComparer<int[]>
    {
        public int Compare(int[] x, int[] y)
        {
            for (int i = 0; i < x.Length; i++)
            {
                if (i == y.Length) return 1; // x>y
                int xx = x[i];
                int yy = y[i];
                if (xx < yy) return -1; // x<y
                if (xx > yy) return 1; // x>y
            }
            if (x.Length == y.Length) return 0; // x==y
            return -1; // x<y (fewer characters in x)
        }
    }
}

using ParameterExtract;
using Combinations;

namespace StringCombCS
{
    class Tests
    {
        public readonly string test = "param1, params2, jisdf334re, 984.0ur,  =-po98.2,";
        public readonly string test1 = "param1, para2asaasf, asf33.1aa,,,,,, 42.0aaaaaaaafug, not50.69lmao,    let'sDo6Too,,,,,,,,,,   ,,,, , , ,";
        public readonly string test2 = "114514,214541,3413514,41435,545345,654456,7415645,877889,912231,112430,13451,1132,1135413";
        public readonly string test3 = "0,222,1,54,89,01,22,43,1,44,21,54";
        public readonly string test4 = "7,33,1,5,22,15,83,101,434,1101,10";
        public readonly string test5 = "22,1,43,17,9,17,32,16,21";
        public readonly string test6 = "1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,,1,,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1";
        public readonly string test7 = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    };

    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                //UNBREAKABLE?!?!
                ParameterExtractor parExtractor = new ParameterExtractor();
                parExtractor.WhiteSpace = ",";
                parExtractor.DistanceFromPoint = 1;
                parExtractor.Limit = 50;

                Console.WriteLine("Let your cat walk on the keyboard, then put some numbers and \n'whitespace' characters here and there, if there aren't some already:");
                //Console.WriteLine($"Enter parameters, separated by ({parExtractor.WhiteSpace}). Each parameter must have \none number. If there are more than one, first is selected:");

                //Tests tests = new Tests();
                //List<int> list = parExtractor.ExtractIntegers(tests.test3);

                List<int> list = parExtractor.ExtractIntegers(Console.ReadLine());

                //Combo stuff
                CombinationMagic combo = new CombinationMagic(list);
                combo.SortedBitwisely();

                combo.PrintCombinations();
                Console.WriteLine(String.Join(" -> ", combo.LongestAscendingCombination()));
            }
            catch (ParameterExtractor.PExtractError e)
            {
                Console.WriteLine($"ParameterExtractor ERROR: {e.Message}");
            }
            catch (CombinationMagic.CombMagicError e)
            {
                Console.WriteLine($"CombinationMagic ERROR: {e.Message}");
            }
            catch (Exception e)
            {
                Console.WriteLine($"EXCEPTION: {e}");
            }
        }
    }
}

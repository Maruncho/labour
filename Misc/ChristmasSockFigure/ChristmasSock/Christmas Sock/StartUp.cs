namespace Christmas_Sock
{
    using System;
    class StartUp
    {
        static void Main(string[] args)
        {
            int n = int.Parse(Console.ReadLine());
            DrawFirstPart(n);
            DrawSecondPart(n);
            DrawLastPart(n);
        }
        public static void DrawFirstPart(int n)
        {
            string dashes = new string('-', n * 2);
            string stars = new string('*', n * 2);
            string first = string.Format($"|{dashes}|");
            string second = string.Format($"|{stars}|");
            Console.WriteLine(first);
            Console.WriteLine(second);
            Console.WriteLine(first);
        }
        public static void DrawSecondPart(int n)
        {
            int length = n * 2 - 3;

            int counterDashes = n - 1;
            int specialSymbolsCounter = 2;

            for (int i = 0; i < length; i++)
            {
                if (i > length / 2)
                {

                    counterDashes++;
                    specialSymbolsCounter -= 2;

                    string dashesSecond = new string('-', counterDashes);
                    string specialSymbols = new string('~', specialSymbolsCounter);
                   
                    string secondFormat = string.Format($"|{dashesSecond}{specialSymbols}{dashesSecond}|");
                    Console.WriteLine(secondFormat);

                }
                else
                {
                    string dashesSecond = new string('-', counterDashes);
                    string specialSymbols = new string('~', specialSymbolsCounter);
                     
                    string secondFormat = string.Format($"|{dashesSecond}{specialSymbols}{dashesSecond}|");
                    Console.WriteLine(secondFormat);

                    if (i == length / 2)
                    {
                        continue;
                    }
                    else
                    {
                        counterDashes--;
                        specialSymbolsCounter += 2;
                    }
                }
            }
        }
        public static void DrawLastPart(int n)
        {
            int loopLength = n + 3;
            int lastCounterDashes = 0;


            for (int i = 0; i < loopLength; i++)
            {
                if (i == n / 2)
                {
                    string dots = new string('.', n - 2);
                    string lastDashes = new string('-', lastCounterDashes);

                    string merry = string.Format($"{lastDashes}\\{dots}MERRY{dots}\\");
                    Console.WriteLine(merry);
                }
                else if (i == n / 2 + 2)
                {
                    string dots = new string('.', n - 2);
                    string lastDashes = new string('-', lastCounterDashes);

                    string xmas = string.Format($"{lastDashes}\\{dots}X-MAS{dots}\\");
                    Console.WriteLine(xmas);
                }
                else if (i == loopLength - 1)
                {
                    string undescore = new string('_', 2 * n + 1);
                    string lastDashes = new string('-', lastCounterDashes);

                    string lastRowFormat = string.Format($"{lastDashes}\\{undescore})");
                    Console.WriteLine(lastRowFormat);
                }
                else
                {

                    string dots = new string('.', 2 * n + 1);
                    string lastDashes = new string('-', lastCounterDashes);

                    string thirdFormat = string.Format($"{lastDashes}\\{dots}\\");
                    Console.WriteLine(thirdFormat);
                }
                lastCounterDashes++;
            }
        } 
    }
}

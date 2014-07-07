using System;
using System.IO;

namespace WPC60_PTC_Linearization
{
    class Program
    {
        static void Main(string[] args)
        {
            kty81_110_conversion[] mapping = 
            {
                new kty81_110_conversion(-55, 490, 0.99),
                new kty81_110_conversion(-50, 515, 0.98),
                new kty81_110_conversion(-40, 567, 0.96),
                new kty81_110_conversion(-30, 624, 0.93),
                new kty81_110_conversion(-20, 684, 0.91),
                new kty81_110_conversion(-10, 747, 0.88),
                new kty81_110_conversion(  0, 815, 0.85),
                new kty81_110_conversion( 10, 886, 0.83),
                new kty81_110_conversion( 20, 961, 0.80),
                new kty81_110_conversion( 25, 1000, 0.79),
                new kty81_110_conversion( 30, 1040, 0.78),
                new kty81_110_conversion( 40, 1122, 0.75),
                new kty81_110_conversion( 50, 1209, 0.73),
                new kty81_110_conversion( 60, 1299, 0.71),
                new kty81_110_conversion( 70, 1392, 0.69),
                new kty81_110_conversion( 80, 1490, 0.67),
                new kty81_110_conversion( 90, 1591, 0.65),
                new kty81_110_conversion( 100, 1696, 0.63),
                new kty81_110_conversion( 110, 1805, 0.61),
                new kty81_110_conversion( 120, 1915, 0.58),
                new kty81_110_conversion( 135, 1970, 0.55),
                new kty81_110_conversion( 130, 2023, 0.52),
                new kty81_110_conversion( 140, 2124, 0.45),
                new kty81_110_conversion( 150, 2211, 0.35)
            };

            // We'll write results out to a text file
            StreamWriter sw = new StreamWriter(Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "results.txt"));

            while (true)
            {
                const string prompt = "Enter integer resistance in ohms : ";
                Console.Write(prompt);

                string inputValue = Console.ReadLine();

                double resistance;
                if (!double.TryParse(inputValue, out resistance))
                {
                    Console.WriteLine("Invalid value");
                    continue;
                }

                int maxElement = mapping.GetUpperBound(0);
                if (resistance < mapping[0].Resistance || resistance > mapping[maxElement].Resistance)
                {
                    Console.WriteLine("Enter a value between {0} and {1}", mapping[0].Resistance, mapping[maxElement].Resistance);
                    continue;
                }

                double temperature = 0;

                for (int i = 0; i <= maxElement; i++)
                {
                    if (resistance <= mapping[i].Resistance)
                    {
                        if (i == 0)
                        {
                            temperature = mapping[i].Temperature;
                            break;
                        }

                        int minTemp = mapping[i - 1].Temperature;
                        int maxTemp = mapping[i].Temperature;
                        double minResist = mapping[i - 1].Resistance;
                        double maxResist = mapping[i].Resistance;

                        temperature = (resistance - minResist) / (maxResist - minResist) * (maxTemp - minTemp) + minTemp;
                        break;
                    }
                }

                string message = string.Format("Temperature = {0:0.000}°C", temperature);
                Console.WriteLine(message);

                sw.WriteLine("Resistance = {0:0.00}Ω  Temperature = {1:0.000}°C", resistance, temperature);
                sw.Flush();
            }
        }
    }

    class kty81_110_conversion
    {
        public int Temperature { get; private set; }
        public int Resistance { get; private set; }
        public double TempCoefficient { get; private set; }

        public kty81_110_conversion(int temperature, int resistance, double coefficient)
        {
            this.Temperature = temperature;
            this.Resistance = resistance;
            this.TempCoefficient = coefficient;
        }
    }
}

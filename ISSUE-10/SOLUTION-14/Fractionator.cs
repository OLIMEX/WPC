using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FractionTest
{
    public class Fractionator
    {
        public static IEnumerable<int> GetFractions(int a, int b)
        {
            if (a >= b || a == 0 || b == 0)
            {
                //Out of range
                return null;
            }

            var result = new List<int>();
            var goal = (double)a / b;
            var total = 0.0;
            var count = 2;

            do
            {
                if (goal >= total + (1d / count))
                {
                    total += 1f / count;
                    result.Add(count);
                }

                ++count;
            } while (total < goal);

            return total == goal ? result : null;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPC53_Random_Number_Generator
{
    public static class Random
    {
        private static uint seed = (uint)DateTime.Now.Ticks;

        public static uint Next()
        {
            return Next(seed);
        }

        public static uint Next(uint minValue, uint maxValue)
        {
            uint unbounded = Next(seed);
            return minValue + (unbounded % (maxValue - minValue + 1));
        }

        public static uint Next(uint initialSeed)
        {
            const uint multiplier = 1103515245;
            const uint addition = 12345;

            uint result;
            uint nextValue = initialSeed;

            nextValue *= multiplier;
            nextValue += addition;
            result = (uint)(nextValue / 65536) % 0x800;

            nextValue *= multiplier;
            nextValue += addition;
            result <<= 10;
            result ^= (uint)(nextValue / 65536) % 0x400;

            nextValue *= multiplier;
            nextValue += addition;
            result <<= 10;
            result ^= (uint)(nextValue / 65536) % 0x400;

            seed = nextValue;
            return result;
        }
    }
}

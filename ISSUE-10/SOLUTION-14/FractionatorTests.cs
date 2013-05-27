using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.Generic;
using System.Linq;

namespace FractionTest
{
    [TestClass]
    public class FractionatorTests
    {
        [TestMethod]
        public void TestMethod1()
        {
            var expected = new[] { 2, 3, 42 };
            Assert.IsTrue(Fractionator.GetFractions(6, 7).IsEqual(expected));
        }

        [TestMethod]
        public void TestMethod2()
        {
            var expected = new[] { 2, 4 };
            Assert.IsTrue(Fractionator.GetFractions(3, 4).IsEqual(expected));
        }

        [TestMethod]
        public void TestMethod3()
        {
            var expected = new[] { 2 };
            Assert.IsTrue(Fractionator.GetFractions(1, 2).IsEqual(expected));
        }

        [TestMethod]
        public void TestMethod4()
        {
            var expected = new[] { 4 };
            Assert.IsTrue(Fractionator.GetFractions(1, 4).IsEqual(expected));
        }

        [TestMethod]
        public void TestMethod5()
        {
            var expected = new[] { 2, 90 };
            Assert.IsTrue(Fractionator.GetFractions(23, 45).IsEqual(expected));
        }

        [TestMethod]
        public void TestMethod6()
        {
            var expected = new[] { 2, 3, 7, 73, 9018, 230409892 };
            Assert.IsTrue(Fractionator.GetFractions(99, 100).IsEqual(expected));
        }
    }

    public static class MyExtensions
    {
        public static bool IsEqual(this IEnumerable<int> primaryEnum, params int[] ints)
        {
            if (primaryEnum.Count() != ints.Length)
            {
                return false;
            }

            for (int i = 0; i < primaryEnum.Count(); i++)
            {
                if (primaryEnum.ElementAt(i) != ints[i])
                {
                    return false;
                }
            }

            return true;
        }
    }
}

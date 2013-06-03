using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace Challenge11
{
	[TestClass]
	public class Solution11UnitTests
	{
		string[] TestMaze0 = new[] {
			"WWWWWWWWWW",
			"W        W",
			"W       WW",
			"W        W",
			"W        W",
			"W        W",
			"W        W",
			"WWWWWWWWWW"
		};

		[TestMethod]
		public void TestMethod0()
		{
			var subject = new Solution11(TestMaze0);

			Assert.IsTrue(subject.LargestAreaObstacles == 0);
		}

		string[] TestMaze1 = new[] {
			"WWWWWWWWWW",
			"W  WW    W",
			"W       WW",
			"W  @@    W",
			"W @@     W",
			"W      @ W",
			"W@    @@ W",
			"WWWWWWWWWW"
		};

		[TestMethod]
		public void TestMethod1()
		{
			var subject = new Solution11(TestMaze1);

			Assert.IsTrue(subject.LargestAreaObstacles == 4);
		}

		string[] TestMaze2 = new[] { "" };

		[TestMethod]
		public void TestMethod2()
		{
			var subject = new Solution11(TestMaze2);

			Assert.IsTrue(subject.LargestAreaObstacles == 0);
		}

		string[] TestMaze3 = new[] 
		{
			"WWW",
			"WWW"
		};

		[TestMethod]
		public void TestMethod3()
		{
			var subject = new Solution11(TestMaze3);

			Assert.IsTrue(subject.LargestAreaObstacles == 0);
		}

		string[] TestMaze4 = new[] {
			"WWWWWWWWWW",
			"W  @@    W",
			"W @  @  WW",
			"W @   @  W",
			"W @@@@   W",
			"W      @ W",
			"W@    @@ W",
			"WWWWWWWWWW"
		};

		[TestMethod]
		public void TestMethod4()
		{
			var subject = new Solution11(TestMaze4);

			Assert.IsTrue(subject.LargestAreaObstacles == 10);
		}

		string[] TestMaze5 = new[] {
			"WWWWWWWWWW",
			"W  @@    W",
			"W @   @@WW",
			"W@  @@  @W",
			"W@  @   @W",
			"W @    @ W",
			"W  @@@@  W",
			"WWWWWWWWWW"
		};

		[TestMethod]
		public void TestMethod5()
		{
			var subject = new Solution11(TestMaze5);

			Assert.IsTrue(subject.LargestAreaObstacles == 18);
		}

		string[] TestMaze6 = new[] {
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
			"W   @     @                         @          W",
			"W   @     @                        @ @         W",
			"W   @     @                       @   @        W",
			"W   @     @                      @  @  @       W",
			"W   @@@@@@@                     @   @   @      W",
			"W    @@@@@@                    @    @   @@     W",
			"W     @@@@@                   @     @          W",
			"W      @@@@                  @      @          W",
			"W       @@@                 @       @          W",
			"W        @@                @  @@@@@@@@@@@@@@@@ W",
			"W         @               @         @          W",
			"W          @             @    @@@@@@@@@@       W",
			"W           @           @     @@@@@@@@@@       W",
			"W            @         @      @@@@@@@@@@       W",
			"W             @       @       @@@@@@@@@@       W",
			"W              @     @        @@@@@@@@@@       W",
			"W               @   @         @@@@@@@@@@       W",
			"W                @ @          @@@@@@@@@@       W",
			"W                 @           @@@@@@@@@@       W",
			"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
		};

		[TestMethod]
		public void TestMethod6()
		{
			var subject = new Solution11(TestMaze6);

			Assert.IsTrue(subject.LargestAreaObstacles == 103);
		}
	}
}

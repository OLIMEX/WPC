/*
 *  Olimex WPC 51 - Container load
 *  
 */

using System;
using System.Collections.Generic;
using System.Linq;

namespace packer
{

	class Container
	{
		static public int width = 244;
		static public int length = 609;
		static public int height = 244;
	}

	class Box
	{
		public int width, length, height;
		public int top, front, side;
		public int volume;
		public int x,y,z;
		public int id;

		private void swap (ref int a, ref int b)
		{
			int temp = a;
			a = b;
			b = temp;
		}

		public Box (int aWidth, int aLength, int aHeight)
		{
			width = aWidth;
			length = aLength;
			height = aHeight;

			if (width <length)
				swap (ref width, ref length);
			if (length < height)
				swap (ref length, ref height);
			if (width < length)
				swap (ref width, ref length);

			top = width * length;
			front = width * height;
			side = length * height;

			if (top < front)
				swap (ref top, ref front);
			if (front < side)
				swap (ref front, ref side);
			if (top < front)
				swap (ref top, ref front);

			volume = width * length * height;
		}
	}

	class Solver
	{
		private List<Box> boxes;
		private List<Box> solution;

		private static int id = 0;

		public void AddBox(Box aBox)
		{
			aBox.id = id;
			id++;
			boxes.Add(aBox);
		}

		public void AddBoxes (List<Box> problem)
		{
			foreach (Box b in problem) 
			{
				b.id = id;
				id++;
			}

			boxes.AddRange(problem);
		}

		public Solver()
		{
			boxes = new List<Box>();
			solution = new List<Box>();
		}

		public void PrintProblem ()
		{
			foreach (Box b in boxes)
				Console.WriteLine("Box {0} with width: {1}, length: {2}, height: {3}", b.id, b.width, b.length, b.height);
		}

		public void PrintSolution ()
		{
			int vol_used = 0;
			int vol_total = Container.width * Container.height * Container.length;

			foreach (Box b in solution) 
			{
				vol_used += b.volume;
				Console.WriteLine ("Box {0} with width: {1}, length: {2}, height: {3} at location ({4},{5},{6})", 
				                   b.id,
				                   b.width, b.length, b.height,
				                   b.x, b.y, b.z);
			}

			Console.WriteLine("Total boxes  : {0}", boxes.Count + solution.Count);
			Console.WriteLine("Boxes packed : {0}", solution.Count);
			Console.WriteLine("Used volume  : {0} m3", vol_used / 1000000);
			Console.WriteLine("Total volume : {0} m3", vol_total / 1000000);
			Console.WriteLine("Efficiency   : {0:0%}", (double)vol_used / vol_total);

			/*Console.WriteLine("---");
			foreach (Box b in solution) 
			{
				Console.WriteLine ("{0}\t{1}\t{2}\t{3}\t{4}\t{5}\t{6}", 
				                   b.id,
				                   b.width, b.length, b.height,
				                   b.x, b.y, b.z);
			}
			Console.WriteLine("---");*/
		}

		public List<Box> Solve()
		{
			boxes = boxes.OrderBy(x => x.height).ThenByDescending(x => x.top).ToList();
			int cx = 0;
			int cy = 0;
			int cz = 0;
			int y_max = 0;
			int z_max = 0;
			while (boxes.Count > 0) 
			{
				Box abox = boxes[0];
				if (cx + abox.width > Container.width)
				{
					cx = 0 ;
					cy = y_max;
				}

				if (cy + abox.length > Container.length)
				{
					cx = 0;
					cy = 0;
					y_max = 0;
					cz = z_max;
				}

				if (cz + abox.height > Container.height)
					return solution;

				abox.x = cx;
				abox.y = cy;
				abox.z = cz;
				y_max = Math.Max(y_max, cy + abox.length);
				z_max = Math.Max(z_max, cz + abox.height);
				cx += abox.width;
				solution.Add(abox);
				boxes.Remove(abox);
				Console.WriteLine("Placed {0} at {1},{2},{3}", abox.id, cx, cy, cz);
			}
			return solution;
		}
	}

	class Tester
	{
		List<Box> problem;

		public Tester()
		{
			problem = new List<Box>();
			Random r = new Random(1024);
			for (int i = 0; i < 500; i++)
				problem.Add(new Box(r.Next(50,100), r.Next(5,100), r.Next(5,100)));
		}

		public void Test ()
		{
			Solver s = new Solver();
			s.AddBoxes(problem);
			s.PrintProblem();
			s.Solve();
			s.PrintSolution();
		}
	}

	class MainClass
	{
		public static void Main (string[] args)
		{
			Tester t = new Tester();
			t.Test();
		}
	}
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Challenge11
{
	public class Solution11
	{
		private const char Obstacle = '@';

		private string[] Maze { get; set; }

		public Solution11(string[] maze)
		{
			if (maze == null || maze.Length < 3 || maze.Length > 100)
			{
				Maze = null;
			}
			else
			{
				Maze = maze;
			}
		}

		public int? LargestAreaObstacles
		{
			get
			{
				if (Maze == null)
				{
					return 0;
				}

				var obsLocation = FindNextObstacle();

				if (obsLocation == null)
				{
					return 0;
				}

				int i = 0;
				int maxConnected = 0;

				do
				{
					var connected = GetConnObsAtLoc(i, obsLocation);

					if (maxConnected < connected)
					{
						maxConnected = connected;
					}

					obsLocation = FindNextObstacle();
					++i;

				} while (obsLocation != null);

				return maxConnected;
			}
		}

		private Tuple<int, int> FindNextObstacle()
		{
			for (int i = 0; i < Maze.Length; i++)
			{
				var obsIndex = Maze[i].IndexOf(Obstacle);

				if (obsIndex > 0)
				{
					return new Tuple<int, int>(i, obsIndex);
				}
			}

			return null;
		}


		/// <summary>
		/// Recursive method that updates the current position to an int (number of the connected shape).
		/// Then returns the total number of connected obstacles
		/// </summary>
		/// <param name="i">Shape Number</param>
		/// <param name="obsLoc">Location (position) of the shape</param>
		/// <returns>Number of obstacles in a shape</returns>
		private int GetConnObsAtLoc(int i, Tuple<int, int> obsLoc)
		{
			if (Maze[obsLoc.Item1][obsLoc.Item2] != Obstacle)
			{
				return 0;
			}

			//Replace with an int
			Maze[obsLoc.Item1] = Maze[obsLoc.Item1].ReplaceAt(obsLoc.Item2, i);

			return
				//top left
				GetConnObsAtLoc(i, new Tuple<int, int>(obsLoc.Item1 - 1, obsLoc.Item2 - 1)) +
				//top center
				GetConnObsAtLoc(i, new Tuple<int, int>(obsLoc.Item1 - 1, obsLoc.Item2)) +
				//top right
				GetConnObsAtLoc(i, new Tuple<int, int>(obsLoc.Item1 - 1, obsLoc.Item2 + 1)) +

				//mid left
				GetConnObsAtLoc(i, new Tuple<int, int>(obsLoc.Item1, obsLoc.Item2 - 1)) +
				//mid right
				GetConnObsAtLoc(i, new Tuple<int, int>(obsLoc.Item1, obsLoc.Item2 + 1)) +

				//bottom left
				GetConnObsAtLoc(i, new Tuple<int, int>(obsLoc.Item1 + 1, obsLoc.Item2 - 1)) +
				//bottom center
				GetConnObsAtLoc(i, new Tuple<int, int>(obsLoc.Item1 + 1, obsLoc.Item2)) +
				//bottom right
				GetConnObsAtLoc(i, new Tuple<int, int>(obsLoc.Item1 + 1, obsLoc.Item2 + 1)) +
				//current location
				1;
		}
	}

	public static class ExtensionClass
	{
		public static string ReplaceAt(this string input, int index, int newInt)
		{
			if (input == null)
			{
				throw new ArgumentNullException("input");
			}
			char[] chars = input.ToCharArray();
			chars[index] = newInt.ToString()[0];
			return new string(chars);
		}
	}
}

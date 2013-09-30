using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace SquareTest
{
    class Program
    {
        public const double MAX_REL_ERROR=0.0001;

        class point
            {

            public double x, y;
            public static List<point> allPoints;

            public point(double parx, double pary)
                {
                x = parx;
                y = pary;
               if (allPoints==null)
                    {
                    allPoints = new List<point>();

                    }

                allPoints.Add(this);

                }

            public double calcDistance(point parPointA, point parPointB)
                {
                return Math.Sqrt(Math.Pow(parPointA.x - parPointB.x, 2) + Math.Pow(parPointA.y - parPointB.y, 2));
                }

            public double calcDistance(double parA, double parB)
                {
                return Math.Sqrt(Math.Pow(parA - parB, 2) + Math.Pow(parA - parB, 2));
                }

            public double calcDistance(double parA)
                {
                return Math.Sqrt(2 * Math.Pow(parA, 2));
                }

            //Check if this point can be a square point, when it has two side a plus hypothenuse
            public Boolean is_aah()
                {
                if (allPoints.Count != 4)
                    {

                    return false;

                    }

                double[] distance = new double[3];
                int i = 0;


                foreach (point iPoint in allPoints)
                    {
                    if(iPoint!=this)
                    distance[i++] = calcDistance(this, iPoint);
                    }


                if (compareDouble(distance[0], distance[1]) && compareDouble(calcDistance(distance[0]), distance[2]))
                    {
                    return true;

                    }
                else if (compareDouble(distance[0], distance[2]) && compareDouble(calcDistance(distance[0]), distance[1]))
                    {


                    return true;

                    }
                else if (compareDouble(distance[1], distance[2]) && compareDouble(calcDistance(distance[1]), distance[0]))
                    {

                    return true;

                    }

                return false;

                }




            public bool compareDouble(double parA, double parB)
                {
                double relativeError;
                if (Math.Abs(parB) > Math.Abs(parA))
                    {

                    relativeError = Math.Abs((parA - parB) / parB);

                    }
                else
                    {

                    relativeError = Math.Abs((parA - parB) / parA);
                    }

                return (relativeError < MAX_REL_ERROR);


                }

            }


        static void Main(string[] args)
        {
            String _sInputString;
            List<point> _pointList =new List<point>();


            try {
           
            if (args.Length == 0)
            {
                 
                Console.WriteLine("Please provide Input:");
               _sInputString = Console.ReadLine();


            }
            else
            {
                _sInputString = args[0];
            }
            String[] _ssArgs;

            _ssArgs = Regex.Split(_sInputString, @"\(([^)]*)\)");

            foreach (String iString in _ssArgs) {

            if (!iString.Equals("") && Regex.IsMatch(iString, @"-?\d,-?\d"))
                {

                String[] parCordinates = iString.Split(',');

                double x = Double.Parse(parCordinates[0]);
                double y = Double.Parse(parCordinates[1]);
                _pointList.Add(new point(x, y));
                }
            }

               
            bool isSquare=true;

            if (point.allPoints == null) {
            Console.WriteLine("No Points entered!");
                }

            // At least two points must be of the type a-a-h, two similiar sides and one hypothenuse.
           foreach(point iPoint in point.allPoints) {
               if(iPoint.is_aah())
                   {
                   isSquare &= true;
                   }else{
                   isSquare &= false;
                   }

               }



            if(isSquare)
                {
                Console.WriteLine("->Square");
                } else
                {
                Console.WriteLine("->Not Square");
                }
            Console.Read();

            }
            catch (Exception e) 
                {
                Console.WriteLine(e.ToString());
                }
           

                

        }
    }
}
